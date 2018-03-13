let alienSpeed = 0.3;

let nextX = (elapsedTime: float, a: Types.alien) : float => 0.;

let isOnEdge = (newX: float, alien: Types.alien) : (bool, bool) => (true, true);

let alienStep = 70.;

let moveOnLeftEdge = (a: Types.alien) : Types.alien => a;

let moveOnRightEdge = (a: Types.alien) : Types.alien => a;

let moveAlien = (elapsedTime: float, a: Types.alien) : Types.alien => a;

let isStillInMap = (alien: Types.alien) => alien.y < Constants.height;

let moveAliens = (elapsedTime: float, aliens: list(Types.alien)) : list(Types.alien) => aliens;

let reducer = (elapsedTime: float, state: Types.alienState, action: Actions.all) : Types.alienState =>
  switch action {
  | Tick => {...state, aliens: moveAliens(elapsedTime, state.aliens)}
  | _ => state
  };