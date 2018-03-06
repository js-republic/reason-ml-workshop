open Types;

let tickShots = (shots: list(shot), elapsedTime: float) : list(shot) =>
  shots
  |> List.map((i: shot) => ({...i, y: i.y -. elapsedTime *. 0.5}: shot))
  |> List.filter((i: shot) => i.y > 0.);

let reducer =
    (elapsedTime: float, state: shotState, action: Actions.all)
    : shotState =>
  switch action {
  | ShotImageLoaded(img) => {
      ...state,
      itemModel: {
        ...state.itemModel,
        potentialSprite: Some(img)
      }
    }
  | Fire(x, y) => {
      ...state,
      shots: state.shots @ [{...state.itemModel, y: y +. 5., x}]
    }
  | Tick => {
      ...state,
      shots:
        state.shots
        |> List.map((shot: shot) => ({...shot, y: shot.y -. 5.}: shot))
    }
  | ResetInGame => {...state, shots: []}
  | Tick => {...state, shots: tickShots(state.shots, elapsedTime)}
  | Fire(x, y) => {...state, shots: state.shots @ [{...state.itemModel, x, y}]}
  | _ => state
  };