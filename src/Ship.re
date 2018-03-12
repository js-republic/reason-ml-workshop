let onSpace = (state: Types.shipState) : unit => {
  let y = Constants.height -. state.height;
  let x = state.x +. state.width /. 2.;
  Store.dispatch(Actions.Fire({x, y}));
};

let onKeyUp = (keyCode: string) : unit =>
  switch keyCode {
  | "ArrowLeft" => Store.dispatch(Actions.GoLeft)
  | "ArrowRight" => Store.dispatch(Actions.GoRight)
  | "Space" => onSpace(Store.store.state.ship)
  | _ => ()
  };

let render = (canvasContext: Types.canvasContext, state: Types.shipState) =>
  switch state.potentialShipSprite {
  | Some(sprite) => Image.draw(canvasContext, sprite, ~x=state.x, ~y=state.y)
  | None => ()
  };