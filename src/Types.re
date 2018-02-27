type screenState = {
  height: float,
  width: float,
  potentialBg: option(HtmlImage.t)
};

type shipState = {
  potentialSprite: option(HtmlImage.t),
  potentialShotImg: option(HtmlImage.t),
  xPos: int,
  height: float,
  width: float
};

type shot = {
  x: float,
  y: float,
  potentialSprite: option(HtmlImage.t),
  width: float,
  height: float
};

type shotState = {
  itemModel: shot,
  items: list(shot)
};

type alienState = {potentialSprite: option(HtmlImage.t)};

type rootState = {
  screen: screenState,
  ship: shipState,
  alien: alienState,
  shots: shotState
};

type stageType = {
  willMount: rootState => unit,
  render: (Webapi.Canvas.Canvas2d.t, rootState) => unit,
  willDestroy: rootState => unit
};