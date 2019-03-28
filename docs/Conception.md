# Conception

## Hiérarchie et dépendances

Description de la hiérarchie de classes utilisées (relations d'héritage et d'encapsulation)

## Interprétation physique

Nous stockons les valeurs physiques (masse, quantité de mouvement, énergie, charge, etc.) dans le système international (SI) et faisons la conversion en unités de GeV au moment opportun (affichage par exemple). Voir les questions et `Convert` pour plus d'informations.

| Valeur physique | Unité de stockage | Unité d'affichage |
| --- | --- | --- |
| Energie | Non stocké | GeV |
| Qté de mouvement | kg*m/s | GeV/c |
| Masse | kg | GeV/c² |
| Vitesse | Non stocké | m/s |
| Force | N | N |
| Distance | m | m |
| Charge | C | C |
| Gamma | - | - |

## Fichiers `.bundle.h`

L'esprit de ce projet est de faire fonctionner chaque composante avec le strict nécessaire.

On n'a, par exemple, pas besoin d'inclure l'entièreté de la définition d'une classe pour pouvoir utiliser son type dans un autre header. Il suffit en effet de juste faire une « forward declaration ».

La gestion des dépendances des classes est alors faire dans un header `.bundle.h` accocié qui permet lors de son utilisation dans un fichier `.cpp`, d'importer directement toutes les dépendances nécessaires. Les `#pragma once` préviennent la double inclusion d'un header.

Avec cette méthode, on est aussi plus explicites au niveau des dépendances requises.

## Conventions

Une courbure k est de signe positif quand elle va dans le sens horaire (anti-trigonométrique)
