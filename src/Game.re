open Store;

type canvasContext = Webapi.Canvas.Canvas2d.t;

let rec onFrame = (ctx: canvasContext, elapsedTime: float) => {
  let reducer = store.reducer(elapsedTime);
  store.state = store.actionsToReduce |> List.fold_left(reducer, store.state);
  store.actionsToReduce = [];
  store.stage.renderers |> List.iter(render => render(ctx, store.state));
  Webapi.requestAnimationFrame(onFrame(ctx));
  ();
};

let run = (ctx: canvasContext) : unit =>
  Webapi.requestAnimationFrame(onFrame(ctx));