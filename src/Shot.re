open Types;

let tickShots = (shots: list(shot), elapsedTime: float) : list(shot) =>
  shots
  |> List.map((i: shot) => ({...i, y: i.y -. elapsedTime *. 0.5}: shot))
  |> List.filter((i: shot) => i.y > 0.);

let reducer = (state: shotState, action: Actions.all) : shotState =>
  switch action {
  | ShotImageLoaded(img) => {
      ...state,
      itemModel: {
        ...state.itemModel,
        potentialSprite: Some(img)
      }
    }
  | ResetInGame => {...state, shots: []}
  | Tick(elapsedTime) => {...state, shots: tickShots(state.shots, elapsedTime)}
  | Shot(x, y) => {...state, shots: state.shots @ [{...state.itemModel, x, y}]}
  | _ => state
  };

let render = (ctx, state: shot) =>
  switch state.potentialSprite {
  | Some(img) =>
    HtmlImage.drawImage(img, int_of_float(state.x), int_of_float(state.y), ctx)
  | _ => ()
  };