module type t = {
  let willMount: unit => unit;
  let willDestroy: unit => unit;
  let reducer: Types.reducer(Types.rootState);
  let render: Types.render(Types.rootState);
};