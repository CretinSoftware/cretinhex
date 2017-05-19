cretinhex
=========



Présentation
------------

Ce dossier contient tout le nécessaire pour compiler l'application *cretinhex*, permettant de jouer au jeu *hex*, 
et répondant au cahier des charges fixé par la consigne de l'UE *Projet S4* (Univ tlse3 - L2 info 2016-2017).

Ce travail a été réalisé par François MAHÉ et Pierre POMERET-COQUOT

Le travail est structuré ainsi :

  - **c/** : coeur de calcul et les IA écrite en C
  - **java/** : application et les interface utilisateur écrites en Java
  - **papiers/** : documents de conception, de spécification et de bilan écrits dans le cadre de l'UE
  - **parametres/** : quelques réglages communs à tout le projet (doxygen et makefiles)


Compilation
-----------

Utilisez le makefile pour compiler l'application entière

	make

Et lancez l'application avec l'exécutable produit

	./mon_premier_programme

Cet exécutable comprend quelques options :

	# Utiliser l'interface graphique
	./mon_premier_programme -ihm [classic|rasta|abeille]
	
	# Paramètres de l'interface en ligne de commande (système unix, largeur du terminal)
	./mon_premier_programme [-ihm console] [-sys=unix] [-l xxx]


Options du makefile
-------------------

Compile

	# Tout
	make [all]
	
	# La partie C
	make c
	
	# La partie Java
	make java

Lance les séries de tests (un avant-goût du dossier c/tests/)

	# Tous les tests
	make tests
	
	# Tous les tests en vérifiant les fuites mémoires
	make tests_memoire
	make memory_tests

Génère la documentation doxygen dans le dossier doc/

	# Tout
	make doc
	
	# La documentation de la partie C
	make cdoc
	
	# La documentation de la partie Java
	make javadoc

Crée le dossier client (sans les codes sources cachés)

	make client

Un peu de nettoyage

	# Nettoie les dossiers c/ et java/
	make [max]clean
	
	# Efface la doc
	make doc-clean
	
	# Grand nettoyage : efface tout ce qui est re-générable
	make maxmaxclean


