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

let onSpace = () => {};

let onKeyDownWrapper = (event: Dom.keyboardEvent) =>
  switch (Webapi.Dom.KeyboardEvent.code(event)) {
  | keyCode => Ship.onKeyDown(keyCode)
  };

let onKeyUpWrapper = (event: Dom.keyboardEvent) =>
  switch (Webapi.Dom.KeyboardEvent.code(event)) {
  | "Space" =>
    let shipState = store.state.ship;
    let y = Constants.height -. shipState.height;
    let x = shipState.x +. shipState.width /. 2. -. store.state.shot.itemModel.width /. 2.;
    dispatch(Actions.Fire({x, y}));
  | _ => ()
  };

let inGame: stageType = {
  willMount: () => {
    Document.addKeyUpEventListener(onKeyUpWrapper, document);
    Document.addKeyDownEventListener(onKeyDownWrapper, document);
    dispatch(Actions.ResetInGame);
  },
  render: (ctx, state) => {
    Bg.renderInGame(ctx, state.screen);
    state.shot.shots |> List.iter(Shot.render(ctx));
    state.alien.aliens |> List.iter(Alien.render(ctx));
    Ship.render(ctx, state.ship);
  },
  willDestroy: () => {
    Document.removeKeyUpEventListener(onKeyUpWrapper, document);
    Document.addKeyDownEventListener(onKeyDownWrapper, document);
  }
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