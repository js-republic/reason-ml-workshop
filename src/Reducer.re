open Types;

let main = (state: rootState, action: Actions.all) : rootState =>
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
  | _ => state
  };