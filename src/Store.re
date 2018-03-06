open Types;

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
      height: Constants.height,
      width: Constants.width,
      potentialBg: None
    },
    ship: {
      potentialSprite: None,
      x: Constants.width /. 2. -. 30.,
      y: Constants.height -. 62.,
      height: 62.,
      width: 60.
    },
    shot: {
      itemModel: {
        potentialSprite: None,
        width: 8.,
        height: 30.,
        x: 0.,
        y: 0.
      },
      shots: []
    },
    alien: {
      itemModel: {
        potentialSprite: None,
        width: 64.,
        height: 64.,
        x: 0.,
        y: 0.,
        direction: 1
      },
      lastSpawn: 0.,
      aliens: []
    }
  },
  stage: None
};

let applyReducers = (elapsedTime: float) : unit => {
  store.state =
    List.fold_left(
      (state, action) => {
        let root = store.reducer(elapsedTime, state, action);
        {
          screen: root.screen,
          shot: Shot_reducer.reducer(elapsedTime, root.shot, action),
          alien: Alien_reducer.reducer(elapsedTime, root.alien, action),
          ship: Ship_reducer.reducer(elapsedTime, root.ship, action)
        };
      },
      store.state,
      store.actions
    );
  store.actions = [];
  ();
};

let dispatch = (action: Actions.all) : unit =>
  store.actions = store.actions @ [action];