cretinhex/c/cretinlib
=====================


Description
-----------

Ce dossier contient l'implémentation des types génériques.

  - **LDC** : Liste doublement chaînée
  - **ABR** : Arbre binaire de recherche
  - **ABRPlus** : Fonctions utilisant ABR et LDC
  - **ARN** : Arbre rouge-noir
  - **ARNPlus** : Fonctions utilisant ARN et LDC
  - **Graphe**
  - **utile** : Fonction affichant une adresse mémoire *(ce fichier a finalement très peu servi)*

Les types génériques sont des collections d'éléments (*LDCELement*, *ABRElement*, etc.) qui sont simplement des alias de *(void \*)*  
Chaque élément doit être associé à sa fonction de suppression (*LDCElementFree*, etc.), et, pour les arbres, à sa fonction d'évaluation (*ABRElementEval*)

Ces collections peuvent donc contenir n'importe quel type d'élément, puisqu'elles travaillent avec leurs adresses. On peut même y stocker des éléments disparates.

Un travail minutieux qui permet de réutiliser grandement ces types en évitant les fuites mémoires

Consultez la documentation pour d'informations.



Options du makefile
-------------------

Compilation : génère les .o

	make

Nettoyage : supprime les .o

	make [max]clean

