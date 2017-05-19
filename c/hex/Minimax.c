/**
 * \file Minimax.c
 * \brief Code source de l'IA basée sur la structure decisionnelle Minimax
 * \author Francois Mahe
 * \version 2.0
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
	struct Et_arbre_minimax **configurations_suivantes;
}arbre_mnx_interne;


/**
 * \brief creer une structure decisionnelle pour une IA minimax
 * \param D //le damier donné lors du premier tour de jeu de l'IA
 * \param nbtour //le nombre de tour écoulé dans le damier D
 * \param profondeur // la profondeur du noeud créer
 * \param X //la coordonnée X du noeud creer
 * \param Y //la coordonnée Y du noeud creer
 */
arbre_mnx creer_mnx(Damier D, int nbtour, int profondeur, int X, int Y)
{
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
 * \brief trouve le max de la condition de victoire des noeuds inférieurs
 * \param A // le noeud servant de racine a l'évaluation
 */
int Max_mnx(arbre_mnx A)
{
	int c = 0;
	int i = 0;
	while((i < A->nb_configurations_suivantes) && (c == 0))
	{
		c = A->configurations_suivantes[i++]->vers_victoire;
	}
	return c;
}

/**
 * \brief trouve le min de la condition de victoire des noeuds inférieurs
 * \param A // le noeud servant de racine a l'évaluation
 */
int Min_mnx(arbre_mnx A)
{
	int c = 1;
	int i;
	while((i < A->nb_configurations_suivantes) && (c == 1))
	{
		c = A->configurations_suivantes[i++]->vers_victoire;
	}
	return c;
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
		i++;
	}
	
	return A;
}

/**
 * \brief noter minimax version 2
 * \param A // la racine de l'arbre a noter
 * \note fonction dissociée de la construction pour pouvoir la tester de manière indépendante.
 */
arbre_mnx noter_mnx_V2(arbre_mnx A)
{
	int i;
	for(i = 0; i < A->nb_configurations_suivantes; i++)
	{
		if(A->configurations_suivantes[i]->vers_victoire == -1)
		{
			noter_mnx_V2(A->configurations_suivantes[i]);
		}
	}
	
	if(Max_mnx(A) == 1)
	{
		A->vers_victoire = 0;
	}
	else
	{
		A->vers_victoire = 1;
	}
	
	return A;
}



/**
 *\brief libère l'espace mémoire occupée par le tableau configurations_suivantes d'un noeud
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
 * \param D //le damier du père ( modifié dans la fonction, noeud par noeud )
 * \param tour_de_jeu_en_entree //tour de jeu du nouvel arbre ( incrémenté a l'appel de la fonction, depuis celui du père)
 * \param profondeur //la profondeur du noeud ajouté a l'appel de la fontion
 * \param X //coordonnée X du noeud ajouté
 * \param Y //coordonnée Y du noeud ajouté
 * \param nb_config_suivantes // précalculée puis transmise dpuis l'arbre appellant
 * \param celui_qui_joue //modifié a chaque appel récurcif grace a la fonction Joueur_suivant
 */

arbre_mnx ajouter_mnx(Damier D, int tour_de_jeu_en_entree, int profondeur, int X, int Y, 
											int nb_config_suivantes, Joueur celui_qui_joue)
{
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
		a->vers_victoire = 1;
	}
	
	GrapheHex_libererMemoire(&graphe_damier_du_noeud);		
	
	return a;
}


/**
 * \brief permet de connaitre le nombre de tour joué dans le damier récupéré par l'IA.
 * \param D // le damier sur le quel opérer le calcul
 * \param *nbcoupJ1 // pointeur vers le nombre de coup de J1
 * \param *nbcoupJ2 // pointeur vers le nombre de coup de J2
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
 * \param idIA \ l'identifiant de l'IA (J1 ou J2) utile malgrés sont absence dans la structure, pour pouvoir simmuler la partie en cours et savoir quoi placer sur une case du plateau
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





/**
 *\brief ne sers que pour générer de l'affichage dans des tests et ne serra ps commentée
 */
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

/**
 * \brief ne sers que pour générer de l'affichage dans des tests et ne serra ps commentée
 */
void afficher_mnx(arbre_mnx A, char mode)
{
	afficher_mnx_recursif(A, "Noeud 0", mode);
}


/**
 *\brief recupère le fils contenant la première configuration suivante gagnante dans un arbre_mnx
 *\param A // l'arbre a scanner
 */ 
arbre_mnx obtenir_config_gagnante_mnx(arbre_mnx A)
{
	int i = 0;
	while((A->configurations_suivantes[i]->vers_victoire != 1) && (i < A->nb_configurations_suivantes - 1))
	{
		i++;
	}
	return A->configurations_suivantes[i];
}

/**
 * \brief obtenir X et Y
 * \param A // le noeud possédent les coordonnées
 */

void obtenir_XY_mnx(arbre_mnx A, int *X, int *Y)
{
	*X = A->coord_X;
	*Y = A->coord_Y;
}
	