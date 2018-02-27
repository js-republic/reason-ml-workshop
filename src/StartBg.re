open Webapi.Canvas.Canvas2d;

let willMount = state => ();

let willDestroy = state => ();

let render = (ctx: Webapi.Canvas.Canvas2d.t, state: Types.screenState) => {
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