open Jest;

open Types;

open Colision;

open Expect;

let mkAlien = (x, y, w, h) => {
  x,
  y,
  potentialSprite: None,
  width: w,
  height: h,
  direction: 1
};

let mkShot = (x, y, w, h) => {
  x,
  y,
  potentialSprite: None,
  width: w,
  height: h
};

let mkShipState = (~x=10., ~y=0., ~height=10., ~width=10., ()) => {
  potentialShipSprite: None,
  x,
  y,
  height,
  width
};

describe("Ship.render (Step 1)", () =>
  test("should not render when the option is None", () => {
    /* given a null raw canvas 2D context js object and a Ship with sprite equal to None */
    let ctx: canvasContext = [%raw {|null|}];
    let state = {
      potentialShipSprite: None,
      x: 0.,
      y: 0.,
      height: 0.,
      width: 0.
    };
    /* when, call render */
    let result = Ship.render(ctx, state);
    /* then, nothing happen */
    expect(result) |> toBe();
  })
);

/* Find a way to test the drawImage call in `Some` case */
describe("Ship.onKeyUp (Step 2-A)", () => {
  /* Reset each time the list of dispatched actions */
  beforeEach(() => Store.store.actions = []);
  testAll(
    "should not dispatch when the keycode is not handled",
    ["unknown_test_code", "Back", "Ctrl"],
    randomTestCode => {
      /* when we call onKeyUp with some random keyCode*/
      Ship.onKeyUp(randomTestCode);
      /* then, no action has been dispatched */
      expect(Store.store.actions) |> toEqual([]);
    }
  );
  test("should dispatch GoLeft when the keycode is 'ArrowLeft'", () => {
    /* when we call onKeyUp with "ArrowLeft" */
    Ship.onKeyUp("ArrowLeft");
    /* then, an action GoLeft has been dispatched */
    expect(Store.store.actions) |> toEqual([Actions.GoLeft]);
  });
  test("should dispatch GoRight when the keycode is 'ArrowRight'", () => {
    /* when we call onKeyUp with "ArrowRight" */
    Ship.onKeyUp("ArrowRight");
    /* then, an action GoRight has been dispatched */
    expect(Store.store.actions) |> toEqual([Actions.GoRight]);
  });
});

describe("Ship_reducer.reducer (Step 2-B)", () => {
  test(
    "should returns the state as it when the action is not GoLeft or GoRight",
    () => {
    /* given a classic Ship state */
    let shipState = mkShipState();
    /* when Ship's reducer is called with an unhandled action*/
    let newShipState =
      Ship_reducer.reducer(0., shipState, Actions.ResetInGame);
    /* then, the returned state is the same */
    expect(newShipState) |> toBe(shipState);
  });
  test("should move ship on the left when the action is GoLeft", () => {
    /* given */
    let shipState = mkShipState(~x=10., ());
    let elapsedTime = 10.;
    let delta = elapsedTime *. Ship_reducer.shipSpeed;
    let expectedShipState = mkShipState(~x=10. -. delta, ());
    /* when Ship's reducer is called with an GoLeft */
    let newShipState =
      Ship_reducer.reducer(elapsedTime, shipState, Actions.GoLeft);
    /* then, the returned state is the same */
    expect(newShipState) |> toEqual(expectedShipState);
  });
  test("should move ship more on the left when the elapsed time is bigger", () => {
    /* given */
    let shipState = mkShipState(~x=30., ());
    let elapsedTime = 30.;
    let delta = elapsedTime *. Ship_reducer.shipSpeed;
    let expectedShipState = mkShipState(~x=30. -. delta, ());
    /* when Ship's reducer is called with an GoLeft */
    let newShipState =
      Ship_reducer.reducer(elapsedTime, shipState, Actions.GoLeft);
    /* then, the returned state is the same */
    expect(newShipState) |> toEqual(expectedShipState);
  });
  test(
    "should not move ship on the left when the Ship try to go out the map", () => {
    /* given the ship is already leftmost*/
    let shipState = mkShipState(~x=0., ());
    /* when Ship's reducer is called with an GoLeft */
    let newShipState = Ship_reducer.reducer(10., shipState, Actions.GoLeft);
    /* then, the returned state is the same */
    expect(newShipState) |> toEqual(shipState);
  });
  test("should move ship on the right when the action is GoRight", () => {
    /* given */
    let shipState = mkShipState(~x=10., ());
    let elapsedTime = 10.;
    let delta = elapsedTime *. Ship_reducer.shipSpeed;
    let expectedShipState = mkShipState(~x=10. +. delta, ());
    /* when Ship's reducer is called with an GoRight */
    let newShipState =
      Ship_reducer.reducer(elapsedTime, shipState, Actions.GoRight);
    /* then, the returned state is the same */
    expect(newShipState) |> toEqual(expectedShipState);
  });
  test(
    "should move ship more on the right when the elapsed time is bigger", () => {
    /* given */
    let shipState = mkShipState(~x=30., ());
    let elapsedTime = 30.;
    let delta = elapsedTime *. Ship_reducer.shipSpeed;
    let expectedShipState = mkShipState(~x=30. +. delta, ());
    /* when Ship's reducer is called with an GoRight */
    let newShipState =
      Ship_reducer.reducer(elapsedTime, shipState, Actions.GoRight);
    /* then, the returned state is the same */
    expect(newShipState) |> toEqual(expectedShipState);
  });
  test(
    "should not move ship on the right when the Ship try to go out the map", () => {
    /* given the ship is already leftmost*/
    let shipWidth = 10.;
    let shipState =
      mkShipState(~x=Constants.width -. shipWidth, ~width=shipWidth, ());
    /* when Ship's reducer is called with an GoRight */
    let newShipState = Ship_reducer.reducer(10., shipState, Actions.GoRight);
    /* then, the returned state is the same */
    expect(newShipState) |> toEqual(shipState);
  });
});

describe("Colision.findNotCollided", () => {
  test("should return empty shot list and alien list when they collide", () => {
    /* given */
    let aliens: list(alien) = [mkAlien(0., 0., 10., 10.)];
    let shots: list(shot) = [mkShot(0., 0., 10., 10.)];
    /* when */
    let (remainingAliens, remainingShots) = findNotCollided(aliens, shots);
    /* then */
    expect((List.length(remainingAliens), List.length(remainingShots)))
    |> toEqual((0, 0));
  });
  test("should return alien and shot when they don't collide", () => {
    let aliens: list(alien) = [mkAlien(0., 0., 10., 10.)];
    let shots: list(shot) = [mkShot(11., 11., 10., 10.)];
    let (remainingAliens, remainingShots) = findNotCollided(aliens, shots);
    expect((List.length(remainingAliens), List.length(remainingShots)))
    |> toEqual((1, 1));
  });
  test("should return one alien when the shot hits another alien", () => {
    let aliens: list(alien) = [
      mkAlien(0., 0., 10., 10.),
      mkAlien(5., 5., 10., 10.)
    ];
    let shots: list(shot) = [mkShot(11., 11., 10., 10.)];
    let (remainingAliens, remainingShots) = findNotCollided(aliens, shots);
    expect((List.length(remainingAliens), List.length(remainingShots)))
    |> toEqual((1, 0));
  });
});