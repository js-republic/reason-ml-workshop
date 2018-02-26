open Webapi.Dom;

open HtmlImage;

open Js.Promise;

open Actions;

let dispatchAllImageActions = imgs =>
  switch imgs {
  | [|shipImg, bgImg, alienImg, shotImg|] =>
    Game.dispatch(ShipImageLoaded(shipImg));
    Game.dispatch(BgImageLoaded(bgImg));
    Game.dispatch(AlienImageLoaded(alienImg));
    Game.dispatch(ShotImageLoaded(shotImg));
    resolve();
  | _ => failwith("At least one image is not loaded correctly")
  };

let bootstrapGame = (el: Dom.element) => {
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
};

let canvasEl: option(Dom.element) = Document.getElementById("game", document);

switch canvasEl {
| Some(el) => bootstrapGame(el)
| None => failwith("Canvas introuvable")
};
/*
 all([|
     loadImage("assets/ship.png"),
     loadImage("assets/space2.png"),
     loadImage("assets/normal-alien.png"),
     loadImage("assets/bad-alien.png")
   |])
   |> then_([|shipImg, space2Img, alienImg, badAlienImg|] => {
     resolve();
   })
   |> catch(error => {
        Js.log(error);
        resolve();
      })
   |> ignore;
   ()

 */