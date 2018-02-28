open HtmlImage;

open Actions;

open Store;

type canvasContext = Webapi.Canvas.Canvas2d.t;

let rec onFrame = (ctx: canvasContext, lastTime: float, newTime: float) => {
  dispatch(Tick(newTime -. lastTime));
  applyReducers();
  switch store.stage {
  | Some(stage) => stage.render(ctx, store.state)
  | _ => ()
  };
  Webapi.requestAnimationFrame(onFrame(ctx, newTime));
  ();
};

let runGame = (ctx: canvasContext) : unit => {
  Stage.goTo(Stage.start);
  Webapi.requestAnimationFrame(onFrame(ctx, 0.));
};

switch (Webapi.Dom.Document.getElementById("game", Webapi.Dom.document)) {
| Some(el) =>
  let ctx = Webapi.Canvas.CanvasElement.getContext2d(el);
  runGame(ctx);
  Js.Promise.all([|
    loadImage("assets/ship.png"),
    loadImage("assets/space2.png"),
    loadImage("assets/normal-alien.png"),
    loadImage("assets/shot.png")
  |])
  |> Js.Promise.then_(imgs =>
       switch imgs {
       | [|shipImg, bgImg, alienImg, shotImg|] =>
         Store.dispatch(ShipImageLoaded(shipImg));
         Store.dispatch(BgImageLoaded(bgImg));
         Store.dispatch(AlienImageLoaded(alienImg));
         Store.dispatch(ShotImageLoaded(shotImg));
         Js.Promise.resolve();
       | _ => failwith("At least one image is not loaded correctly")
       }
     )
  |> Js.Promise.catch(err => {
       Js.log(err);
       Js.Promise.resolve();
     })
  |> ignore;
  ();
| None => failwith("Canvas introuvable")
};