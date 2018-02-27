open Types;

let tickShots = (shots: list(shot), elapsedTime: float) : list(shot) =>
  shots
  |> List.map((i: shot) => ({...i, y: i.y -. elapsedTime *. 0.5}: shot))
  |> List.filter((i: shot) => i.y > 0.);

let reducer = (state: shotState, action: Actions.all) : shotState =>
  switch action {
  | ClearInGameState => {...state, items: []}
  | Tick(elapsedTime) => {...state, items: tickShots(state.items, elapsedTime)}
  | Shot(x, y) => {...state, items: state.items @ [{...state.itemModel, x, y}]}
  | _ => state
  };

let render = (ctx, state: shot) => {
  Js.log(string_of_float(state.x) ++ "::" ++ string_of_float(state.y));
  switch state.potentialSprite {
  | Some(img) =>
    HtmlImage.drawImage(img, int_of_float(state.x), int_of_float(state.y), ctx)
  | _ => ()
  };
};