cretinhex/c/tests
=================


Description
-----------

Ce dossier contient tous les tests des modules réalisés en C :

  - **exec_tests.sh** et **exec\_serie\_tests.sh** : scripts lançant des séries de tests. On leur passe la commande, les fichiers en entrée, etc.
  - **main_XXX.c** : mini-programme implémentant les fonctions à tester du module XXX
  - **script\_test\_XXX.sh** : script appelant *exec\_serie\_tests.sh* en lui passant les commandes correspondant à *main_XXX.c*, etc.
  - **mk_YYY.c** : programme générant les fichiers en entrée pour les tests (nombres, n-uplets, données de graphes, sauvegardes de parties)

Utilisez le makefile pour lancer les séries de tests automatiques.

Après chaque test / série de tests, des fichiers sont produits dans le dossier *fichiers_out/* :

  - Le résultat de la commande passée (donc, réalisée par *main_XXX*)
  - Le log de valgrind, si des tests mémoire on été effectués.

Le fichier en sortie est ensuite comparé au résultat attendu, ou vérifié avec une commande shell.

  - Si le résultat est conforme, un **OK** vert est affiché
  - Si le résultat n'est pas confome, un **KO** rouge est affiché
  - Si aucun protocole de vérification n'a été spécifié, un **??** jaune est affiché

En effet nous n'avons pas su à quoi comparer certains résultats, comme par exemple la décision prise par une IA.  
Ces tests sont néanmoins réalisés car :

  - Certains tests peuvent être vérifiés *à la main*, en regardant le fichier en sortie
  - Les tests sont chronométrés, et l'information peut être intéressante
  - Les tests mémoire peuvent être effectués


Utilité
-------

La présence de ces tests nous a permis :

  - De valider les modules au fur et à mesure
  - De valider rapidement les modifications faîtes sur des fichiers
  - De regarder les **OK** hypnotiques qui défilent à l'écran
  



Options du makefile
-------------------

Ce makefile, **à l'exception des autres**, est capable de vérifier si des fichiers présents en dehors de son dossier sont à jour.  
C'est assez pratique, mais c'est une exception.


Compilation : génère les .o du dossier, ainsi que ceux des modules à tester

	make

Tests : Exécute les tests (après avoir compilé si nécessaire)

	# Teste tous les modules, et vérifie les résultats
	make tests
	
	# Teste tous les modules, vérifie les résultat et surveille les fuites mémoires
	make tests_memoire
	make memory_tests
	
	# Teste le module XXX et vérifie les résultats
	make XXX
	
	# Tests le module XXX, vérifie les résultat et surveille les fuites mémoires
	make XXX_memoire

Nettoyage : 

	# Supprime les .o
	make clean
	
	# Supprime les .o, les fichiers en entrée et en sortie, ainsi que les exécutables
	make maxclean
