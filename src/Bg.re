open Webapi.Canvas.Canvas2d;

let renderStartStage = (ctx: Types.canvasContext, state: Types.screenState) => {
  setFillStyle(ctx, String, "black");
  ctx |> beginPath;
  ctx |> rect(~x=0., ~y=0., ~w=state.width, ~h=state.height);
  ctx |> fill;
  setFillStyle(ctx, String, "white");
  font(ctx, "30px Arial");
  textAlign(ctx, "center");
  ctx |> fillText("Start Game", ~x=state.width /. 2., ~y=state.height /. 2.);
  ();
};

let renderInGame =
    (canvasContext: Types.canvasContext, state: Types.screenState) =>
  switch state.potentialBg {
  | Some(bg) => Image.draw(canvasContext, bg, ~x=0., ~y=0.)
  | None => ()
  };