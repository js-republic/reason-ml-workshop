let shotSpeed = 0.3;

let stillInTheScreen = (shot: Types.shot) : bool => shot.y > 0.;

let moveShot = (elapsedTime: float, shot: Types.shot) : Types.shot => {
  ...shot,
  y: shot.y -. elapsedTime *. shotSpeed
};

let moveShots = (elapsedTime: float, shots: list(Types.shot)) : list(Types.shot) =>
  shots |> List.map(moveShot(elapsedTime)) |> List.filter(stillInTheScreen);

let reducer = (elapsedTime: float, state: Types.shotState, action: Actions.all) : Types.shotState =>
  switch action {
  | Tick => {...state, shots: state.shots |> moveShots(elapsedTime)}
  | _ => state
  };