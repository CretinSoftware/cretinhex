cretinhex/c
===========


Description
-----------

Ce dossier contient tout le code écrit en C

  - **cretinlib/** : implémentation des types génériques LDC, Graphe, ABR et ARN
  - **hex/** : implémentation des types spécifiques au jeu de *hex* : Joueur, Damier, GrapheHex, Partie et Minimax
  - **ia_randombot/** : notre première *stupidité artificielle* jouant au hasard. Elle n'a servi qu'a tester l'integration des IA
  - **ia_gotoonebot/** : IA implémentant l'algorithme du Minimax exhaustif. N'est pas capable de jouer dans des temps raisonnable sur des grilles supérieures à 3x3 cases
  - **ia_bridgebot/** : IA détectant les ponts et jouant en temps raisonnable sur des grilles raisonnables (inférieur à 20x20)
  - **tests/** : tests de tous ces modules



Options du makefile
-------------------

Compilation des sous-dossiers et création des bibliothèques *.so*

	make

Génération des headers JNI (utilise ../java/Makefile)

	make headers

Nettoyage

	# Fait un clean dans les sous-dossiers
	make clean
	
	# Fait un maxclean dans les sous-dossiers, et supprime les bibliothèques .so
	make maxclean
