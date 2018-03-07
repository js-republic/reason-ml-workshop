let render = (ctx, state: Types.alien) =>
  switch state.potentialSprite {
  | Some(img) => Image.draw(ctx, img, ~x=state.x, ~y=state.y)
  | _ => ()
  };