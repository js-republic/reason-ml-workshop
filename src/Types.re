type canvasContext = Webapi.Canvas.Canvas2d.t;

type image;

type coordinate = {
  x: float,
  y: float
};

type screenState = {
  height: float,
  width: float,
  potentialBg: option(image)
};

type shipState = {
  potentialShipSprite: option(image),
  x: float,
  y: float,
  height: float,
  width: float
};

type shot = {
  x: float,
  y: float,
  potentialSprite: option(image),
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
  potentialSprite: option(image),
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
  willMount: unit => unit,
  render: (canvasContext, rootState) => unit,
  willDestroy: unit => unit
};