type all =
  | ResetInGame
  | Tick
  | ShipImageLoaded(HtmlImage.t)
  | BgImageLoaded(HtmlImage.t)
  | AlienImageLoaded(HtmlImage.t)
  | ShotImageLoaded(HtmlImage.t)
  | GoLeft
  | GoRight
  | Shot(float, float);