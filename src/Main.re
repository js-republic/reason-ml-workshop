open HtmlImage;

open Actions;

let dispatchAllImageActions = imgs =>
  switch imgs {
  | [|shipImg, bgImg, alienImg, shotImg|] =>
    Store.dispatch(ShipImageLoaded(shipImg));
    Store.dispatch(BgImageLoaded(bgImg));
    Store.dispatch(AlienImageLoaded(alienImg));
    Store.dispatch(ShotImageLoaded(shotImg));
    Js.Promise.resolve();
  | _ => failwith("At least one image is not loaded correctly")
  };

switch (Webapi.Dom.Document.getElementById("game", Webapi.Dom.document)) {
| Some(el) =>
  let ctx = Webapi.Canvas.CanvasElement.getContext2d(el);
  Game.run(ctx);
  Js.Promise.all([|
    loadImage("assets/ship.png"),
    loadImage("assets/space2.png"),
    loadImage("assets/normal-alien.png"),
    loadImage("assets/shot.png")
  |])
  |> Js.Promise.then_(dispatchAllImageActions)
  |> Js.Promise.catch(err => {
       Js.log(err);
       Js.Promise.resolve();
     })
  |> ignore;
  ();
| None => failwith("Canvas introuvable")
};