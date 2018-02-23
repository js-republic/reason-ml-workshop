open Webapi.Dom;
open Util;
let bootstrapGame = (el: Dom.element) => {
  let ctx: Canvas2dRe.t = Webapi.Canvas.CanvasElement.getContext2d(el);
  Js.Promise.all4((
    loadImage("assets/ship.png"),
    loadImage("assets/space2.png"),
    loadImage("assets/normal-alien.png"),
    loadImage("assets/bad-alien.png")
  ))
  |> Js.Promise.then_( images => {
    Game.run(ctx, images);
    Js.Promise.resolve();
  })
  |> Js.Promise.catch( error => {
    Js.log(error);
    Js.Promise.resolve();
  })
  |> ignore;
  ()
};
let canvasEl: option(Dom.element) = Document.getElementById("game", document);
switch (canvasEl){
  | Some(el) => bootstrapGame(el)
  | None => failwith ("Canvas introuvable")
};