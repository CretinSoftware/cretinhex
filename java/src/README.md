cretinhex/java/src
==================


Description
-----------

Code source Java de l'application.

Les classes Java sont réparties dans trois paquetages

  - **cretinplay** : Paquetage contenant uniquement la classe *Application*, dans laquelle se trouve le *main*. Son rôle est de déchiffrer la commande passée, puis de lancer une ihm.
  - **noyau** : L'aspect *calcul* y est rangé. Ce sont les classes de ce paquetage qui communiqunte avec les bibliothèqued natived.
  - **ihm** : Paquetage des différentes IHM proposées (ligne de commande et affichage graphique). Elles répondent toutes deux à la même interface, et permettent à l'utilisateur d'interagir avec le noyau.


Cette séparation entre l'interface et le noyau est directement inspirée de nos cours d'IHM au semestre dernier.





