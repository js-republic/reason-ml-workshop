open Webapi.Canvas.Canvas2d;

let renderStartStage = (ctx: t, state: Types.screenState) => {
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

let renderInGame = (ctx: Webapi.Canvas.Canvas2d.t, state: Types.screenState) =>
  switch state.potentialBg {
  | Some(bg) => HtmlImage.drawImage(bg, ~x=0., ~y=0., ctx)
  | None => ()
  };