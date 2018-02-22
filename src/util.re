type gameImage;

[@bs.send.pipe : Webapi.Canvas.Canvas2d.t] external drawImage : (gameImage, int, int) => unit = "";


let loadImage: (string)=> Js.Promise.t(gameImage) = [%bs.raw {|
  function (url) {
    const img = new Image();
    img.src = url;
    return new Promise ((resolve, reject) => {
      img.onload = () => resolve(img);
      img.onerror = () => reject(`${url} cannot be loaded.`)
    });
  }
|}];