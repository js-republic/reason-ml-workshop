open Webapi.Canvas.Canvas2d;

let render = (ctx: Webapi.Canvas.Canvas2d.t, state: Types.screenState) => {
  setFillStyle(ctx, String, "black");
  ctx |> beginPath;
  ctx |> rect(~x=0., ~y=0., ~w=state.width, ~h=state.height);
  ctx |> fill;
  setFillStyle(ctx, String, "white");
  ctx |> fillText("Start Game", ~x=10., ~y=50.);
  ();
};