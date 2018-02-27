open Store;

open Types;

let start: stageType = {
  willMount: (_) => (),
  render: (ctx, state) => StartBg.render(ctx, state.screen),
  willDestroy: (_) => ()
};

let inGame: stageType = {
  willMount: (_) => dispatch(Actions.ClearInGameState),
  render: (ctx, state) => {
    InGameBg.render(ctx, state.screen);
    Ship.render(ctx, state);
    state.shots.items |> List.iter(Shot.render(ctx));
  },
  willDestroy: (_) => ()
};

let goTo = (stage: stageType) => {
  switch store.stage {
  | Some(stage) => stage.willDestroy(store.state)
  | _ => ()
  };
  stage.willMount(store.state);
  store.stage = Some(stage);
};