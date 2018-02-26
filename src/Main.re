open Webapi.Dom;

open HtmlImage;

open Js.Promise;

open Actions;

let dispatchAllImageActions = imgs =>
  switch imgs {
  | [|shipImg, bgImg, alienImg, shotImg|] =>
    Store.dispatch(ShipImageLoaded(shipImg));
    Store.dispatch(BgImageLoaded(bgImg));
    Store.dispatch(AlienImageLoaded(alienImg));
    Store.dispatch(ShotImageLoaded(shotImg));
    resolve();
  | _ => failwith("At least one image is not loaded correctly")
  };

switch (Document.getElementById("game", document)) {
| Some(el) =>
  let ctx = Webapi.Canvas.CanvasElement.getContext2d(el);
  Game.run(ctx);
  all([|
    loadImage("assets/ship.png"),
    loadImage("assets/space2.png"),
    loadImage("assets/normal-alien.png"),
    loadImage("assets/shot.png")
  |])
  |> then_(dispatchAllImageActions)
  |> catch(err => {
       Js.log(err);
       resolve();
     })
  |> ignore;
  ();
| None => failwith("Canvas introuvable")
};