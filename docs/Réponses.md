# Réponses

## Semaine 1

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

## Semaine 2

N/A

## Semaine 3

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

## Semaine 4

> Comment proposez-vous de représenter et d'organiser les éléments ?

On a créé une classe Element dont héritent les classes Dipole et Quadrupole.

> Comment proposez-vous de représenter les champs magnétiques des éléments ?

Une fonction `Vector3D getField(Vector3D)` retourne la direction et l'amplitude du champ magnétique donné à un endroit dans l'espace par le `Vector3D` fourni en argument.

> Avez-vous représenté le centre de courbure des éléments courbes ? Si oui, comment (sous quelle forme) ?

Oui, comme l'élément est fixe (la position d'entrée de sortie sont des `const`), le centre de courbure est fixe et on peut donc le calculer une seule fois lors de l'initialisation afin d'éviter de le recalculer à chaque fois.

Nous prenons la CONVENTION que quand k est positif, le sens de l'arc de cercle dont les extrémités sont la position initiale et la position finale is TRIGONOMETRIQUE

> Comment représentez le fait que chaque particule doit être dans un seul élément ? Cela modifie-t-il d'autres classes (que les Elements) ?

Chaque Particle dispose d'un pointeur à la C sur un élément de l'accélérateur. Il nous est impossible d'utiliser les `unique_ptr` car il est possible qu'un autre élément/particule aie aussi un pointeur sur l'élément. Nous envisageons la possibilité d'utiliser des `shared_ptr`.

> Comment représentez vous la classe Accelerateur ?

La classe Accelerator contient des tableaux dynamiques de Particle et d'Element

> Pourquoi qualifier le constructeur de copie et `operator =` de « deleted » ?

Les instances de classe accélérateur contiennent beaucoup de particules et l'éléments, ie. c'est un gros zobjet. On voudrait protéger l'utilisateur de la classe d'en faire des copies non intentionnelles.
