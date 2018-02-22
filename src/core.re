open Webapi.Canvas.CanvasElement;
open Webapi.Dom;

type stage = {
  width: float,
  height: float
};
let game:stage = {
  width : 500.,
  height : 500.
};

type keyCode = {
  left : int,
  right : int,
  space : int,
  back: int,
};

let keys = {
  left : 37,
  right : 39,
  space : 32,
  back: 13
};

type image;

[@bs.send.pipe : Webapi.Canvas.Canvas2d.t] external drawImage : (image, int, int) => unit = "";
let loadImage: (string)=> Js.Promise.t(image) = [%bs.raw {|
  function (url) {
    const img = new Image();
    img.src = url;
    return new Promise ((resolve, reject) => {
      img.onload = () => resolve(img);
    });
  }
|}];

let onKeyDown = (event: Dom.event):unit => {
  Js.log(event);
};


let bootStrapGame = (el) => {
  let ctx = getContext2d(el);
  let futurShip = loadImage("ship.png");
  futurShip
   |> Js.Promise.then_(content => {
     ctx |> drawImage(content, 50, 50);
     Js.Promise.resolve(content);
   });

  /*setFillStyle(ctx, String, "red");
  ctx |> beginPath;
  ctx |> rect(~x=0., ~y=0., ~w=game.width, ~h=game.height);
  ctx |> fill;*/

  

  Document.addEventListener("keydown", onKeyDown, document);
};

let canvasEl = Document.getElementById("game", document);
switch (canvasEl){
  | Some(el) => bootStrapGame(el)
  | None => Js.log("Canvas introuvable")
};