[@bs.scope "Math"] [@bs.val] external max : (float, float) => float = "max";

[@bs.scope "Math"] [@bs.val] external min : (float, float) => float = "min";

open Constants;

let reducer =
    (elapsedTime: float, state: Types.shipState, action: Actions.all)
    : Types.shipState =>
  switch action {
  | ShipImageLoaded(img) => {...state, potentialSprite: Some(img)}
  | _ => state
  };