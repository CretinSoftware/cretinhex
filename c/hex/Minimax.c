/**
 * \file Minimax.c
 * \brief Code source de l'IA basée sur la structure decisionnelle Minimax
 * \author Francois Mahe
 * \version 1.0
 * \date 10 Avril 2017
 *
 * \todo TAD
 * \todo positionner_mnx
 * \todo jouer_mnx
 * \todo noter_mnx
 * \todo toute les fonctions de libération de mémoire
 * 
 * Minimax est une IA destinée a jouer des partie de hex.
 * Il est développé dans le cadre du projet S4 (UPS Tlse3, L2 Info, session 2016-2017).
 *
 *
 * Type abstrait de données dans le fichier header
 * \see Minimax.h
 *     
 */



#include <assert.h>
#include <stdlib.h>
#include "Minimax.h"



/* ATTENTION Vieux shnock : change rien a l'arrache stp ! je pense tenir un bon truc. Dis moi juste ce que t'en pense.
 */

/* 
Salut mec. J'ai eu pas mal d'erreurs à la compilation, tu as le log ci dessous.
Je suis assez surpris que tu n'aies que 3 erreurs et si tu utilises aussi gcc, alors je pense que c'est dû aux makefiles.

Le secret pour compiler avec mes makefiles, c'est de compiler dans le dossier où on travaille (donc, ici, c/hex/)
Le makefile général ne vérifie pas si les .o, si le code a changé, ni rien. S'il trouve des vieux .o, il s'en sert.
Je pense que c'est ça qui a dû jouer. Je ne sais pas trop...
Donc 'cd c/hex && make', ou, sur place, 'make -C c/hex'

Le makefile général appelle celui du dossier c/ UNIQUEMENT si les bibliothèques .so  sont absentes (peu importe si elles sont à jour)
Le makefile du dossier c/ appelle ceux des sous-dossiers UNIQUEMENT si les .o sont absents, de la même manière.
Parfois, 'make maxclean all' (efface et recompile tout) et peut être salutaire, mais bien plus long.


 


CE QUE J'AI CHANGÉ DANS CE FICHIER (15/05)  :

   - Ce grand commentaire
   - Une légère ambiguïté entre le type arbre_mnx (struct * mnx) et les tableaux de type arbre_mnx* (struct ** mnx)
   - L'utilisation du type caché Damier comme s'il était ouvert

Tu verras les modifs ligne par ligne en regardant le dernier commit (bitbucket ou gitg etc)



Sinon ça m'a l'air bien pensé. J'aime bien la façon dont tu codes, et la façon dont tu présente ton code :-)
Allez bon courage et moi je passe à table
 
 
 
 
 
 
 
 
 

kendou@debian:~/Bureau/UPS Tlse 3/S4/Projet S4/cretinhex/c/hex$ make
gcc -Wall -Werror -ansi -fPIC -g -c Minimax.c -o obj/Minimax.o
Minimax.c: In function ‘ajouter_mnx’:
Minimax.c:119:38: error: incompatible type for argument 1 of ‘ajouter_mnx’
     A->configurations_suivantes[i] = ajouter_mnx(A->configurations_suivantes[i], A->damier_du_noeud, idIA, A->tour_de_jeu+1, j%Damier_obtenirLargeur(D), j/Damier_obtenirLargeur(D), 
                                      ^
Minimax.c:86:11: note: expected ‘arbre_mnx’ but argument is of type ‘struct Et_arbre_minimax’
 arbre_mnx ajouter_mnx(arbre_mnx A, Damier D, Joueur idIA, int tour_de_jeu_en_entree, int X, int Y, 
           ^
Minimax.c: In function ‘calcul_nb_tour’:
Minimax.c:148:18: error: dereferencing pointer to incomplete type
  for(i = 0; i < D->largeur * D->largeur; i++)
                  ^
Minimax.c:148:31: error: dereferencing pointer to incomplete type
  for(i = 0; i < D->largeur * D->largeur; i++)
                               ^
Minimax.c:150:7: error: dereferencing pointer to incomplete type
   if(D->cellules[i] != J0)
       ^
Minimax.c:152:8: error: dereferencing pointer to incomplete type
    if(D->cellules[i] == J1)
        ^
Minimax.c: In function ‘construir_mnx’:
Minimax.c:200:12: error: dereferencing pointer to incomplete type
   if((j < D->largeur * D->largeur) && (D->cellules[j] == J0))
            ^
Minimax.c:200:25: error: dereferencing pointer to incomplete type
   if((j < D->largeur * D->largeur) && (D->cellules[j] == J0))
                         ^
Minimax.c:200:41: error: dereferencing pointer to incomplete type
   if((j < D->largeur * D->largeur) && (D->cellules[j] == J0))
                                         ^
Minimax.c:202:128: error: dereferencing pointer to incomplete type
    a->configurations_suivantes[i] = ajouter_mnx(a->configurations_suivantes[i], a->damier_du_noeud, idIA, a->tour_de_jeu+1, j%D->largeur, j/D->largeur,
                                                                                                                                ^
Minimax.c:202:142: error: dereferencing pointer to incomplete type
    a->configurations_suivantes[i] = ajouter_mnx(a->configurations_suivantes[i], a->damier_du_noeud, idIA, a->tour_de_jeu+1, j%D->largeur, j/D->largeur,
                                                                                                                                              ^
Minimax.c:202:37: error: incompatible type for argument 1 of ‘ajouter_mnx’
    a->configurations_suivantes[i] = ajouter_mnx(a->configurations_suivantes[i], a->damier_du_noeud, idIA, a->tour_de_jeu+1, j%D->largeur, j/D->largeur,
                                     ^
Minimax.c:86:11: note: expected ‘arbre_mnx’ but argument is of type ‘struct Et_arbre_minimax’
 arbre_mnx ajouter_mnx(arbre_mnx A, Damier D, Joueur idIA, int tour_de_jeu_en_entree, int X, int Y, 
           ^
Minimax.c: In function ‘suprimer_MNX’:
Minimax.c:221:3: error: incompatible type for argument 1 of ‘suprimer_MNX’
   suprimer_MNX(A->configurations_suivantes[i]);
   ^
Minimax.c:216:6: note: expected ‘arbre_mnx’ but argument is of type ‘struct Et_arbre_minimax’
 void suprimer_MNX(arbre_mnx A)
      ^
Makefile:36: recipe for target 'obj/Minimax.o' failed
make: *** [obj/Minimax.o] Error 1
kendou@debian:~/Bureau/UPS Tlse 3/S4/Projet S4/cretinhex/c/hex$ 

*/




/**
 * \struct Et.arbre_minimax
 * \brief Structure décisionelle de l'IA minimax
 */
typedef struct Et_arbre_minimax
{
	int vers_victoire;
	Joueur qui_est_IA;
	int tour_de_jeu;
	int coord_X;
	int coord_Y;
	int nb_configurations_suivantes;
	Damier damier_du_noeud;
	struct Et_arbre_minimax **configurations_suivantes; /* C'est un tableau : l'adresse d'une liste d'adresses */
}arbre_mnx_interne;


/**
 * \brief creer une structure decisionnelle pour une IA minimax
 * \param D //le damier donné lors du premier tour de jeu de l'IA
 * \
 */
arbre_mnx creer_mnx(Damier D, int nbtour, Joueur idIA)
{
	arbre_mnx a = (arbre_mnx) malloc(sizeof(arbre_mnx));
	assert(a != NULL);
	
	a->qui_est_IA = idIA;
	a->tour_de_jeu = nbtour;
	a->coord_X = -1;
	a->coord_Y = -1;
	a->nb_configurations_suivantes = (Damier_obtenirLargeur(D) * Damier_obtenirLargeur(D)) -(nbtour);
	a->damier_du_noeud = D;
	a->configurations_suivantes = (arbre_mnx*) calloc(a->nb_configurations_suivantes, sizeof(arbre_mnx));
	
	return a;
}

/**
 * \brief ajoute a une racine de type arbre_mnx, les arbres_mnx venant composer son tableau de configurations suivantes. 
 * La fonction est récurcive, les branches sont construites les unes aprés les autres depuis la racine.
 * \param A //le nouvel arbre ( il est créer avant appel de la fonction )
 * \param D //le damier du père ( modifié dans la fonction, noeud par noeud )
 * \param idIA // identificateur de l'IA ( serra utile lors de la notation des branches )
 * \param tour_de_jeu_en_entree //tour de jeu du nouvel arbre ( incrémenté a l'appel de la fonction, depuis celui du père)
 * \param X
 * \param Y
 * \param nb_config_suivantes
 * \param celui_qui_joue / modifié a chaque appel récurcif grace a la fonction Joueur_suivant
 */

arbre_mnx ajouter_mnx(arbre_mnx A, Damier D, Joueur idIA, int tour_de_jeu_en_entree, int X, int Y, 
											int nb_config_suivantes, Joueur celui_qui_joue)
{
	/*parametrage de l'arbre allant être ajouté
	 */
	A->qui_est_IA = idIA;
	A->damier_du_noeud = Damier_modifierCase(D, celui_qui_joue, X, Y);
	A->tour_de_jeu = tour_de_jeu_en_entree;
	A->coord_X = X;
	A->coord_Y = Y;
	A->nb_configurations_suivantes = nb_config_suivantes;
	A->configurations_suivantes = (arbre_mnx*) calloc(A->nb_configurations_suivantes, sizeof(arbre_mnx));
	/*fin du parametrage de l'arbre.
	 */
	
	/*si l'arbre doit avoir des fils
	 */
	if(A->nb_configurations_suivantes > 0)
	{
		/*indice de navigation dans le tableau de configurations suivante du nouvel arbre_mnx
		 */
		int i = 0;
		/*indice de navigation dans le damier du noeud de l'arbre.
		 */
		int j = 0;
		/*tant que le tableau de configurations suivantes du nouvel arbre n'est pas complet
		 */
		while(i < A->nb_configurations_suivantes)
		{
			/*si j est positionné sur une case n'étant pas attribué.
			 */
			if((j < Damier_obtenirLargeur(D) * Damier_obtenirLargeur(D)) && (Damier_obtenirCase(A->damier_du_noeud, j%Damier_obtenirLargeur(D), j/Damier_obtenirLargeur(D)) == J0))
			{
				A->configurations_suivantes[i] = ajouter_mnx(A->configurations_suivantes[i], A->damier_du_noeud, idIA, A->tour_de_jeu+1, j%Damier_obtenirLargeur(D), j/Damier_obtenirLargeur(D), 
																										 A->nb_configurations_suivantes-1, Joueur_suivant(celui_qui_joue));
				i++;
			}
			j++;
		}
	}
	
	return A;
}


/**
 * \brief permet de connaitre le nombre de tour joué dans le damier récupéré par l'IA.
 * \param D
 * \param *nbcoupJ1
 * \param *nbcoupJ2
 */

int calcul_nb_tour(Damier D, int *nbcoupJ1, int *nbcoupJ2)
{
	/*initialisation de chaque contenue d'adresse pour comptage a venir.
	 */
	*nbcoupJ2 = 0;
	*nbcoupJ1 = 0;
	
	/*parcourt de l'intégralité des cases du damier et comptage des coup de J1 et J2
	 */
	/*int i;
	for(i = 0; i < D->largeur * D->largeur; i++)
	{
		if(D->cellules[i] != J0)
		{
			if(D->cellules[i] == J1)
			{
				*nbcoupJ1+=1;
			}
			else
			{
				*nbcoupJ2+=1;
			}
		}
	}*/
	/* On ne peut pas acceder au type caché Damier, (D->largeur, D->cellules) il faut utiliser les opérateurs du .h */
	int x, y, largeur;
	largeur = Damier_obtenirLargeur(D);
	for (y = 0; y < largeur; ++y)
		for (x = 0; x < largeur; ++x)
			if (Damier_obtenirCase(D, x, y) == J1)
				++*nbcoupJ1;
			else if (Damier_obtenirCase(D, x, y) == J2)
				++*nbcoupJ2;
				
	
	return(*nbcoupJ1 + *nbcoupJ2);
}


/**
 * \brief construit un arbre decisionelle de type minimax
 * \param D \ un damier quelquonc en entrée
 * \param idIA \ l'identifiant de l'IA (J1 ou J2)
 * \note joueur idIA désigne ici quel joueur est l'IA ATTENTION idée de génie: pour suprimer la question : a qui c'est de jouer dans mon arbre d'IA ?
 * l'IA peu ne créer son arbre qu'a son premier tour de jeu lors d'une partie et non, au lancement de la partie. 
 * Ainsi, dans l'arbre, l'IA commence toujours par placer ses propre pions dans les arbre succédants a la racine de son arbre, 
 * l'IA ne donnera 1 que pour les noeud menant vers une victoire en rang (prodfondeur) impaire.
 */

arbre_mnx construir_mnx(Damier D, Joueur idIA)
{
	/* deux variables permettant de savoir le nombre de coup jouer par chacuns des deux joueurs au moment ou l'ont recoit le damier. 
	 * elles seront sans doute locale a calcul_nb_tour plus tard dans le dévellopement
	 */
	int nbcoupJ1;
	int nbcoupJ2;
	int nbtour;
	
	nbtour = calcul_nb_tour(D, &nbcoupJ1, &nbcoupJ2);
	/*on creer un arbre, en lui donnant le damier.
	 */
	arbre_mnx a = creer_mnx(D, nbtour, idIA);
	
	/*on initialise ensuite chaque configuration suivantes de la racine
	 */
	/*indice de navigation dans le tableau de configurations suivante du nouvel arbre_mnx
	*/
	/*int i = 0;*/
	/*indice de navigation dans le damier du noeud de l'arbre.
	*/
	/*
	int j = 0;
	while( i < a->nb_configurations_suivantes)
	{
		if((j < D->largeur * D->largeur) && (D->cellules[j] == J0))
		{
			a->configurations_suivantes[i] = ajouter_mnx(a->configurations_suivantes[i], a->damier_du_noeud, idIA, a->tour_de_jeu+1, j%D->largeur, j/D->largeur,
																									 a->nb_configurations_suivantes-1, idIA);
			i++;
		}
		j++;
	}*/
	/* Accès à D->largeur, etc. impossible */
	int i, x, y, largeur;
	largeur = Damier_obtenirLargeur(D);
	for (i = 0; i < a->nb_configurations_suivantes; ++i)
		for (y = 0; y < largeur; ++y)
			for (x = 0; x < largeur; ++x)
				if (Damier_obtenirCase(D, x, y) == J0)
					a->configurations_suivantes[i] = ajouter_mnx(a->configurations_suivantes[i],
					                                             a->damier_du_noeud,
					                                             idIA,
					                                             a->tour_de_jeu + 1,
					                                             x,
					                                             y,
					                                             a->nb_configurations_suivantes - 1,
					                                             idIA);
		
	return a;
}


/**
 * \brief libère l'espace mémoire occupée par une structure Minimax
 * \param A //la structure minimax a supprimer
 */
void suprimer_MNX(arbre_mnx A)
{
	int i;
	for(i = 0; i < A->nb_configurations_suivantes; i++)
	{
		suprimer_MNX(A->configurations_suivantes[i]);
	}
	free(A);
}
	
