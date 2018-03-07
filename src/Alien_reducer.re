let moveAlien = (elapsedTime: float, a: Types.alien) : Types.alien => {
  let x = a.x +. elapsedTime *. 0.3 *. float_of_int(a.direction);
  switch (x > 0., x +. a.width < Constants.width) {
  | (true, true) => {...a, x}
  | (false, _) => {...a, x: 0., y: a.y +. 70., direction: a.direction * (-1)}
  | (_, false) => {
      ...a,
      x: Constants.width -. a.width,
      y: a.y +. 70.,
      direction: a.direction * (-1)
    }
  };
};

let moveAliens =
    (aliens: list(Types.alien), elapsedTime: float)
    : list(Types.alien) =>
  aliens
  |> List.map(moveAlien(elapsedTime))
  |> List.filter((a: Types.alien) => a.y < Constants.height);

let reducer =
    (elapsedTime: float, state: Types.alienState, action: Actions.all)
    : Types.alienState => {
  let now = Js.Date.now();
  switch action {
  | AlienImageLoaded(img) => {
      ...state,
      itemModel: {
        ...state.itemModel,
        potentialSprite: Some(img)
      }
    }
  | ResetInGame => {...state, lastSpawn: now}
  | Tick =>
    let hasToRespawn = now -. state.lastSpawn > 500.;
    let aliens =
      moveAliens(
        hasToRespawn ? state.aliens @ [state.itemModel] : state.aliens,
        elapsedTime
      );
    {...state, lastSpawn: hasToRespawn ? now : state.lastSpawn, aliens};
  | _ => state
  };
};