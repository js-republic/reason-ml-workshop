/* record gameImage*/
type t;

exception ImageNotFound(string);

[@bs.send.pipe : Webapi.Canvas.Canvas2d.t]
external drawImage : (t, ~x: float, ~y: float) => unit = "";

[@bs.new] external makeImage : unit => t = "Image";

[@bs.set] external setSrc : (t, string) => unit = "src";

[@bs.set] external setOnload : (t, unit => unit) => unit = "onload";

[@bs.set] external setError : (t, unit => unit) => unit = "onerror";

let loadImage = (url: string) : Js.Promise.t(t) => {
  let img = makeImage();
  setSrc(img, url);
  Js.Promise.make((~resolve, ~reject) => {
    setOnload(img, () => [@bs] resolve(img));
    setError(img, () =>
      [@bs] reject(ImageNotFound(url ++ "cannot be loaded."))
    );
    ();
  });
};