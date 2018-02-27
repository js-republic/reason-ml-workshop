let onKeyDown = (state: Types.rootState, _) => {
  let y = state.screen.height -. state.ship.height;
  let x = float_of_int(state.ship.xPos) +. state.ship.width /. 2.;
  Store.dispatch(Actions.Shot(x, y));
};

let render = (ctx, state: Types.rootState) =>
  switch state.ship.potentialSprite {
  | Some(sprite) =>
    let y = int_of_float(state.screen.height -. state.ship.height);
    HtmlImage.drawImage(sprite, state.ship.xPos, y, ctx);
    ();
  | None => ()
  };