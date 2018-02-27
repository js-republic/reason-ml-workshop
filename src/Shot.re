open Types;

let willMount = () => ();

let willDestroy = () => ();

let shotsReducer =
    (elapsedTime: float, state: shotsState, action: Actions.all)
    : shotsState =>
  switch action {
  | Tick =>
    let items: list(shot) =
      state.items
      |> List.map(i => {...i, y: i.y -. elapsedTime *. 0.5})
      |> List.filter(i => i.y > 0.);
    {...state, items};
  | Shot(xPos, yPos) => {
      ...state,
      items: state.items @ [{...state.itemModel, x: xPos, y: yPos}]
    }
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