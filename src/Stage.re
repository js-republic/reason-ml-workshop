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
    dispatch(Actions.ResetInGame);
  },
  render: (ctx, state) => {
    Bg.renderInGame(ctx, state.screen);
    Ship.render(ctx, state.ship);
    state.shot.shots |> List.iter(Shot.render(ctx));
    state.alien.aliens |> List.iter(Alien.render(ctx));
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
  render: (ctx, state) => Bg.renderStartStage(ctx, state.screen),
  willDestroy: (_) => ()
};