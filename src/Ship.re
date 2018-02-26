let onKeyDown = (event: Dom.event) : unit => Js.log(event);

let willMount = () => ();

let willDestroy = () => ();

let render = (ctx, state: Types.rootState) =>
  switch state.ship.potentialSprite {
  | Some(sprite) =>
    let y = int_of_float(state.screen.height -. state.ship.height);
    HtmlImage.drawImage(sprite, state.ship.xPos, y, ctx);
    ();
  | None => ()
  };

let reducer = (x, y) => x;