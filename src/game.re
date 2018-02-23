open Constants;
open Webapi.Canvas.Canvas2d;

type state = StartState | InGameState | EndState;

let handleStartState = (ctx: Canvas2dRe.t, images) => {
  setFillStyle(ctx, String, "tomato");
  ctx |> beginPath;
  ctx |> rect(~x=0., ~y=0., ~w=game.width, ~h=game.height);
  ctx |> fill;
  /*
  goToState(ctx, images, InGameState);*/
  ()
};
 
let handleInGameState = (ctx: Canvas2dRe.t, images) => {
  /*goToState(ctx, images, EndState);*/
  ()
};

let handleEndState = (ctx: Canvas2dRe.t, images) => {
  /*goToState(ctx, images, StartState);*/
  ()
};

let goToState = (ctx: Canvas2dRe.t, images, currentState: state): unit => switch (currentState) {
  | StartState => handleStartState(ctx, images)
  | InGameState => handleInGameState(ctx, images)
  | EndState => handleEndState(ctx, images)
};

let run = (ctx: Canvas2dRe.t, images): unit => {
  goToState(ctx, images, StartState);
}


/*
  Document.addEventListener("keydown", (event: Dom.event):unit => {
    Js.log(event);
  }, document);
*/