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
  | _ => state
  };
/*| Tick =>
    let newShotItems: list(shot) =
      state.shots.items
      |> List.map(i => {...i, y: i.y -. elapsedTime *. 0.5})
      |> List.filter(i => i.y > 0.);
    {
      ...state,
      shots: {
        ...state.shots,
        items: newShotItems
      }
    };
  | Shot(xPos, yPos) =>
    Js.log(state.shots.items |> List.length);
    {
      ...state,
      shots: {
        ...state.shots,
        items:
          state.shots.items @ [{...state.shots.itemModel, x: xPos, y: yPos}]
      }
    };*/