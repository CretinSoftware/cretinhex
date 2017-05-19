cretinhex/java/src/ihm/rasta
============================


Description
-----------

Le package **ihm.rasta** fournit les classes nécessaires à l'IHMRasta (affichage graphique)

L'interface graphique est réalisée avec les packages dédiés *awt* et *swing*.  
Les classes développées héritent, pour la plupart, de ces packages.

  - **Fenetre** hérite de JFrame : c'est la fenêtre de l'application. Elle est à l'écoute des événements, et contient tous les composants (menus, boutons, etc.). Elle est capable d'afficher et de redessiner à la demande les cadres.
  - **Cadre** hérite de JPanel, et **CadreAccueil**, **CadreNouvellePartie**, **CadreJeu** et **CadreHisto** en héritent à leur tour. Ces cadres sont les différents contenus à afficher dans la fenêtre
  - **composants** est un sous-paquetage contenant les blocs à dessiner dans les cadres (boutons, images, etc.)
  - **apparences** est un sous-paquetage contenant plusieurs implémentations de l'interface **Apparence**. Ce sont en fait des collections d'images et de couleurs à afficher.
  - **Action** contient la liste des actions (événements) écoutés par la fenêtre, sous forme de constantes.
  - **Contenu** contient les textes à afficher dans les fenêtres (aide, à propos, etc.)
  
  
Fonctionnement
--------------

La fenêtre de l'application est à l'écoute : elle implémente l'interface *ActionListener*.  
C'est aussi le cas de certains composants.

Lorsqu'une action est réalisée, cela provoque l'exécution du code associé :

  - Afficher tel cadre
  - Ouvrir une popup
  - Interagir avec le noyau
  
 