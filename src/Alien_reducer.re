open Types;

let reducer =
    (elapsedTime: float, state: alienState, action: Actions.all)
    : alienState => {
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
  | _ => state
  };
};