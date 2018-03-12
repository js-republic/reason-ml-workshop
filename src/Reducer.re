let pre = (_, state: Types.rootState, action: Actions.all) : Types.rootState =>
  switch action {
  | Tick =>
    let (aliens, shots) =
      Colision.findNotCollided(state.alien.aliens, state.shot.shots);
    {
      ...state,
      shot: {
        ...state.shot,
        shots
      },
      alien: {
        ...state.alien,
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
  | Fire(coord) => {
      ...state,
      shot: {
        ...state.shot,
        shots:
          state.shot.shots
          @ [{...state.shot.itemModel, y: coord.y, x: coord.x}]
      }
    }
  | ResetInGame => {
      ...state,
      shot: {
        ...state.shot,
        shots: []
      }
    }
  | _ => state
  };

let post = (_, state: Types.rootState, _) : Types.rootState => state;