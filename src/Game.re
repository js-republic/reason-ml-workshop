open Store;

type canvasContext = Webapi.Canvas.Canvas2d.t;

let rec onFrame = (ctx: canvasContext, elapsedTime: float) => {
  applyReducer(elapsedTime);
  switch store.stage {
  | Some(stage) => stage.render(ctx, store.state)
  | _ => ()
  };
  Webapi.requestAnimationFrame(onFrame(ctx));
  ();
};

let run = (ctx: canvasContext) : unit => {
  Stage.goTo(Stage.inGame);
  Webapi.requestAnimationFrame(onFrame(ctx));
};