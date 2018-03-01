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
      x: 0.,
      y: 400. -. 62.,
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
        width: 30.,
        height: 30.,
        x: 30.,
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
        ...store.reducer(elapsedTime, state, action),
        shot: Shot_reducer.reducer(elapsedTime, state.shot, action),
        alien: Alien_reducer.reducer(elapsedTime, state.alien, action),
        ship: Ship_reducer.reducer(elapsedTime, state.ship, action)
      },
      store.state,
      store.actions
    );
  store.actions = [];
  ();
};

let dispatch = (action: Actions.all) : unit =>
  store.actions = store.actions @ [action];