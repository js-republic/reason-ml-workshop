open Types;

open List;

let findNotCollided =
    (aliens: list(alien), shots: list(shot))
    : (list(alien), list(shot)) => (
  aliens,
  shots
);