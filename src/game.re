open State;

open Actions;

type canvasContext = Webapi.Canvas.Canvas2d.t;

let renderInGameStage = (ctx: canvasContext, state: State.rootStateType) => {
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
    rootState.ship = {...rootState.ship, potentialSprite: Some(img)}
  | BgImageLoaded(img) =>
    rootState.screen = {...rootState.screen, potentialBg: Some(img)}
  | AlienImageLoaded(img) => rootState.alien = {potentialSprite: Some(img)}
  | ShotImageLoaded(img) =>
    rootState.ship = {...rootState.ship, potentialShotImg: Some(img)}
  };

let rec onFrame = (ctx: canvasContext, state: rootStateType, _: float) => {
  switch state.currentStage {
  | _ => renderInGameStage(ctx, state)
  };
  Webapi.requestAnimationFrame(onFrame(ctx, rootState));
  ();
};

let run = (ctx: canvasContext) : unit =>
  Webapi.requestAnimationFrame(onFrame(ctx, rootState));