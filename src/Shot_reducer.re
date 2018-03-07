let tickShots =
    (shots: list(Types.shot), elapsedTime: float)
    : list(Types.shot) =>
  shots
  |> List.map((i: Types.shot) =>
       ({...i, y: i.y -. elapsedTime *. 0.5}: Types.shot)
     )
  |> List.filter((i: Types.shot) => i.y > 0.);

let reducer =
    (elapsedTime: float, state: Types.shotState, action: Actions.all)
    : Types.shotState =>
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
        |> List.map((shot: Types.shot) =>
             ({...shot, y: shot.y -. 5.}: Types.shot)
           )
    }
  | ResetInGame => {...state, shots: []}
  | Tick => {...state, shots: tickShots(state.shots, elapsedTime)}
  | Fire(x, y) => {...state, shots: state.shots @ [{...state.itemModel, x, y}]}
  | _ => state
  };