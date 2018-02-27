open Types;

let main =
    (elapsedTime: float, state: rootState, action: Actions.all)
    : rootState =>
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