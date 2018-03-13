let onKeyDown = (keyCode: string) : unit =>
  switch keyCode {
  | _ => ()
  };

let render = (canvasContext: Types.canvasContext, state: Types.shipState) =>
  switch state.potentialShipSprite {
  | None => ()
  };