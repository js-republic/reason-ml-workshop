let removeKilledBy = (shot: Types.shot, aliens: list(Types.alien)) : list(Types.alien) =>
  List.filter(
    (alien: Types.alien) =>
      ! (
        shot.x < alien.x
        +. alien.width
        && shot.x
        +. shot.width > alien.x
        && shot.y < alien.y
        +. alien.height
        && shot.height
        +. shot.y > alien.y
      ),
    aliens
  );

let findNotCollided =
    (aliens: list(Types.alien), shots: list(Types.shot))
    : (list(Types.alien), list(Types.shot)) => {
  let initValue: (list(Types.alien), list(Types.shot)) = (aliens, []);
  List.fold_left(
    ((aliensStillAlive, missedShots), shot: Types.shot) => {
      let newAliensStillAlive = aliensStillAlive |> removeKilledBy(shot);
      let isShotHit = List.length(newAliensStillAlive) != List.length(aliensStillAlive);
      let newMissedShot = isShotHit ? missedShots : missedShots @ [shot];
      (newAliensStillAlive, newMissedShot);
    },
    initValue,
    shots
  );
};