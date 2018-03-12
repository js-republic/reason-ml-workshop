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
  | Fire(coord) => {
      ...state,
      shots: state.shots @ [{...state.itemModel, y: coord.y +. 5., x: coord.x}]
    }
  | Tick => {...state, shots: tickShots(state.shots, elapsedTime)}
  | _ => state
  };