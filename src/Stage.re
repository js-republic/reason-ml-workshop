open Store;

open Types;

open Webapi.Dom;

let goTo = (stage: stageType) => {
  switch store.stage {
  | Some(stage) => stage.willDestroy()
  | _ => ()
  };
  stage.willMount();
  store.stage = Some(stage);
};

let inGame: stageType = {
  willMount: () => {
    Document.addKeyUpEventListener(Ship.onKeyUp, document);
    dispatch(Actions.ResetInGame);
  },
  render: (ctx, state) => {
    Bg.renderInGame(ctx, state.screen);
    state.shot.shots |> List.iter(Shot.render(ctx));
    state.alien.aliens |> List.iter(Alien.render(ctx));
    Ship.render(ctx, state.ship);
  },
  willDestroy: () => Document.removeKeyUpEventListener(Ship.onKeyUp, document)
};

let start: stageType = {
  willMount: () => {
    let rec onClick = (_) => {
      goTo(inGame);
      Document.removeClickEventListener(onClick, document);
    };
    Document.addClickEventListener(onClick, document);
  },
  render: (ctx, state) => Bg.renderStartStage(ctx, state.screen),
  willDestroy: () => ()
};