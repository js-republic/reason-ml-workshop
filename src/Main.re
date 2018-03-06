open Actions;

open Store;

type canvasContext = Webapi.Canvas.Canvas2d.t;

let rec onFrame = (ctx: canvasContext, lastTime: float, newTime: float) => {
  dispatch(Tick);
  applyReducers(newTime -. lastTime);
  switch store.stage {
  | Some(stage) => stage.render(ctx, store.state)
  | _ => ()
  };
  Webapi.requestAnimationFrame(onFrame(ctx, newTime));
  ();
};

let runGame = (ctx: canvasContext) : unit => {
  Stage.goTo(Stage.inGame);
  Webapi.requestAnimationFrame(onFrame(ctx, 0.));
};

[@bs.new] external makeImage : unit => Types.image = "Image";

[@bs.set] external setSrc : (Types.image, string) => unit = "src";

[@bs.set] external setOnload : (Types.image, unit => unit) => unit = "onload";

[@bs.set] external setError : (Types.image, unit => unit) => unit = "onerror";

exception ImageNotFound(string);

let loadImage = (url: string) : Js.Promise.t(Types.image) => {
  let img = makeImage();
  setSrc(img, url);
  Js.Promise.make((~resolve, ~reject) => {
    setOnload(img, () => [@bs] resolve(img));
    setError(img, () =>
      [@bs] reject(ImageNotFound(url ++ "cannot be loaded."))
    );
    ();
  });
};

switch (Webapi.Dom.Document.getElementById("game", Webapi.Dom.document)) {
| Some(el) =>
  let ctx = Webapi.Canvas.CanvasElement.getContext2d(el);
  runGame(ctx);
  Js.Promise.(
    all4((
      loadImage("assets/ship.png"),
      loadImage("assets/bg.png"),
      loadImage("assets/alien.png"),
      loadImage("assets/shot.png")
    ))
    |> then_(imgs =>
         switch imgs {
         | (shipImg, bgImg, alienImg, shotImg) =>
           Store.dispatch(ShipImageLoaded(shipImg));
           Store.dispatch(BgImageLoaded(bgImg));
           Store.dispatch(AlienImageLoaded(alienImg));
           Store.dispatch(ShotImageLoaded(shotImg));
           resolve();
         }
       )
    |> catch(err => {
         Js.log(err);
         resolve();
       })
    |> ignore
  );
  ();
| None => failwith("Canvas introuvable")
};