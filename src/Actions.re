type all =
  | ResetInGameState
  | Tick(float)
  | ShipImageLoaded(HtmlImage.t)
  | BgImageLoaded(HtmlImage.t)
  | AlienImageLoaded(HtmlImage.t)
  | ShotImageLoaded(HtmlImage.t)
  | Shot(float, float);