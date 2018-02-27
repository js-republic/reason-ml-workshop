type screenState = {
  height: float,
  width: float,
  potentialBg: option(HtmlImage.t)
};

type shipState = {
  potentialSprite: option(HtmlImage.t),
  potentialShotImg: option(HtmlImage.t),
  x: float,
  y: float,
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

type alien = {
  x: float,
  y: float,
  potentialSprite: option(HtmlImage.t),
  width: float,
  height: float
};

type alienState = {
  itemModel: alien,
  items: list(alien)
};

type rootState = {
  screen: screenState,
  ship: shipState,
  alien: alienState,
  shot: shotState
};

type stageType = {
  willMount: rootState => unit,
  render: (Webapi.Canvas.Canvas2d.t, rootState) => unit,
  willDestroy: rootState => unit
};