let onKeyUp = (event: Dom.keyboardEvent) : unit =>
  switch (Webapi.Dom.KeyboardEvent.code(event)) {
  | _ => ()
  };

let render = (ctx, state: Types.shipState) =>
  switch state.potentialSprite {
  | _ => ()
  };