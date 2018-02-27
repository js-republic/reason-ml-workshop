type all =
  | ClearInGameState
  | Tick(float)
  | ShipImageLoaded(HtmlImage.t)
  | BgImageLoaded(HtmlImage.t)
  | AlienImageLoaded(HtmlImage.t)
  | ShotImageLoaded(HtmlImage.t)
  | Shot(float, float);