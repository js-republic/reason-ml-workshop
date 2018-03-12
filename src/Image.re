/**
 * Define a draw function wich interops with the `drawImage` method presents on a
 * `CanvasContext` instance.
 * The tag [@bs.send] is a Buckescript tag used to explain that the function draw will be transpiled
 * into method callable on a `canvasContext` object in plain JavaScript.
 * Please note, the names between parentheses are not variable's names but
 * type's names !
 *
 * @see https://www.w3schools.com/tags/canvas_drawimage.asp
 * @see https://bucklescript.github.io/docs/en/function.html#object-method
 *
 * @param Types.canvasContext Type of Canvas's context used to draw the image
 * @param Types.image  Type of the image we want to draw
 * @param ~x:float labeled X coordinate declared as float, where we want to draw image
 * @param ~y:float labeled Y coordinate declared as float, where we want to draw image
 * @return unit (aka. Nothing)
 *
 */
[@bs.send]
external draw :
  (Types.canvasContext, Types.image, ~x: float, ~y: float) => unit =
  "drawImage";