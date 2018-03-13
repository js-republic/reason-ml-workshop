open Jest;

open Types;

open Colision;

open Expect;

let makeAlien = (~x=10., ~y=0., ~height=10., ~width=10., ~direction=1, ()) => {
  x,
  y,
  potentialSprite: None,
  width,
  height,
  direction
};

let makeShot = (~x=10., ~y=0., ~height=10., ~width=10., ()) => {
  x,
  y,
  potentialSprite: None,
  width,
  height
};

let makeShip = (~x=10., ~y=0., ~height=10., ~width=10., ()) => {
  potentialShipSprite: None,
  x,
  y,
  height,
  width
};

describe("Ship.re", () => {
  describe("render", () =>
    test("should not render when the option is None", () => {
      /* given a null raw canvas 2D context js object and a Ship with sprite equal to None */
      let ctx: canvasContext = [%raw {|null|}];
      let state = {potentialShipSprite: None, x: 0., y: 0., height: 0., width: 0.};
      /* when, call render */
      let result = Ship.render(ctx, state);
      /* then, nothing happen */
      expect(result) |> toBe();
    })
  );
  /* Find a way to test the drawImage call in `Some` case */
  describe("onKeyDown", () => {
    /* Reset each time the list of dispatched actions */
    beforeEach(() => Store.store.actions = []);
    testAll(
      "should not dispatch when the keycode is not handled",
      ["unknown_test_code", "Back", "Ctrl"],
      randomTestCode => {
        /* when we call onKeyDown with some random keyCode*/
        Ship.onKeyDown(randomTestCode);
        /* then, no action has been dispatched */
        expect(Store.store.actions) |> toEqual([]);
      }
    );
    test("should dispatch GoLeft when the keycode is 'ArrowLeft'", () => {
      /* when we call onKeyDown with "ArrowLeft" */
      Ship.onKeyDown("ArrowLeft");
      /* then, an action GoLeft has been dispatched */
      expect(Store.store.actions) |> toEqual([Actions.GoLeft]);
    });
    test("should dispatch GoRight when the keycode is 'ArrowRight'", () => {
      /* when we call onKeyDown with "ArrowRight" */
      Ship.onKeyDown("ArrowRight");
      /* then, an action GoRight has been dispatched */
      expect(Store.store.actions) |> toEqual([Actions.GoRight]);
    });
  });
});

describe("Ship_reducer.re", () =>
  describe("reducer", () => {
    test("should returns the state as it when the action is not GoLeft or GoRight", () => {
      /* given a classic Ship state */
      let shipState = makeShip();
      /* when Ship's reducer is called with an unhandled action*/
      let newShipState = Ship_reducer.reducer(0., shipState, Actions.ResetInGame);
      /* then, the returned state is the same */
      expect(newShipState) |> toBe(shipState);
    });
    test("should move ship on the left when the action is GoLeft", () => {
      /* given */
      let shipState = makeShip(~x=10., ());
      let elapsedTime = 10.;
      let delta = elapsedTime *. Ship_reducer.shipSpeed;
      let expectedShipState = makeShip(~x=10. -. delta, ());
      /* when Ship's reducer is called with an GoLeft */
      let newShipState = Ship_reducer.reducer(elapsedTime, shipState, Actions.GoLeft);
      /* then, the returned state is the same */
      expect(newShipState) |> toEqual(expectedShipState);
    });
    test("should move ship more on the left when the elapsed time is bigger", () => {
      /* given */
      let shipState = makeShip(~x=30., ());
      let elapsedTime = 30.;
      let delta = elapsedTime *. Ship_reducer.shipSpeed;
      let expectedShipState = makeShip(~x=30. -. delta, ());
      /* when Ship's reducer is called with an GoLeft */
      let newShipState = Ship_reducer.reducer(elapsedTime, shipState, Actions.GoLeft);
      /* then, the returned state is the same */
      expect(newShipState) |> toEqual(expectedShipState);
    });
    test("should not move ship on the left when the Ship try to go out the map", () => {
      /* given the ship is already leftmost*/
      let shipState = makeShip(~x=0., ());
      /* when Ship's reducer is called with an GoLeft */
      let newShipState = Ship_reducer.reducer(10., shipState, Actions.GoLeft);
      /* then, the returned state is the same */
      expect(newShipState) |> toEqual(shipState);
    });
    test("should move ship on the right when the action is GoRight", () => {
      /* given */
      let shipState = makeShip(~x=10., ());
      let elapsedTime = 10.;
      let delta = elapsedTime *. Ship_reducer.shipSpeed;
      let expectedShipState = makeShip(~x=10. +. delta, ());
      /* when Ship's reducer is called with an GoRight */
      let newShipState = Ship_reducer.reducer(elapsedTime, shipState, Actions.GoRight);
      /* then, the returned state is the same */
      expect(newShipState) |> toEqual(expectedShipState);
    });
    test("should move ship more on the right when the elapsed time is bigger", () => {
      /* given */
      let shipState = makeShip(~x=30., ());
      let elapsedTime = 30.;
      let delta = elapsedTime *. Ship_reducer.shipSpeed;
      let expectedShipState = makeShip(~x=30. +. delta, ());
      /* when Ship's reducer is called with an GoRight */
      let newShipState = Ship_reducer.reducer(elapsedTime, shipState, Actions.GoRight);
      /* then, the returned state is the same */
      expect(newShipState) |> toEqual(expectedShipState);
    });
    test("should not move ship on the right when the Ship try to go out the map", () => {
      /* given the ship is already leftmost*/
      let shipWidth = 10.;
      let shipState = makeShip(~x=Constants.width -. shipWidth, ~width=shipWidth, ());
      /* when Ship's reducer is called with an GoRight */
      let newShipState = Ship_reducer.reducer(10., shipState, Actions.GoRight);
      /* then, the returned state is the same */
      expect(newShipState) |> toEqual(shipState);
    });
  })
);

describe("Alien_reducer.re", () => {
  describe("nextX", () => {
    test("should compute the next alien x position when direction is left to right", () => {
      let x = Alien_reducer.nextX(10., makeAlien(~x=10., ~direction=1, ()));
      expect(x) |> toBe(13.);
    });
    test("should compute the next alien x position when direction is right to left", () => {
      let x = Alien_reducer.nextX(10., makeAlien(~x=10., ~direction=-1, ()));
      expect(x) |> toBe(7.);
    });
  });
  describe("isOnEdge", () => {
    test("should be (true, _) when X is under 0", () => {
      let (leftPart, _) = Alien_reducer.isOnEdge(-1., makeAlien());
      expect(leftPart) |> toBe(true);
    });
    test("should be (false, _) when X is equal or more than 0", () => {
      let (leftPart, _) = Alien_reducer.isOnEdge(0., makeAlien());
      expect(leftPart) |> toBe(false);
    });
    test("should be (_, true) when the right border of alien exeeds map width", () => {
      let (_, rightPath) = Alien_reducer.isOnEdge(591., makeAlien(~width=10., ()));
      expect(rightPath) |> toBe(true);
    });
    test("should be (_, false) when the right border of alien doesn't exeed map width", () => {
      let (_, rightPath) = Alien_reducer.isOnEdge(590., makeAlien(~width=10., ()));
      expect(rightPath) |> toBe(false);
    });
  });
  describe("moveOnLeftEdge", () =>
    test("should move correclty", () => {
      let alien = makeAlien(~x=10., ~y=20., ~direction=-1, ());
      let newAlien = Alien_reducer.moveOnLeftEdge(alien);
      expect(newAlien) |> toEqual(makeAlien(~x=0., ~y=90., ~direction=1, ()));
    })
  );
  describe("moveOnRightEdge", () =>
    test("should move correclty", () => {
      let alien = makeAlien(~x=590., ~y=20., ~direction=1, ~width=10., ());
      let newAlien = Alien_reducer.moveOnRightEdge(alien);
      expect(newAlien) |> toEqual(makeAlien(~x=590., ~y=90., ~direction=-1, ()));
    })
  );
  describe("moveAlien", () =>
    testAll(
      "should apply motion for each case",
      [
        (makeAlien(~x=10., ~y=20., ~direction=1, ()), makeAlien(~x=13., ~y=20., ~direction=1, ())),
        (
          makeAlien(~x=10., ~y=20., ~direction=-1, ()),
          makeAlien(~x=7., ~y=20., ~direction=-1, ())
        ),
        (makeAlien(~x=0., ~y=30., ~direction=-1, ()), makeAlien(~x=0., ~y=100., ~direction=1, ())),
        (
          makeAlien(~x=591., ~y=10., ~direction=1, ()),
          makeAlien(~x=590., ~y=80., ~direction=-1, ())
        )
      ],
      ((alien, expectedAlien)) => {
        let newAlien = Alien_reducer.moveAlien(10., alien);
        expect(newAlien) |> toEqual(expectedAlien);
      }
    )
  );
  describe("moveAliens", () =>
    test("should apply motion on all aliens", () => {
      let newAliens =
        Alien_reducer.moveAliens(
          [
            makeAlien(~x=10., ~y=20., ~direction=-1, ()),
            makeAlien(~x=591., ~y=10., ~direction=1, ())
          ],
          10.
        );
      expect(newAliens)
      |> toEqual([
           makeAlien(~x=7., ~y=20., ~direction=-1, ()),
           makeAlien(~x=590., ~y=80., ~direction=-1, ())
         ]);
    })
  );
  describe("moveAliens", () =>
    test("should filter aliens out the map", () => {
      let newAliens =
        Alien_reducer.moveAliens(
          [
            makeAlien(~x=10., ~y=-1., ~direction=-1, ()),
            makeAlien(~x=10., ~y=0., ~direction=1, ())
          ],
          10.
        );
      expect(newAliens) |> toEqual([makeAlien(~x=10., ~y=0., ~direction=1, ())]);
    })
  );
});

describe("Colision.re", () =>
  describe("findNotCollided", () => {
    test("should return empty shot list and alien list when they collide", () => {
      /* given */
      let aliens: list(alien) = [makeAlien()];
      let shots: list(shot) = [makeShot()];
      /* when */
      let (remainingAliens, remainingShots) = findNotCollided(aliens, shots);
      /* then */
      expect((List.length(remainingAliens), List.length(remainingShots))) |> toEqual((0, 0));
    });
    test("should return alien and shot when they don't collide", () => {
      let aliens: list(alien) = [makeAlien()];
      let shots: list(shot) = [makeShot(~x=11., ~y=11., ())];
      let (remainingAliens, remainingShots) = findNotCollided(aliens, shots);
      expect((List.length(remainingAliens), List.length(remainingShots))) |> toEqual((1, 1));
    });
    test("should return one alien when the shot hits another alien", () => {
      let aliens: list(alien) = [makeAlien(), makeAlien(~x=5., ~y=5., ())];
      let shots: list(shot) = [makeShot(~x=11., ~y=11., ())];
      let (remainingAliens, remainingShots) = findNotCollided(aliens, shots);
      expect((List.length(remainingAliens), List.length(remainingShots))) |> toEqual((1, 0));
    });
  })
);