open Webapi.Canvas.Canvas2d;

let render = (ctx: Webapi.Canvas.Canvas2d.t, state: Types.screenState) => {
  switch state.potentialBg {
  | Some(bg) => HtmlImage.drawImage(bg, 0, 0, ctx)
  | None =>
    setFillStyle(ctx, String, "black");
    ctx |> beginPath;
    ctx |> rect(~x=0., ~y=0., ~w=state.width, ~h=state.height);
    ctx |> fill;
  };
  ();
};