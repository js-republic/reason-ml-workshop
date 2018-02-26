open Store;

open Actions;

type canvasContext = Webapi.Canvas.Canvas2d.t;

let renderInGameStage = (ctx: canvasContext, state: Types.rootState) => {
  InGameStage.render(ctx, state);
  Ship.render(ctx, state);
  ();
};

/*
 goToState(ctx, images, InGameState);*/
let dispatch = (action: bootstrapAction) =>
  /* TODO: Call each reducer ! */
  switch action {
  | ShipImageLoaded(img) =>
    store.state.ship = {...store.state.ship, potentialSprite: Some(img)}
  | BgImageLoaded(img) =>
    store.state.screen = {...store.state.screen, potentialBg: Some(img)}
  | AlienImageLoaded(img) => store.state.alien = {potentialSprite: Some(img)}
  | ShotImageLoaded(img) =>
    store.state.ship = {...store.state.ship, potentialShotImg: Some(img)}
  };

let rec onFrame = (ctx: canvasContext, elapsedTime: float) => {
  store.state.currentStage.renderers
  |> List.iter(render => render(ctx, store.state));
  Webapi.requestAnimationFrame(onFrame(ctx));
  ();
};

let run = (ctx: canvasContext) : unit =>
  Webapi.requestAnimationFrame(onFrame(ctx));