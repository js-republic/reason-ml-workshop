type storeType('state) = {
  mutable actions: list(Actions.all),
  mutable preReducer: (float, 'state, Actions.all) => 'state,
  mutable postReducer: (float, 'state, Actions.all) => 'state,
  mutable state: 'state,
  mutable stage: option(Types.stageType)
};

let store: storeType(Types.rootState) = {
  preReducer: Reducer.pre,
  postReducer: Reducer.post,
  actions: [],
  /* "rootState" état global du système de type Types.rootState */
  state:
    /* "screen" définie l'état de l'écran (pas utile pour vous) de type Types.screenState */
    {
      screen: {
        height: Constants.height,
        width: Constants.width,
        potentialBg: None
      },
      /* "ship" de type Types.shipState, définie l'état du vaisseau */
      ship:
        /* "potentialShipSprite" est l'image potentiellement chargée du vaisseau */
        {
          potentialShipSprite: None,
          /* x et y sont les coordonnées du vaisseau */
          x: Constants.width /. 2. -. 30.,
          y: Constants.height -. 62.,
          /* height et width sont la hauteur et largeur du vaisseau */
          height: 62.,
          width: 60.
        },
      /* "shot" de type Types.shotState, définie l'état de tous les projectiles */
      shot: {
        itemModel:
          /* "potentialSprite" est l'image potentiellement chargée du shot */
          {
            potentialSprite: None,
            /* height et width sont la hauteur et largeur d'un projectile */
            width: 8.,
            height: 30.,
            /* x et y sont les coordonnées d'un projectile */
            x: 0.,
            y: 0.
          },
        /* list des projectiles actuellement déssinés */
        shots: []
      },
      /* "alien" de type Types.alienState, définie l'état de tous les aliens */
      alien: {
        itemModel:
          /* "potentialSprite" est l'image potentiellement chargée de l'alien */
          {
            potentialSprite: None,
            /* height et width sont la hauteur et largeur d'un alien */
            width: 64.,
            height: 64.,
            /* x et y sont les coordonnées d'un alien */
            x: 0.,
            y: 0.,
            /* "direction" est le sens de déplacement de l'alien, 1 pour de gauche à droite, -1 pour droite à gauche */
            direction: 1
          },
        /* "lastSpawn" réprésente le dernier timestamp auquel un alien a été créé */
        lastSpawn: 0.,
        /* list des aliens actuellement déssinés */
        aliens: []
      }
    },
  stage: None
};

let applyReducers = (elapsedTime: float) : unit => {
  store.state =
    List.fold_left(
      (state, action) => {
        let preState: Types.rootState =
          store.preReducer(elapsedTime, state, action);
        let newState: Types.rootState = {
          screen: preState.screen,
          shot: Shot_reducer.reducer(elapsedTime, preState.shot, action),
          alien: Alien_reducer.reducer(elapsedTime, preState.alien, action),
          ship: Ship_reducer.reducer(elapsedTime, preState.ship, action)
        };
        store.postReducer(elapsedTime, newState, action);
      },
      store.state,
      store.actions
    );
  store.actions = [];
  ();
};

let dispatch = (action: Actions.all) : unit =>
  store.actions = store.actions @ [action];