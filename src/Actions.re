type all =
  | ResetInGame
  | Tick
  | ShipImageLoaded(Types.image)
  | BgImageLoaded(Types.image)
  | AlienImageLoaded(Types.image)
  | ShotImageLoaded(Types.image)
  | GoLeft
  | GoRight
  | Fire(Types.coordinate);