open Store;

open Types;

open Webapi.Dom;

let goTo = (stage: stageType) => {
  switch store.stage {
  | Some(stage) => stage.willDestroy(store.state)
  | _ => ()
  };
  stage.willMount(store.state);
  store.stage = Some(stage);
};

let inGame: stageType = {
  willMount: state => {
    document |> Document.addEventListener("keydown", Ship.onKeyDown(state));
    dispatch(Actions.ClearInGameState);
  },
  render: (ctx, state) => {
    InGameBg.render(ctx, state.screen);
    Ship.render(ctx, state.ship);
    state.shot.items |> List.iter(Shot.render(ctx));
    state.alien.items |> List.iter(Alien.render(ctx));
  },
  willDestroy: state =>
    document |> Document.removeEventListener("keydown", Ship.onKeyDown(state))
};

let start: stageType = {
  willMount: (_) => {
    let rec onClick = (_) => {
      goTo(inGame);
      Document.removeEventListener("click", onClick, document);
    };
    Document.addEventListener("click", onClick, document);
  },
  render: (ctx, state) => StartBg.render(ctx, state.screen),
  willDestroy: (_) => ()
};