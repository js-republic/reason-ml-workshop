open Types;

let render = (ctx, state: shot) =>
  switch state.potentialSprite {
  | Some(img) => HtmlImage.drawImage(img, ~x=state.x, ~y=state.y, ctx)
  | _ => ()
  };