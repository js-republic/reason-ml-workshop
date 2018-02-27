open Types;

/*willMount: (Types.rootState) => (),*/
type storeType('state) = {
  mutable actions: list(Actions.all),
  mutable reducer: ('state, Actions.all) => 'state,
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
      items: []
    },
    alien: {
      itemModel: {
        potentialSprite: None,
        width: 30.,
        height: 30.,
        x: 0.,
        y: 0.
      },
      items: []
    }
  },
  stage: None
};

let applyReducers = () : unit => {
  store.state =
    store.actions
    |> List.fold_left(
         (state, action) => {
           ...store.reducer(state, action),
           shot: Shot.reducer(state.shot, action),
           alien: Alien.reducer(state.alien, action)
         },
         store.state
       );
  store.actions = [];
  ();
};

let dispatch = (action: Actions.all) : unit =>
  store.actions = store.actions @ [action];