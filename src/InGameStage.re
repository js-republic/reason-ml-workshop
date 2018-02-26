open Webapi.Canvas.Canvas2d;

let render = (ctx: Webapi.Canvas.Canvas2d.t, state: State.rootStateType) => {
  switch state.screen.potentialBg {
  | Some(bg) => HtmlImage.drawImage(bg, 0, 0, ctx)
  | None =>
    setFillStyle(ctx, String, "black");
    ctx |> beginPath;
    ctx |> rect(~x=0., ~y=0., ~w=state.screen.width, ~h=state.screen.height);
    ctx |> fill;
  };
  ();
};