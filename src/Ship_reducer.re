[@bs.scope "Math"] [@bs.val] external max : (float, float) => float = "max";

[@bs.scope "Math"] [@bs.val] external min : (float, float) => float = "min";

let reducer =
    (elapsedTime: float, state: Types.shipState, action: Actions.all)
    : Types.shipState =>
  switch action {
  | ShipImageLoaded(img) => {...state, potentialSprite: Some(img)}
  | GoLeft => {...state, x: max(0., state.x -. elapsedTime *. 0.5)}
  | GoRight => {
      ...state,
      x: min(Constants.height -. state.width, state.x +. elapsedTime *. 0.5)
    }
  | _ => state
  };