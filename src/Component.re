module type t = {
  let willMount: unit => unit;
  let willDestroy: unit => unit;
  let apply: State.rootStateType => State.rootStateType;
  let render: (Webapi.Canvas.Canvas2d.t, State.rootStateType) => unit;
};