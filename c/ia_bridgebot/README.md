cretinhex/c/bridgebot
=====================


Description
-----------

BridgeBot est l'IA qui détecte les ponts, demandée dans la version 3.  
Elle utilise grandement les fonctions offertes par GrapheHexPlus.  
Elle est composée de ces fichiers

  - **bridgebot** : Calcul du plus court chemin par la méthode des *patatoïdes concentriques*, et recherche du placement de pion *le plus utile*
  - **bridgebotJNI** : Interface JNI pour une utilisation depuis Java

Le fonctionnement de *BridgeBot* est détaille dans le document de bilan, avec une analyse de sa complexité.  
*Voir papiers/Bilan.pdf*



Options du makefile
-------------------

Compilation : génère les .o

	make

Nettoyage : supprime les .o

	make [max]clean

