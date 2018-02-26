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

type alienState = {potentialSprite: option(HtmlImage.t)};

type render('a) = (Webapi.Canvas.Canvas2d.t, 'a) => unit;

type stage('b) = {renderers: list(render('b))};

type rootState = {
  mutable screen: screenState,
  mutable ship: shipState,
  mutable alien: alienState
};