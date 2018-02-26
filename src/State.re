type screenState = {
  height: float,
  width: float,
  potentialBg: option(HtmlImage.t)
};

type stage =
  | StartState
  | InGameState
  | EndState;

type shipState = {
  potentialSprite: option(HtmlImage.t),
  potentialShotImg: option(HtmlImage.t),
  xPos: int,
  height: float,
  width: float
};

type alienState = {potentialSprite: option(HtmlImage.t)};

type rootStateType = {
  mutable screen: screenState,
  mutable currentStage: stage,
  mutable ship: shipState,
  mutable alien: alienState
};

let initialRootState: rootStateType = {
  screen: {
    height: 400.,
    width: 600.,
    potentialBg: None
  },
  currentStage: StartState,
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
};

let rootState = initialRootState;