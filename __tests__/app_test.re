open Jest;

open Types;

open Colision;

open Expect;

let mkAlien = (x, y, w, h) : alien => {
  x,
  y,
  potentialSprite: None,
  width: w,
  height: h,
  direction: 1
};

let mkShot = (x, y, w, h) : shot => {
  x,
  y,
  potentialSprite: None,
  width: w,
  height: h
};

describe("findNotCollided", () => {
  test(
    "should return empty shot list and empty alien list when they collide", () => {
    let aliens: list(alien) = [mkAlien(0., 0., 10., 10.)];
    let shots: list(shot) = [mkShot(0., 0., 10., 10.)];
    let (remainedAliens, remainedShots) = findNotCollided(aliens, shots);
    expect(List.length(remainedAliens)) |> toBe(0);
    expect(List.length(remainedShots)) |> toBe(0);
  });
  test("should return alien and shot when they don't collide", () => {
    let aliens: list(alien) = [mkAlien(0., 0., 10., 10.)];
    let shots: list(shot) = [mkShot(11., 11., 10., 10.)];
    let (remainedAliens, remainedShots) = findNotCollided(aliens, shots);
    expect(List.length(remainedAliens)) |> toBe(1);
    expect(List.length(remainedShots)) |> toBe(1);
  });
  test("should return one alien when the shot hits another alien", () => {
    let aliens: list(alien) = [
      mkAlien(0., 0., 10., 10.),
      mkAlien(5., 5., 10., 10.)
    ];
    let shots: list(shot) = [mkShot(11., 11., 10., 10.)];
    let (remainedAliens, remainedShots) = findNotCollided(aliens, shots);
    expect(List.length(remainedAliens)) |> toBe(1);
    expect(List.length(remainedShots)) |> toBe(0);
  });
});

describe("Expect.Operators", () => {
  open Expect;
  open! Expect.Operators;
  test("==", () =>
    expect(1 + 2) === 3
  );
});