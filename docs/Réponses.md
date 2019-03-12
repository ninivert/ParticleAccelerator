# Réponses

## Semaine 1

> Comment représentez vous ces vecteurs ?

Avec une classe `Vector3D`.

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

[Voir la documentation Vector3D](#vector3d) pour plus d'informations.

> Quels droits d'accès ?

Toutes les méthodes de surcharge et les paramètres du vecteur sont en privé (aucune raison pour que l'utilisateur veuille y accéder, sachant que l'on a surchargé les opérateurs).

Le reste est en public.

## Semaine 2

N/A

## Semaine 3

> Avez-vous ajouté un constructeur de copie ? Pourquoi (justifiez votre choix) ?

Oui, c'est toujours pratique de pouvoir déclarer un nouveau vecteur à partir d'un vecteur déjà existant.

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

[Voir documentation](#vector3d).

> Comment avez-vous implémenté gamma : comme attribut ou comme méthode ? Même question pour l'énergie.

On stocke `gamma` comme un attribut simple, car

1. Nous comptons l'utiliser souvent pour évaluer la quantité de mouvement
2. La quantité de mouvement (alors facile à calculer) est facile à interpréter phyisquement et nous semble beaucoup utilisée dans les calculs
3. Manipuler les quantités `gamma` bien plus petites que les c^2 que l'énergie implique nous permettra de mieux comprendre et d'avoir une meilleur précision sur les résultats.

Le choix logique est alors d'implémenter l'énergie comme une méthode `getEnergy`.
