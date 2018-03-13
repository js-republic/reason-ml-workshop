let shotSpeed = 0.3;

let stillInTheScreen = (shot: Types.shot) : bool => true;

let moveShot = (elapsedTime: float, shot: Types.shot) : Types.shot => shot;

let moveShots = (elapsedTime: float, shots: list(Types.shot)) : list(Types.shot) => shots;

let reducer = (elapsedTime: float, state: Types.shotState, action: Actions.all) : Types.shotState =>
  switch action {
  | _ => state
  };