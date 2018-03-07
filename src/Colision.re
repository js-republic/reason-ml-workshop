open Types;

open List;

let removeKilledBy = (shot: shot, aliens: list(alien)) : list(alien) =>
  aliens
  |> filter(alien =>
       ! (
         shot.x < alien.x
         +. alien.width
         && shot.x
         +. shot.width > alien.x
         && shot.y < alien.y
         +. alien.height
         && shot.height
         +. shot.y > alien.y
       )
     );

let findNotCollided =
    (aliens: list(alien), shots: list(shot))
    : (list(alien), list(shot)) => {
  let initValue: (list(alien), list(shot)) = (aliens, []);
  fold_left(
    ((aliensStillAlive, missedShots), shot: shot) => {
      let newAliensStillAlive = aliensStillAlive |> removeKilledBy(shot);
      let isShotHit = length(newAliensStillAlive) != length(aliensStillAlive);
      let newMissedShot = isShotHit ? missedShots : missedShots @ [shot];
      (newAliensStillAlive, newMissedShot);
    },
    initValue,
    shots
  );
};