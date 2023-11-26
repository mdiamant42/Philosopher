# philosopher

Ce projet, réalisé dans le cadre de l'école 42, consiste à implémenter une simulation du problème classique des philosophes dînant.

## Description

Le problème des philosophes dînant met en scène un groupe de philosophes assis autour d'une table, chacun ayant une assiette de spaghetti et une fourchette. Entre chaque paire de philosophes, il y a une fourchette. Les philosophes passent leur temps à penser, dormir et manger. Cependant, ils doivent partager les fourchettes pour manger. Un philosophe ne peut manger que s'il a les deux fourchettes (gauche et droit) et il relâche ensuite les fourchettes.

## Objectif

L'objectif de ce projet est de créer une simulation qui évite les deadlocks et les data race entre les philosophes.

## Utilisation

Le programme prend en entrée le nombre de philosophes le temps qu'ils ont pour vivre
le temps nécéssaire pour mange, le temps nécessaire pour dormir et en option
le nombre de repas que doit prendre chaque philosophe avant d'arreter la simulation.
Exemple d'utilisation :
```shell
./philosopher 4 401 200 200 7
```

## Compilation

Compilez le programme avec le Makefile fourni ou en utilisant la commande `make`.

Exemple de compilation : `make`

## Ressources

Pour plus de détails sur le projet philosopher, référez-vous au sujet fourni par l'école 42.
