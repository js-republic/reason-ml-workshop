/**
 * This function can be used to return the greater float between two. It's a direct
 * binding to the `Math.max` function existing in JavaScript.
 *
 * Example : let greater = max(1, 5); /* 5 */
 *
 * @param {float} A first float
 * @param {float} A second float
 * @return {float} The greater of the two given in input
 */
[@bs.scope "Math"]
[@bs.val]
external max : (float, float) => float = "max";

/**
 * This function can be used to return the smallest float between two. It's a direct
 * binding to the `Math.max` function existing in JavaScript.
 *
 * Example : let smallest = max(1, 5); /* 1 */
 *
 * @param {float} A first float
 * @param {float} A second float
 * @return {float} The smallest of the two given in input
 */
[@bs.scope "Math"]
[@bs.val]
external min : (float, float) => float = "min";

let shipSpeed = 0.5;

let reducer =
    (elapsedTime: float, state: Types.shipState, action: Actions.all)
    : Types.shipState =>
  switch action {
  | GoLeft => {...state, x: max(0., state.x -. elapsedTime *. shipSpeed)}
  | GoRight => {
      ...state,
      x:
        min(
          Constants.width -. state.width,
          state.x +. elapsedTime *. shipSpeed
        )
    }
  | _ => state
  };