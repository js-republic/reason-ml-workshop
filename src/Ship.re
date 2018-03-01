let onSpace = (state: Types.rootState) => {
  let y = state.screen.height -. state.ship.height;
  let x = state.ship.x +. state.ship.width /. 2.;
  Store.dispatch(Actions.Shot(x, y));
};

let onKeyUp = (event: Dom.keyboardEvent) : unit =>
  switch (Webapi.Dom.KeyboardEvent.code(event)) {
  | "ArrowLeft" => Store.dispatch(Actions.GoLeft)
  | "ArrowRight" => Store.dispatch(Actions.GoRight)
  | "Space" => onSpace(Store.store.state)
  | _ => ()
  };

let render = (ctx, state: Types.shipState) =>
  switch state.potentialSprite {
  | Some(sprite) =>
    ctx
    |> HtmlImage.drawImage(
         sprite,
         int_of_float(state.x),
         int_of_float(state.y)
       );
    ();
  | None => ()
  };