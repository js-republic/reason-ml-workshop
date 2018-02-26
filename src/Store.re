open Types;

let startState: stage(rootState, rootState) = {
  reducers: [Ship.reducer],
  renderers: [InGameStage.render, Ship.render]
};

let inGameState: stage(rootState, rootState) = {reducers: [], renderers: []};

let endState: stage(rootState, rootState) = {reducers: [], renderers: []};

type storeType('state) = {mutable state: 'state};

let store: storeType(rootState) = {
  state: {
    screen: {
      height: 400.,
      width: 600.,
      potentialBg: None
    },
    currentStage: startState,
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