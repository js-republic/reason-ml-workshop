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

type reducer('a) = ('a, float) => 'a;

type stage('a, 'b) = {
  reducers: list(reducer('a)),
  renderers: list(render('b))
};

type rootState = {
  mutable screen: screenState,
  mutable currentStage: stage(rootState, rootState),
  mutable ship: shipState,
  mutable alien: alienState
};