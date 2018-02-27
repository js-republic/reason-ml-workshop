open Types;

/*willMount: (Types.rootState) => (),*/
type storeType('state) = {
  mutable actions: list(Actions.all),
  mutable reducer: (float, 'state, Actions.all) => 'state,
  mutable state: 'state,
  mutable stage: option(stageType)
};

let store: storeType(rootState) = {
  reducer: Reducer.main,
  actions: [],
  state: {
    screen: {
      height: 400.,
      width: 600.,
      potentialBg: None
    },
    ship: {
      potentialSprite: None,
      potentialShotImg: None,
      xPos: 0,
      height: 62.,
      width: 60.
    },
    shots: {
      itemModel: {
        potentialSprite: None,
        width: 8.,
        height: 30.,
        x: 0.,
        y: 0.
      },
      items: []
    },
    alien: {
      potentialSprite: None
    }
  },
  stage: None
};

let applyReducer = (elapsedTime: float) : unit => {
  store.state =
    store.actions |> List.fold_left(store.reducer(elapsedTime), store.state);
  store.actions = [];
  ();
};

let dispatch = (action: Actions.all) : unit =>
  store.actions = store.actions @ [action];