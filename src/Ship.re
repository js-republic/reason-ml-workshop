let onKeyDown = (state: Types.rootState, _) => {
  let y = state.screen.height -. state.ship.height;
  let x = state.ship.x +. state.ship.width /. 2.;
  Store.dispatch(Actions.Shot(x, y));
};

let render = (ctx, state: Types.shipState) =>
  switch state.potentialSprite {
  | Some(sprite) =>
    HtmlImage.drawImage(
      sprite,
      int_of_float(state.x),
      int_of_float(state.y),
      ctx
    );
    ();
  | None => ()
  };