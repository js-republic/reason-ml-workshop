open Store;

open Types;

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
    Webapi.Dom.document
    |> Webapi.Dom.Document.addEventListener("keydown", Ship.onKeyDown(state));
    dispatch(Actions.ClearInGameState);
  },
  render: (ctx, state) => {
    InGameBg.render(ctx, state.screen);
    Ship.render(ctx, state);
    state.shots.items |> List.iter(Shot.render(ctx));
  },
  willDestroy: state => {
    Webapi.Dom.document
    |> Webapi.Dom.Document.addEventListener("keydown", Ship.onKeyDown(state));
    dispatch(Actions.ClearInGameState);
  }
};

let start: stageType = {
  willMount: (_) => {
    let rec onClick = (_) => {
      goTo(inGame);
      Webapi.Dom.Document.removeEventListener(
        "click",
        onClick,
        Webapi.Dom.document
      );
    };
    Webapi.Dom.Document.addEventListener(
      "click",
      onClick,
      Webapi.Dom.document
    );
  },
  render: (ctx, state) => StartBg.render(ctx, state.screen),
  willDestroy: (_) => ()
};