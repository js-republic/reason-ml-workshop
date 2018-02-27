let mainReducer =
    (_: float, state: Types.rootState, action: Actions.all)
    : Types.rootState =>
  switch action {
  | ClearInGameState => {
      ...state,
      shots: {
        ...state.shots,
        items: []
      }
    }
  | ShipImageLoaded(img) => {
      ...state,
      ship: {
        ...state.ship,
        potentialSprite: Some(img)
      }
    }
  | BgImageLoaded(img) => {
      ...state,
      screen: {
        ...state.screen,
        potentialBg: Some(img)
      }
    }
  | AlienImageLoaded(img) => {
      ...state,
      alien: {
        potentialSprite: Some(img)
      }
    }
  | ShotImageLoaded(img) => {
      ...state,
      shots: {
        ...state.shots,
        itemModel: {
          ...state.shots.itemModel,
          potentialSprite: Some(img)
        }
      }
    }
  | Tick =>
    let shots = state.shots.items;
    {
      ...state,
      shots: {
        ...state.shots,
        items: shots
      }
    };
  | Shot(xPos) =>
    let model = state.shots.itemModel;
    {
      ...state,
      shots: {
        ...state.shots,
        items: state.shots.items @ [{...model, x: xPos, y: 30.}]
      }
    };
  };