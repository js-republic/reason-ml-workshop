open Store;

type canvasContext = Webapi.Canvas.Canvas2d.t;

let rec onFrame = (ctx: canvasContext, lastTime: float, newTime: float) => {
  dispatch(Actions.Tick(newTime -. lastTime));
  applyReducers();
  switch store.stage {
  | Some(stage) => stage.render(ctx, store.state)
  | _ => ()
  };
  Webapi.requestAnimationFrame(onFrame(ctx, newTime));
  ();
};

let run = (ctx: canvasContext) : unit => {
  Stage.goTo(Stage.inGame);
  Webapi.requestAnimationFrame(onFrame(ctx, 0.));
};