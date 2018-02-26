let onKeyDown = (event: Dom.event) : unit => Js.log(event);

let willMount = () => ();

let willDestroy = () => ();

let renderShip = (sprite, ctx, state: State.rootStateType) => {
  let y = int_of_float(state.screen.height -. state.ship.height);
  HtmlImage.drawImage(sprite, state.ship.xPos, y, ctx);
  ();
};

let render = (ctx, state: State.rootStateType) =>
  switch state.ship.potentialSprite {
  | Some(sprite) => renderShip(sprite, ctx, state)
  | None => ()
  };

let apply = x => x;