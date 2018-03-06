open Types;

/**
 * Define a draw function wich interops with the drawImage method presents on the
 * CanvasContext instance.
 * The tag [@bs.send] is a Buckescript tag used to explain that the function draw will be transpiled
 * into method callable on a `canvasContext` object in plain JavaScript.
 * Please note, the names between parentheses are not variable's names but
 * type's names !
 *
 * @see https://www.w3schools.com/tags/canvas_drawimage.asp
 * @see https://bucklescript.github.io/docs/en/function.html#object-method
 *
 * @param canvasContext Type of canvas context where we want to draw the image
 * @param image  Type of image we want to draw
 * @param x X coordinate where we want to draw image
 * @param y Y coordinate where we want to draw image
 * @return unit (aka. Nothing)
 *
 */
[@bs.send]
external draw : (canvasContext, image, ~x: float, ~y: float) => unit =
  "drawImage";