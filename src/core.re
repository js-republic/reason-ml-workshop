open Webapi.Canvas.Canvas2d;
open Webapi.Canvas.CanvasElement;
open Webapi.Dom;

let bootStrapGame = (el) => {
  let ctx = getContext2d(el);

  setFillStyle(ctx, String, "red");
  ctx |> beginPath;
  ctx |> rect(~x=0., ~y=0., ~w=110., ~h=100.);
  ctx |> fill;
};

let canvasEl = Document.getElementById("game", document);
switch (canvasEl){
| Some(el) => bootStrapGame(el)
| None => Js.log("Canvas introuvable")
};