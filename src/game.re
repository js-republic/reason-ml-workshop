open Util;
open Constants;
open Webapi.Canvas.Canvas2d;

let run = (ctx, images: (gameImage ,gameImage, gameImage, gameImage)) => {
  setFillStyle(ctx, String, "tomato");
  ctx |> beginPath;
  ctx |> rect(~x=0., ~y=0., ~w=game.width, ~h=game.height);
  ctx |> fill;
}

/*
  Document.addEventListener("keydown", (event: Dom.event):unit => {
    Js.log(event);
  }, document);
*/