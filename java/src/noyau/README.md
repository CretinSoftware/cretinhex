cretinhex/java/src/noyau
========================


Description
-----------

Le paquetage *noyau* est organisé autour de trois pôles :

#### Joueur

Le type énuméré **Joueur** est composé de trois valeurs *J0*, *J1* et *J2*.

Il représente la couleur des pions :

 - *J0* : case vide
 - *J1* : joueur blanc
 - *J2* : joueur noir

On s'en sert pour indiquer l'occupant d'une case oo le rôle d'un utilisateur

#### Utilisateur

La classe abstraite **Utilisateur** représentant les personnes assises autour de la table pour jouer à *hex*. 

Ces classes en héritent :

  - **Humain**
  - **IA0** (RandomBot)
  - **GotooneBot**
  - **BridgeBot**

#### Partie

Les classes **Partie** et **PartieJNI** qui stockent et manipulent la partie en cours, et offrent tous les services du jeu (placement de pions, annulation, sauvegarde, etc.)


JNI
---

On notera que la plupart de ces classes ne réalisent pas les calculs elles-mêmes, mais appellent les bibliothèques natives développées en C.

