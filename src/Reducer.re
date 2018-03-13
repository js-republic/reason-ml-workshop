let pre = (_, state: Types.rootState, action: Actions.all) : Types.rootState => {
  let now = Js.Date.now();
  switch action {
  | ResetInGame => {
      ...state,
      shot: {
        ...state.shot,
        shots: []
      },
      alien: {
        ...state.alien,
        lastSpawn: now
      }
    }
  | Tick =>
    let hasToRespawn = now -. state.alien.lastSpawn > 500.;
    let aliens = hasToRespawn ? state.alien.aliens @ [state.alien.itemModel] : state.alien.aliens;
    let (aliens, shots) = Colision.findNotCollided(aliens, state.shot.shots);
    {
      ...state,
      shot: {
        ...state.shot,
        shots
      },
      alien: {
        ...state.alien,
        lastSpawn: hasToRespawn ? now : state.alien.lastSpawn,
        aliens
      }
    };
  | BgImageLoaded(img) => {
      ...state,
      screen: {
        ...state.screen,
        potentialBg: Some(img)
      }
    }
  | ShipImageLoaded(img) => {
      ...state,
      ship: {
        ...state.ship,
        potentialShipSprite: Some(img)
      }
    }
  | ShotImageLoaded(img) => {
      ...state,
      shot: {
        ...state.shot,
        itemModel: {
          ...state.shot.itemModel,
          potentialSprite: Some(img)
        }
      }
    }
  | AlienImageLoaded(img) => {
      ...state,
      alien: {
        ...state.alien,
        itemModel: {
          ...state.alien.itemModel,
          potentialSprite: Some(img)
        }
      }
    }
  | Fire(coord) => {
      ...state,
      shot: {
        ...state.shot,
        shots: state.shot.shots @ [{...state.shot.itemModel, y: coord.y, x: coord.x}]
      }
    }
  | _ => state
  };
};

let post = (_, state: Types.rootState, _) : Types.rootState => state;