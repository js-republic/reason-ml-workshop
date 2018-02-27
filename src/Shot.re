let willMount = () => ();

let willDestroy = () => ();

let render = (ctx, state: Types.shot) => {
  Js.log(string_of_float(state.x) ++ "::" ++ string_of_float(state.y));
  switch state.potentialSprite {
  | Some(img) =>
    HtmlImage.drawImage(img, int_of_float(state.x), int_of_float(state.y), ctx)
  | _ => ()
  };
};