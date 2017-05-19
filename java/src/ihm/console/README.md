cretinhex/java/src/ihm/console
==============================


Description
-----------

Le package **ihm.console** fournit les classes nécessaires à l'IHMConsole, en ligne de commande.

On y trouve :

  - La classe abstraite **Page**, dont héritent les **PageAccueil**, **PageOptions**, **PageNouvellePartie**, **PageJeu** et **PageSortie**. Elle permet l'affichage et l'exécution du code correspondant.
  - La classe **Menu**, proposant plusieurs types de menus en ligne de commande : choix parmi des propositions ou des pages, saisie d'un entier, d'une chaîne de caractère, d'une coordonnée de la forme B2.
  
  
Fonctionnement
--------------

La classe **IHMConsole** provoque l'exécution d'une boucle sans fin dans laquelle les pages se succèdent. 
Chaque page doit implémenter la méthode *executer_code()* renvoyant une page, c'est ce renvoi qui sera exécuté en suivant.

La **PageSortie** appelle simplement la fonction *System.exit(0);* afin de terminer l'exécution du programme.