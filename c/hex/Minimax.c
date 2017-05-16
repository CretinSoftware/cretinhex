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
		if(A->configurations_suivantes[i]->vers_victoire == -1)
		{
			A->configurations_suivantes[i] = noter_mnx(A->configurations_suivantes[i]);
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
	
	/*NOTE: Il me semble que je ne suis pas tout à fait d'accord avec ta boucle while. 
	 * Elle dit qu'un noeud est gagnant si tous ses fils sont gagnants, ce qui n'est pas vrai.
	 *
	 * D'après moi il y a deux façons de voir la chose, les deux ressemblent assez à ta solution, mais pas pile :
	 * 
	 * Solution 1. La note 1 veut dire que l'ia gagne, la note 0 veut dire que l'ia perd.
	 * Dans ce cas, la notation dépend de la profondeur du noeud (i.e. de qui va poser le pion)
	 * Si l'ia va poser le pion, alors un fils gagnant (note = 1) suffit : l'ia le choisira
	 * Si l'adversaire va poser le pion, alors un fils perdant (note = 0) suffit pour perdre, il faudrait tous les fils gagnant (note = 1) pour gagner
	 *
	 * Solution 2. La note 1 veut dire que celui qui va poser le pion va gagner (donc, selon la profondeur, c'est l'ia ou son adversaire)
	 * Dans ce cas, un noeud est perdant (note = 0) si l'un de ses fils est gagnant (note = 1)
	 * car un joueur est perdant si au coup suivant l'adversaire est gagnant.
	 *
	 * Je pense que les deux marchent.
	 * L'ia cherche donc un coup parmi les fils de la racine (situation actuelle) qui est noté 1 
	 * 
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
	printf("prof=%d x=%d y=%d\n", profondeur, X, Y);
	arbre_mnx a = creer_mnx(D, tour_de_jeu_en_entree, profondeur, X, Y);
	a->damier_du_noeud = Damier_modifierCase(Damier_copier(D), celui_qui_joue, X, Y);
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
	
	GrapheHex_libererMemoire(&graphe_damier_du_noeud);		
	
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
	a->damier_du_noeud = Damier_copier(D);
	
	/*on initialise ensuite chaque configuration suivantes de la racine
	 */
	int i, x, y, largeur;
	largeur = Damier_obtenirLargeur(D);
	i = 0;
	for (y = 0; y < largeur; ++y)
		for (x = 0; x < largeur; ++x)
			if (Damier_obtenirCase(D, x, y) == J0){
				a->configurations_suivantes[i] = ajouter_mnx(a->damier_du_noeud,
				                                             nbtour + 1,
				                                             a->hauteur + 1,
				                                             x,
				                                             y,
				                                             a->nb_configurations_suivantes - 1,
				                                             idIA);
				++i;
			}
		
	/*return a = noter_mnx(a);*/
	return a;
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
		/* Supprime récursivement les sous-arbres */
		suprimer_mnx(A->configurations_suivantes[i]);
	}
	/* Supprime le tableau */
	free(A->configurations_suivantes);
	
	/* Supprime le damier */
	Damier_libererMemoire(&(A->damier_du_noeud));
	
	/* Supprime la structure */
	free(A);
}







void afficher_mnx_recursif(arbre_mnx A, const char * legende, char mode)
{
	char str[256];
	int i;
	
	printf("%s", legende);
	switch (A->vers_victoire)
	{
		case 1: sprintf(str, "gagnant"); break;
		case 0: sprintf(str, "perdant"); break;
		default:sprintf(str, "?"); break;
	}
	switch (mode)
	{
		case 'v':
			printf("  vers_victoire = %s\n", str);
			printf("  hauteur       = %d\n", A->hauteur);
			printf("  coord_X       = %d\n", A->coord_X);
			printf("  coord_Y       = %d\n", A->coord_Y);
			printf("  nb_conf_suiv  = %d\n\n", A->nb_configurations_suivantes);
			break;
		default:
			printf(" -> %s\n", str);
	}
	
	for (i = 0; i < A->nb_configurations_suivantes; ++i)
	{
		sprintf(str, "%s -> %d", legende, i);
		afficher_mnx_recursif(A->configurations_suivantes[i], str, mode);
	}
}

void afficher_mnx(arbre_mnx A, char mode)
{
	afficher_mnx_recursif(A, "Noeud 0", mode);
}



