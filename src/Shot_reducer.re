open Types;

let reducer =
    (elapsedTime: float, state: shotState, action: Actions.all)
    : shotState =>
  switch action {
  | ShotImageLoaded(img) => {
      ...state,
      itemModel: {
        ...state.itemModel,
        potentialSprite: Some(img)
      }
    }
  | ResetInGame => {...state, shots: []}
  | _ => state
  };