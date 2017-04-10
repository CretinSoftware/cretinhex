/**
 * \file Minimax.c
 * \brief Code source de l'IA basée sur la structure decisinoelle Minimax
 * \author Francois Mahe
 * \version 1.0
 * \date 10 Avril 2017
 *
 * \todo TAD
 * \todo finir init_mnx
 * \todo contruir_mnx
 * \todo positionner_mnx
 * \todo et tout le reste...
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



/**
 * \struct Et.arbre_minimax
 * \brief Structure décisionelle de l'IA minimax
 */
typedef struct Et.arbre_minimax
{
	int vers_victoire;
	int premier_joueur;
	int tour_de_jeu;
	int coord_X;
	int coord_Y;
	Partie partie_courante;
	Damier damier_du_noeud;
	struct Et.arbre_minimax** configurations_suivantes;
}arbre_mnx_interne;


/**
 * \brief initialise un pointeur de type arbre_mnx
 * \param p
 */

arbre_mnx init_mnx(Partie P)
{
	arbre_mnx a = (arbre_mnx) malloc(sizeof(arbre_mnx));
	assert(arbre_mnx != NULL);
	
	a->partie_courante = P;
	a->premier_joueur = //premier joueur de la partie == IA
	Damier damier_du_noeud = NULL;
	return a;
}



/**
 * \brief ajoute un arbre_mnx a un arbre_mnx ( créer et ajoute un fils )
 * \param racine
 * \param X
 * \param Y
 */

arbre_mnx ajouter_mnx(arbre_mnx racine, int x, int y)
{
	if (racine->damier_du_noeud == NULL)
	{
		racine->tour_de_jeu = Partie_obtenirTour(racine->partie_courante);
		racine->coord_X = x;
		racine->coord_Y = y;
		racine->damier_du_noeud = Partie_obtenirDamier(racine->partie_courante);
		configurations_suivantes = (configurations_suivantes) calloc(damier_du_noeud->largeur * damier_du_noeud->largeur, arbre_mnx);
	}
	else
	{
		arbre_mnx fils = (arbre_mnx) malloc(sizeof(arbre_mnx));
		assert(fils != NULL);
		
		fils->tour_de_jeu = racine->tour_de_jeu+1;
		fils->coord_X = x;
		fils->coord_Y = y;
		
		
		