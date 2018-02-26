module type t = {
  let willMount: unit => unit;
  let willDestroy: unit => unit;
  let render: Types.render(Types.rootState);
};