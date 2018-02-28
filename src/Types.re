type screenState = {
  height: float,
  width: float,
  potentialBg: option(HtmlImage.t)
};

type shipState = {
  potentialSprite: option(HtmlImage.t),
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
  shots: list(shot)
};

type alien = {
  x: float,
  y: float,
  potentialSprite: option(HtmlImage.t),
  width: float,
  height: float,
  direction: int
};

type alienState = {
  itemModel: alien,
  lastSpawn: float,
  aliens: list(alien)
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