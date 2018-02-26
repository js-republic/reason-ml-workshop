open Types;

open Actions;

let startStage: stage(rootState) = {renderers: []};

let inGameStage: stage(rootState) = {
  renderers: [InGameStage.render, Ship.render]
};

let endStage: stage(rootState) = {renderers: []};

type storeType('state) = {
  mutable actionsToReduce: list(bootstrapAction),
  mutable reducer: (float, 'state, bootstrapAction) => 'state,
  mutable stage: stage('state),
  mutable state: 'state
};

let store: storeType(rootState) = {
  stage: inGameStage,
  reducer: Reducer.mainReducer,
  actionsToReduce: [],
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
    alien: {
      potentialSprite: None
    }
  }
};

let dispatch = (action: bootstrapAction) =>
  store.actionsToReduce = store.actionsToReduce @ [action];