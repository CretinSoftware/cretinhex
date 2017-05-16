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
*/
 


/**
 * struct Et_arbre_minimax
 * \brief /Structure décisionelle de l'IA minimax
 */
typedef struct Et_arbre_minimax
{
	int vers_victoire;
	int hauteur;
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
arbre_mnx creer_mnx(Damier D, int nbtour, int profondeur, int X, int Y)
{
	/* idIA ne sert peut être plus a rien*/
	/* ancienne definition de la fonction : arbre_mnx creer_mnx(Damier D, int nbtour, Joueur idIA)*/
	arbre_mnx a = (arbre_mnx) malloc(sizeof(arbre_mnx_interne));
	assert(a != NULL);
	
	a->vers_victoire = -1;
	a->hauteur = profondeur;
	a->coord_X = X;
	a->coord_Y = Y;
	a->nb_configurations_suivantes = (Damier_obtenirLargeur(D) * Damier_obtenirLargeur(D)) - (nbtour);
	a->damier_du_noeud = NULL;
	a->configurations_suivantes = (arbre_mnx*) calloc(a->nb_configurations_suivantes, sizeof(arbre_mnx));
	
	return a;
}


/**
 * \brief noter minimax
 * \param A // l'arbre Minimax a noter
 */

arbre_mnx noter_mnx(arbre_mnx A)
{
	int i;
	for(i = 0; i < A->nb_configurations_suivantes; i++)
	{
		if(A->configurations_suivantes[i]->vers_victoire == 2)
		{
			noter_mnx(A->configurations_suivantes[i]);
		}
	}
	i = 0;
	A->vers_victoire = 1;
	while ((i < A->nb_configurations_suivantes) && (A->vers_victoire == 1))
	{
		A->vers_victoire = A->configurations_suivantes[i]->vers_victoire;
	}
	/*ATTENTION: Il me semble finalement me rendre compte que l'IA cherche a gagner a coup sûr, les branches quelle suivra serront forcément notée 1, puisque venant de la racine, elle suivra
	 * des branches qui forcément, mène à sa victoire, sans que le joueur n'ai la possibilité de gagner. Elle suivra donc des branches qui auront toute leurs configurations se terminant 
	 * sur une feuille de profondeur impaire, les branches aillant des noeuds se terminant sur des profondeur paire serront forcément élliminées, puisque si le joueurs est bon, il choisira
	 * forcément un coup le faisant gagner si il en a la possibilité. Le fait de se diriger vers une branche faisant perdre l'IA ne serra pas de son fait, mais celui de son adversaire,
	 * adopter une politique de notation différente en fonction d'un noeud de profondeur pair ou impaire est donc inutile, puisque ce n'est pas l'IA qui joue à la place de son adversaire.
	 */
	return A;
}

/**
 *\brief libère l'espace mamoire occupée par le tableau configurations_suivantes d'un noeud
 *\param A //le noeud sur le quel le tableau de configurations_suivantes n'est plus utile
 */

arbre_mnx suprimer_config_suivante_mnx(arbre_mnx A)
{
	int i;
	for(i = 0; i < A->nb_configurations_suivantes; i++)
	{
		free(A->configurations_suivantes[i]);
	}
	A->nb_configurations_suivantes = 0;
	return A;
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

arbre_mnx ajouter_mnx(Damier D, int tour_de_jeu_en_entree, int profondeur, int X, int Y, 
											int nb_config_suivantes, Joueur celui_qui_joue)
{
	arbre_mnx a = creer_mnx(D, tour_de_jeu_en_entree, profondeur, X, Y);
	a->damier_du_noeud = Damier_modifierCase(D, celui_qui_joue, X, Y);
	a->nb_configurations_suivantes = nb_config_suivantes;
	
	/*si l'arbre doit avoir des fils, il faudrait aussi ajouté une condition sur le fait que le damier du noeud puisse être gagnant, dans ce cas, free son tableau de config suivante et return a
	*/
	GrapheHex graphe_damier_du_noeud = GrapheHex_init(a->damier_du_noeud);
	if((a->nb_configurations_suivantes > 0) && (GrapheHex_quiGagne(graphe_damier_du_noeud) == J0))
	{
		/*indice de navigation dans le tableau de configurations suivante du nouvel arbre_mnx
		 */
		int i = 0;
		/*indice de navigation dans le damier du noeud de l'arbre.
		 */
		int j = 0;
		/*tant que le tableau de configurations suivantes du nouvel arbre n'est pas complet
		 */
		while(i < a->nb_configurations_suivantes)
		{
			/*si j est positionné sur une case n'étant pas attribué.
			 */
			if((j < Damier_obtenirLargeur(D) * Damier_obtenirLargeur(D)) && (Damier_obtenirCase(a->damier_du_noeud, j%Damier_obtenirLargeur(D), j/Damier_obtenirLargeur(D)) == J0))
			{
				a->configurations_suivantes[i] = ajouter_mnx(a->damier_du_noeud, tour_de_jeu_en_entree+1, profondeur+1, j%Damier_obtenirLargeur(D), j/Damier_obtenirLargeur(D), 
																										 a->nb_configurations_suivantes-1, Joueur_suivant(celui_qui_joue));
				i++;
			}
			j++;
		}
	}
	else if (a->nb_configurations_suivantes > 0)
	{
		a = suprimer_config_suivante_mnx(a);
	}
	
	if (a->nb_configurations_suivantes == 0)
	{
		if(a->hauteur%2 == 0)
		{
			a->vers_victoire = 0;
		}
		else
		{
			a->vers_victoire = 1;
		}
	}
			
	
	return a;
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
 * l'IA ne donnera 1 que pour les noeud menant vers une victoire en rang (profondeur) impaire.
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
	arbre_mnx a = creer_mnx(D, nbtour, 0, -1, -1);
	a->damier_du_noeud = D;
	
	/*on initialise ensuite chaque configuration suivantes de la racine
	 */
	int i, x, y, largeur;
	largeur = Damier_obtenirLargeur(D);
	for (i = 0; i < a->nb_configurations_suivantes; ++i)
		for (y = 0; y < largeur; ++y)
			for (x = 0; x < largeur; ++x)
				if (Damier_obtenirCase(D, x, y) == J0)
					a->configurations_suivantes[i] = ajouter_mnx(a->damier_du_noeud,
																											 nbtour + 1,
																											 a->hauteur + 1,
					                                             x,
					                                             y,
					                                             a->nb_configurations_suivantes - 1,
					                                             idIA);
		
	return a = noter_mnx(a);
}


/**
 * \brief libère l'espace mémoire occupée par une structure Minimax
 * \param A //la structure minimax a supprimer
 */
void suprimer_mnx(arbre_mnx A)
{
	int i;
	for(i = 0; i < A->nb_configurations_suivantes; i++)
	{
		suprimer_mnx(A->configurations_suivantes[i]);
	}
	free(A);
}


