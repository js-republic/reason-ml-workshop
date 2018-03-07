let onSpace = (state: Types.shipState) => {
  let y = Constants.height -. state.height;
  let x = state.x +. state.width /. 2.;
  Store.dispatch(Actions.Fire(x, y));
};

let onKeyUp = (event: Dom.keyboardEvent) : unit =>
  switch (Webapi.Dom.KeyboardEvent.code(event)) {
  | "ArrowLeft" => Store.dispatch(Actions.GoLeft)
  | "ArrowRight" => Store.dispatch(Actions.GoRight)
  | "Space" => onSpace(Store.store.state.ship)
  | _ => ()
  };

let render = (canvasContext: Types.canvasContext, state: Types.shipState) =>
  switch state.potentialSprite {
  | Some(sprite) => Image.draw(canvasContext, sprite, ~x=state.x, ~y=state.y)
  | None => ()
  };