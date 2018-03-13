let render = (canvasContext: Types.canvasContext, state: Types.shot) =>
  switch state.potentialSprite {
  | Some(img) => Image.draw(canvasContext, img, ~x=state.x, ~y=state.y)
  | _ => ()
  };