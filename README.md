# ReasonML Workshop

Ce workshop a pour but de familiariser les participants avec le langage ReasonML en développant plusieurs parties d'un Space Invader !

_ReasonML_ est fortement inspiré de OCaml et donc par définition statiquement fortement typé ainsi que fonctionel.
ReasonML a été conçu afin d'être plus simple d'utilisation qu'OCaml et se rapprocher un peu plus de la syntaxe classique de JavaScript.
ReasonML est fortement lié à un autre projet nomé [Bucklescript](bucklescript.github.io]) qui sert justement à compiler du OCaml ou ReasonML en JavaScript.

## Pré-requis

* Un ordinateur... c'est mieux :)
* NodeJS & NPM installé
* Visual Studio Code (optionel, mais a la meilleur intégration pour l'instant) et le plugin ReasonML installé. cf. [Package ReasonML](https://github.com/reasonml-editor/vscode-reasonml)

## Démarrage

> Capitaine Kirk, les aliens débarquent et le système de défense de l'enterprise est hors service, nous avons besoin de vous !

Pour le réparer, il vous faudra d'abord récupérer les sources du centre de contrôle ici :

```bash
git clone git@github.com:js-republic/reason-ml-workshop.git
```

Vous pourrez ensuite le démarrer en rentrant dans le terminal :

```bash
npm install
```

```bash
npm start
```

Il ne vous restera qu'a ouvrir le panneau de contrôle (aka. le fichier `index.html`) dans votre navigateur.

Votre mission commence ici capitaine, nous comptons sur vous et votre fine équipe.

## GPS intergalactic brouillé

Votre première tâche va consister a réparer le GPS de l'entreprise. En effet pour l'instant celui-ci n'apparait même sur la carte ...

Rendez-vous dans le fichier `src/Ship.re`, pour réactiver le rendu de notre vaisseau sur la carte en implémentant la fonction `render` :

```reason
let render = (ctx, state: Types.shipState) =>
  switch state.potentialSprite {
  | _ => ()
  };
```

L'ensemble des plans du vaisseau ainsi que les types utilisés dans le système sont visibles dans le fichier `src/Types.re`.

Cette fonction prends en argument, en premier le context du canvas ([API Canvas Context](https://developer.mozilla.org/fr/docs/Web/API/CanvasRenderingContext2D)) et en deuxième l'état courant du vaisseau visible dans le fichier `src/Types.re` à la ligne 7.

> Spock vous signale qu'une fonction `drawImage` existe dans le fichier `src/HtmlImage.re` à la ligne 7. Il nous transmet aussi une liste de documents utiles :

* <https://reasonml.github.io/docs/en/pattern-matching.html#usage>
* <https://reasonml.github.io/docs/en/syntax-cheatsheet.html>
* <https://reasonml.github.io/docs/en/function.html#labeled-arguments>
* <https://reasonml.github.io/docs/en/variant.html#option>

<details>
<summary><i>Découvrer la solution ici</i></summary>
<p>
<pre>
let render = (ctx, state: Types.shipState) =>
  switch state.potentialSprite {
  | Some(sprite) =>
    ctx |> HtmlImage.drawImage(sprite, ~x=state.x, ~y=state.y);
    ();
  | None => ()
  };
</pre>
</p>
</details>

---

## Remettez en marche les propulseurs auxiliaires

Notre vaiseau est cloué sur place et nous ne pouvons rien faire pour défendre la Fédération des planètes unies. Nous avons besoin de réparer les propulseurs auxiliaires.

> Spock nous signale que notre vaisseau repose sur une architecture Flux et qu'il dispose d'actions listées dans le fichier `src/Actions.re`. Ces actions peut être dispatchées grâce à la fonction `dispatch` du module `Store` trouvable dans le fichier `src/Store.re`.

Vous devez donc implémenter la fonction `onKeyUp` du fichier `src/Ship.re` pour y dispatcher les action `GoLeft` ou `GoRight` en fonction des touches du clavier.

```reason
let onKeyUp = (event: Dom.keyboardEvent) : unit =>
  switch (Webapi.Dom.KeyboardEvent.code(event)) {
  | _ => ()
  };
```

Et le reducer du vaisseau `src/Ship_reducer.re` pour gérer les actions afin d'appliquer une translation du vaisseau en `y` en fonction de la direction que vous avez dispatché...
L'ingénieur Scott, nous fait remarqué que ce reducer est un modèle un peu particulié car il prend aussi en charge le temps depuis le dernier rafraichissement de l'écran, le paramètre `elapsedTime` en millisecond. Cela permettra de d'avoir une vitesse constante.

```reason
let reducer = (elapsedTime: float, state: Types.shipState, action: Ations.all): Types.shipState =>
  switch action {
  | ShipImageLoaded(img) => {...state, potentialSprite: Some(img)}
  | _ => state
  };
```

> Des fonctions `max` et `min` sont disponibles ainsi qu'un module `Constants` contenant la taille de la carte. Et rappelez-vous, vous devez toujours renvoyer une nouvelle instance du state jamais le modifiez directement.

Liens utiles :

* <https://reasonml.github.io/docs/en/variant.html>
* <https://reasonml.github.io/docs/en/integer-and-float.html>
* <http://2ality.com/2018/01/lists-arrays-reasonml.html#more-ways-of-creating-lists>

<details>
<summary><i>Découvrer la solution ici</i></summary>
<p>
// src/Ship.re
<pre>
let onKeyUp = (event: Dom.keyboardEvent) : unit =>
  switch (Webapi.Dom.KeyboardEvent.code(event)) {
  | "ArrowLeft" => Store.dispatch(Actions.GoLeft)
  | "ArrowRight" => Store.dispatch(Actions.GoRight)
  | _ => ()
  };
</pre>
// src/Ship_reducer.re
<pre>
let reducer =
    (elapsedTime: float, state: Types.shipState, action: Actions.all)
    : Types.shipState =>
  switch action {
  | ShipImageLoaded(img) => {...state, potentialSprite: Some(img)}
  | GoLeft => {...state, x: max(0., state.x -. elapsedTime *. 0.5)}
  | GoRight => {...state, x: min(height, state.x +. elapsedTime *. 0.5)}
  | _ => state
  };
</pre>
</p>
</details>

---

# Activer l'armement de l'enterprise

Se déplacer c'est déjà très bien, mais nos défenses sont toujours inertes et les aliens se rapprochent, le temps devient notre ennemi !

Le canon à Ion principale a visiblement été endomagé durant la dernière bataille. Il ne reçoit même pas les instructions de tir ! Aller dans le fichier `src/Ship.re` et dispatcher l'action `Fire` à l'appui d'une touche en lui donnant comme coordonnés d'origine celle du vaiseau.

> L'ingénieur Scott rappel que l'on peut accéder exeptionellement aux donnés du store du vaisseau avec l'expression `Store.store.state`. Cela sera bien utile pour récupérer notre position courante.

<details>
<summary><i>Découvrer la solution ici</i></summary>
<p>
<pre>
let onSpace = (state: Types.shipState) => {
  let y = Constants.height -. state.height;
  let x = state.x +. state.width /. 2.;
  Store.dispatch(Actions.Fire(x, y));
};

let onKeyUp = (event: Dom.keyboardEvent) : unit =>
switch (Webapi.Dom.KeyboardEvent.code(event)) {
| "ArrowLeft" => Store.dispatch(Actions.GoLeft)
| "ArrowRight" => Store.dispatch(Actions.GoRight)
| "Space" => onSpace(Store.store.state.ship)
| \_ => ()
};

</pre>
</p>
</details>

Nous pouvons désormais bien envoyé les instructions de tir, mais le canon reste inactif... Regarder dans le reducer `src/Shot_reducer.re`, l'action `Fire` n'est probablement pas géré. De même, chaque projectile du canon à Ion doit-être guidé grâce à l'action `Tick` dispatché par l'intelligence artificielle à chaque boucle. Cela comprend aussi l'auto-destruction des projectiles quand ils sortent de l'écran de contrôle - Faudrait pas dégomer une étoile noire par erreur ...

<details>
<summary><i>Découvrer la solution ici</i></summary>
<p>
<pre>
open Types;

let tickShots = (shots: list(shot), elapsedTime: float) : list(shot) =>
shots
|> List.map((i: shot) => ({...i, y: i.y -. elapsedTime \*. 0.5}: shot))
|> List.filter((i: shot) => i.y > 0.);

let reducer =
(elapsedTime: float, state: shotState, action: Actions.all)
: shotState =>
switch action {
| ShotImageLoaded(img) => {
...state,
itemModel: {
...state.itemModel,
potentialSprite: Some(img)
}
}
| ResetInGame => {...state, shots: []}
| Tick => {...state, shots: tickShots(state.shots, elapsedTime)}
| Fire(x, y) => {...state, shots: state.shots @ [{...state.itemModel, x, y}]}
| \_ => state
};

</pre>
</p>
</details>

Doc du canon à Ion Mark III :

* <http://2ality.com/2017/12/functions-reasonml.html#example-piping-lists>
* <http://2ality.com/2018/01/lists-arrays-reasonml.html#more-ways-of-creating-lists>
