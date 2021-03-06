# Réponses

## Partie 1

> Comment représentez vous ces vecteurs ?

Avec une classe Vector3D.

> Comment sont-ils organisés : quels attributs ?

Les paramètres sont représentés comme triplet de doubles `x`, `y`, `z`.

On a préféré cela à l'utilisation de tableaux, moins intuitifs et puisque vu que le projet entier est en 3D, il n'est pas nécessaire de rendre la classe généralisable à `n` dimensions.

> Quelles méthodes ?

- Getters: `get<Variable>`
- Setters: `set<Variable>`
- Méthodes de surcharge: `__<methode>__` (à la python)
- Surcharge des opérateurs: en utilisant les méthodes `__<methode>__`
- Méthodes publiques propres à chaque instance de la classe
- Méthodes statiques avec `static`

Voir la documentation Vector3D pour plus d'informations.

> Quels droits d'accès ?

Toutes les méthodes de surcharge et les paramètres du vecteur sont en privé (aucune raison pour que l'utilisateur veuille y accéder, sachant que l'on a surchargé les opérateurs).

Le reste est en public.

## Partie 2

N/A

## Partie 3

> Avez-vous ajouté un constructeur de copie ? Pourquoi (justifiez votre choix) ?

Non, en stockant les coordonnées du vecteur sous forme de `double`, la copie de surface fournie par défaut fonctionne parfaitement. Idem pour l'opérateur d'assignement `=`.

> Si l'on souhaitait ajouter un constructeur par coordonnées sphériques (deux angles et une longueur),
>
> - que cela impliquerait-il au niveau des attributs de la classe ?
> - quelle serait la difficulté majeure (voire l'impossibilité) de sa réalisation en C++ ? (C'est d'ailleurs pour cela qu'on ne vous demande pas de faire un tel constructeur!)

Au niveau de la construction, on calculerait les coordonnées carthésiennes correspondantes et on appellerait le constructeur pour `x, y, z`.

Au niveau des attributs de classe, cela dépend de comment on souhaite utiliser la classe.

| Forme stockée | Utilisation des méthodes "carthésiennes" (`operator +`, `operator *`, `operator ^`, etc.) | Utilisation des méthodes "sphériques" (`norm`, `rotate`, etc.) |
| --- | --- | --- |
| Carthésienne `x`, `y`, `z` | Optimal | Soit (1) recalculer la représentation sphérique sur demande avec des getters, soit (2) stocker la représentation sphérique et les updater à chaque fois que la représentation carthésienne change |
| Sphérique `alpha`, `theta`, `r` | Lent: les fonctions `sin`, `cos`, `sqrt` etc. sont chères en temps d'exécution. Soit (1) recalculer la représentation carthésienne sur demande avec des getters, soit (2) stocker la représentation carthésienne et les updater à chaque fois que la représentation sphérique change | Optimal |

Tout dépend de comment on souhaite utiliser la classe. Pour l'instant, il nous semble optimal de rester en représentation carthésienne, puisque au bout du compte c'est celle qu'il nous faut pour faire les graphismes et que c'est parfaitement envisageable de programmer le moteur physique en représentation carthésienne (chose que j'ai déjà faite avec d'autres systèmes de particules).

> Quels opérateurs avez vous introduits ?

Voir documentation de Vector3D.

> Comment avez-vous implémenté gamma : comme attribut ou comme méthode ? Même question pour l'énergie.

`gamma` et `energy` sont implémentées sous forme d'attributs pour les raisons suivantes:

1. On stocke la quantité de mouvement: il est en effet plus efficace d'un point de vue algorithmique de la manipuler plutôt que gamma ou l'énergie, gourmandes en racines carrées et autres opérations lentes.
2. Gamma et l'énergie sont alors juste utiles à deux moments: l'initialisation et l'affichage. Inutile alors de les stocker pour devoir les updater à chaque `Particle::step` !

> Extra: quelles unités pour la représentation?

Nous avons choisi d'utiliser les SI pour les raisons suivantes:

1. Les équations du mouvement sont de base exprimées en SI. Si on avait pris des GeV, il aurait fallu faire beaucoup de conversions !
2. L'ordinateur se "fiche" bien de manipuler des SI ou des GeV. Les `double` peuvent représenter des réels allant de `2.2e−308` à `1.7e308` ([Wikipedia](https://en.wikipedia.org/wiki/Double-precision_floating-point_format#Double-precision_examples)), donc la précision n'est pas un problème ici. C'est à l'affichage (bien moins fréquent que l'appel de `Particle::step` !) que la conversion se fait à l'aide de `CONVERT::<...>SItoGeV` pour que la sortie soit un peu plus agréable à lire.

## Partie 4

> Comment proposez-vous de représenter et d'organiser les éléments ?

On a créé une classe Element dont héritent les classes Dipole et Quadrupole.

> Comment proposez-vous de représenter les champs magnétiques des éléments ?

Une fonction `Vector3D getField(Vector3D)` retourne la direction et l'amplitude du champ magnétique donné à un endroit dans l'espace par le `Vector3D` fourni en argument.

> Avez-vous représenté le centre de courbure des éléments courbes ? Si oui, comment (sous quelle forme) ?

Oui, comme l'élément est fixe (la position d'entrée de sortie sont des `const`), le centre de courbure est fixe et on peut donc le calculer une seule fois lors de l'initialisation afin d'éviter de le recalculer à chaque fois.

Nous prenons la CONVENTION que quand k est positif, le sens de parcourt de l'arc de cercle dont les extrémités sont la position initiale et la position finale est ANTI-TRIGONOMETRIQUE

> Comment représentez le fait que chaque particule doit être dans un seul élément ? Cela modifie-t-il d'autres classes (que les Elements) ?

Chaque Particle dispose d'un pointeur à la C sur un élément de l'accélérateur. Il nous est impossible d'utiliser les `unique_ptr` car il est possible qu'un autre élément/particule aie aussi un pointeur sur l'élément. Nous envisageons la possibilité d'utiliser des `shared_ptr`.

> Comment représentez vous la classe Accelerateur ?

La classe Accelerator contient des tableaux dynamiques de Particle et d'Element

> Pourquoi qualifier le constructeur de copie et `operator =` de « deleted » ?

Les instances de classe accélérateur contiennent beaucoup de particules et l'éléments, ie. c'est un gros zobjet. On voudrait protéger l'utilisateur de la classe d'en faire des copies non intentionnelles.

## Partie 5

> En termes de POO, quelle est donc la nature de la méthode heurte_bord() (ici `Element::isInWall`) ?
>
> Qu'est-ce que cela implique sur la classe générale Element ?

C'est une méthode virtuelle pure, puisque la classe élément est une classe abstraite, c'est-à-dire que l'on ne peut pas instancier un membre de la classe Element.

> En termes de POO, quelle est donc la nature de la méthode dessine() (ici `draw`) ?

- Dans `Renderer`: méthode virtuelle pure (aussi surchargée pour pouvoir dessiner les différents éléments)
- Dans `Drawable`: méthode virtuelle pure destinée à être substituée dans les sous-classes héritant de `Drawable`
- Dans les sous-classes héritant de `Drawable`: appel à la fonction `Renderer::draw` pour l'instance en question (polymorphisme)

> La classe `Accelerator` possède une collection de `Particle`s et une collection d'`Element`s et nous souhaitons pouvoir invoquer la méthode `draw` de chacun(e) de ses particules/éléments, de sorte que chacun(e) soit dessiné(e) avec ses caractéristiques propres, c.-à-d. sa propre méthode `draw`
>
> Quelle est la bonne façon de le faire dans un cadre de programmation orientée-objet ?

On introduit le polymorphisme sous forme de vecteurs de pointeurs sur des `Element`s et des `Particle`s

> A quoi faut-il faire attention pour les classes contenant des pointeurs ? Quelles solutions peut-on envisager ?

Il faire attention à la gestion de mémoire, lors de

- L'initialisation: allocation de la mémoire en utilisant `new`
- L'utilisation: utiliser la syntaxe `instance_ptr->method` au lieu de `instance.method`
- La destruction: désallouer la mémoire correctement avec `delete` ou `smart_ptr.reset()`. Aussi mettre le destructeur en `virtual`, afin que les sous-classes puissent se détruire correctement

## Partie 6

> Comment avez-vous implémenté ces différentes caractéristiques : comme attribut ou comme méthode ?

Les émittances sont implémentées sous forme de méthodes. La méthode `Beam::getEllipsePhaseCoef*()` retourne un `Vector3D` des coefficients des ellipses. Idem pour l'énergie moyenne.

c.f. documentation pour plus d'informations.

## Partie 7

> Quelle est la complexité de ces deux algorithmes ?

On suppose le calcul de forces et leur application en `O(1)`

_Algorithme 1_

```py
for i in range(n):
	for j in range(i):
		# calcul de force F
		# force F de i sur j
		# force -F de j sur i
```

En total, `(n*(n-1))/2` itérations, c'est-à-dire algorithme en `O(n²)`

_Algorithme 2_

```py
for i in range(n):
	for j in range(n):
		# calcul de force F
		# force F de i sur j
```

Celui ci aussi en `O(n²)`, mais on notera qu'en termes implémentation, le premier algorithme sera plus rapide, car on n'a pas besoin de recalculer deux fois une même force.

> Cases: avant de préciser les détails d'implémentation, quelle est la complexité temporelle pire cas de cette solution en fonction du nombre de particules ? [ On supposera ici que les particules sont « assez bien réparties » dans les cases. On supposera de plus que la taille d'une case est petite par rapport à la taille du système. Ainsi on peut faire l'hypothèse que le nombre de particules par case est négligeable (O(1)) devant le nombre total de particules (c.-à-d. que toutes les particules ne se retrouvent pas en même temps dans la même case). ]

```py
for particule in particules: # O(nb de particules)
	# mettre a jour la kääääääääääääse de chaque particule

for case in accelerator: # O(nb de cases)
	for particule in voisins(case): # O(1)
		# calcul des forces O(1)
		# application des forces
```

En faisant la supposition que le nombre de cases est bien inférieur au nombre de particules, on a donc un algorithme `O(n)`, où `n` représente le nombre de particules dans l'accélérateur.

> Quel(s) inconvénient(s) présente cependant cette solution ?

- Au niveau de l'encapsulation, les particules « savent » dans quelle case elles sont, et la case sait quelles particules elle contient. On devrait alors changer les `unique_ptr` dans l'accélérateur à des `shared_ptr`, ce qui n'a conceptuellement pas de sens.
- Ceci perturberait aussi dans notre cas la structure du code

> Comment et où avez-vous implémenté cette nouvelle façon de calculer les interactions entre particules ?

A chaque `step`, on cacule le "progrès" de chaque particule dans l'accélérateur, en se basant sur l'approximation que l'accélérateur est circulaire. Le progrès est alors défini comme l'angle que fait le vecteur position de la particule avec la position d'entrée du premier élément dans l'accélérateur.

La taille d'une case est alors simplement définie comme une distance entre deux progrès.

```py
for beam in beams:
	for particles in beam:
		for particle in particles:
			# stockage de l'angle
			angle = <particle, base_vector>

for particles in accelerator:
	for otherParticles in accelerator:
		if (abs(angle - otherAngle) < epsilon):
			# exercer les intéractions entre les 2 particules
```
