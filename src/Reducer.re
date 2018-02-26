open Actions;

let mainReducer =
    (_: float, state: Types.rootState, action: bootstrapAction)
    : Types.rootState =>
  switch action {
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
      ship: {
        ...state.ship,
        potentialShotImg: Some(img)
      }
    }
  };