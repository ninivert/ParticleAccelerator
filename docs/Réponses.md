# Semaine 1

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

Voir la page [Vector3D](Classes/Vector3D.md) pour plus d'informations

> Quels droits d'accès ?

Toutes les méthodes de surcharge et les paramètres du vecteur sont en privé (aucune raison pour que l'utilisateur veuille y accéder, sachant que l'on a surchargé les opérateurs).

Le reste est en public.