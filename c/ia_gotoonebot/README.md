cretinhex/c/gotoonebot
======================


Description
-----------

Voici l'IA qui utilise l'arbre Minimax

Gotoone *(prononcez Gotoune ou Gotouwane)*  
Étymologie : *Aglomération des mots go-to-one, ce que se contente de faire cette IA*

Contenu :

  - **gotoonebot** : Implémentation de l'IA (elle cherche dans un arbre minimax des fils notés 1)
  - **gotoonebotJNI** : Interface JNI pour l'utilisation de l'IA en Java

Cette IA est imbattable (du moins si elle commence), et toute erreur face à elle est impardonnable.  
Elle adopte toujours la stratégie gagnante, si elle existe. Or nous savons que cette stratégie existe pour le premier joueur.

Néanmoins il faut noter que sa complexité en temps et en mémoire est ahurissante, supérieure à la factorielle du nombre de case.  
Pour une grille de 3x3 cases, par exemple, l'arbre Minimax comporte presque un million de noeuds !  
Nous n'avons pas eu la patience de le faire tourner sur une grille de 4x4 cases (environ 50 000 000 000 noeuds !

Analyse de complexité disponible dans le document de bilan.  
*voir papiers/Bilan.pdf*


Options du makefile
-------------------

Compilation : génère les .o

	make

Nettoyage : supprime les .o

	make [max]clean

