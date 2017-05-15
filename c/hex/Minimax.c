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
#include "Minimax.h"
#include "Partie.h"
#include "Damier.h"
#include "Joueur.h"


/* ATTENTION Vieux shnock : change rien a l'arrache stp ! je pense tenir un bon truc. Dis moi juste ce que t'en pense.


/**
 * \struct Et.arbre_minimax
 * \brief Structure décisionelle de l'IA minimax
 */
typedef struct Et.arbre_minimax
{
	int vers_victoire;//booleen
	Joueur qui_est_IA;
	int tour_de_jeu;
	int coord_X;
	int coord_Y;
	int nb_configurations_suivantes;
	Damier damier_du_noeud;
	struct Et.arbre_minimax* configurations_suivantes;
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
	a->tour_de_jeu = nbtour
	a->coord_X = -1;
	a->coord_Y = -1;
	a->nb_configurations_suivantes = (D->largeur * D->largeur)-(nbtour);
	a->damier_du_noeud = D;
	a->configurations_suivantes = (arbre_mnx) calloc(a->nb_configurations_suivantes, arbre_mnx);//vérifier la syntaxe des fonctions calloc
	
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
	//parametrage de l'arbre allant être ajouté
	A->qui_est_IA = idIA;
	A->damier_du_noeud = Damier_modifierCase(D, celui_qui_joue, X, Y);
	A->tour_de_jeu = tour_de_jeu_en_entree;
	A->coord_X = X;
	A->coord_Y = Y;
	A->nb_configurations_suivantes = nb_config_suivantes
	A->configurations_suivantes = (arbre_mnx) calloc(A->nb_configurations_suivantes, arbre_mnx);//verif syntaxe
	//fin du parametrage de l'arbre.
	
	//si l'arbre doit avoir des fils
	if(A->nb_configurations_suivantes > 0)
	{
		int i = 0;//indice de navigation dans le tableau de configurations suivante du nouvel arbre_mnx
		int j = 0;//indice de navigation dans le damier du noeud de l'arbre.
		while(i < A->nb_configurations_suivantes)//tant que le tableau de configurations suivantes du nouvel arbre n'est pas complet
		{
			//si j est positionné sur une case n'étant pas attribué.
			if((j < D->largeur * D->largeur) && (A->damier_du_noeud->cellules[j] == J0))
			{
				A->configurations_suivantes[i] = ajouter_mnx(A->configurations_suivantes[i], A->damier_du_noeud, idIA, A->tour_de_jeu +1, j%D->largeur, j/D->largeur, 
																										 nb_config_suivantes-1, Joueur_suivant(celui_qui_joue);
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
	//initialisation de chaque contenue d'adresse pour comptage a venir.
	*nbcoupJ2 = 0;
	*nbcoupJ1 = 0;
	
	//parcourt de l'intégralité des cases du damier et comptage des coup de J1 et J2
	for(int i = 0; i < D->largeur * D->largeur; i++)
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
	}
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
	//on creer un arbre, en lui donnant le damier.
	arbre_mnx a = creer_mnx(D, nbtour, idIA);
	
	//on initialise ensuite chaque configuration suivantes de la racine
	int i = 0;//indice de navigation dans le tableau de configurations suivantes
	int j = 0;//indice de navigation dans le damier du noeud
	while( i < a->nb_configurations_suivantes)
	{
		if((j < D->largeur * D->largeur) && (D->cellules[j] == J0))
		{
			a->configurations_suivantes[i] = ajouter_mnx(a->configurations_suivantes[i], a->damier_du_noeud, idIA, a->tour_de_jeu +1, j%D->largeur, j/D->largeur,
																									 a->configurations_suivantes -1, idIA);
			i++;
		}
		j++
	}
	return a;
}


/**
 * \brief libère l'espace mémoire occupée par une structure Minimax
 * \param A //la structure minimax a supprimer
 */
void suprimer_MNX(arbre_mnx A)
{
	for(int i = 0; i < A->nb_config_suivantes; i++)
	{
		suprimer_MNX(
		

// a finir !! (voir les todo)
