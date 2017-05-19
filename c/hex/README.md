cretinhex/c/hex
===============


Description
-----------

Ce dossier contient l'implémentation des types spécifiques au jeu *hex*.

  - **Joueur** : Type énuméré (J0, J1, J2) et ses opérateurs
  - **Damier** : Représente une grille de hex (position des pions)
  - **Partie** : Représente une partie de hex (damier, tour, historique, etc.)
  - **PartieJNI** : Interface JNI (Java Native Interface) offrant les services de *Partie*
  - **GrapheHex** : Graphe simplifié bâti sur un Damier. Rend certains calculs aisés, particulièrement la détection du vainqueur
  - **GrapheHexPlus** : Fonction complémentaires servant au calcul des distances dans le graphe, en considérant ou non les ponts
  * **Minimax** : Arbre Minimax exhaustif adapté au jeu de Hex.

Consultez la documentation pour plus d'informations


GrapheHex
---------

Le GrapheHex est constitué d'un *Graphe (voir c/cretinlib/Graphe.h)* auto-simplifiable : les sommets de même couleur, non vides, sont fusionnés.  
On assue un accès en *O(1)* aux sommets grâce à un métagraphe *(i.e. un tableau associant aux coordonnées d'une case le sommet qui la représente)*

Les fonctions de *GrapheHexPlus* sont assez complexes, et détaillées dans le document de bilan  
*Voir : papiers/Bilan.pdf*


Minimax
-------

L'arbre Minimax utilise cette méthode de notation :

  - En français : *Un placement de pion est gagnant si les bords opposés sont reliés, où si l'adversaire ne peut que perdre au coup suivant. Il est perdant dans les autres cas*
  - En matheux : *Une feuille est notée 1. Un nœud est noté 1 si tous ses fils sont à 0, et noté 0 sinon*

La note qui remonte récursivement est alors relative au joueur dont c'est le tour, est annonce la victoire (ou la défaite) :

  - Du joueur utilisant le minimax au profondeurs impaires
  - De son adversaires aux profondeurs paires

Cela en considérant que la profondeur de la racine est 0


Options du makefile
-------------------

Compilation : génère les .o

	make

Nettoyage : supprime les .o

	make [max]clean

