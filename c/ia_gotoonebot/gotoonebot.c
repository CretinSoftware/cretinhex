#include "gotoonebot.h"
#include <stdlib.h>



typedef struct Et_gotoone
{
	Joueur qui_suis_je;
	arbre_mnx mon_jeu;
}gotoone_interne;

/**
 * \brief initialise une IA basée sur la structure de donnée Minimax
 * \param qui_est_ce // l'identité de l'IA
 */

gotoone gotoone_init(Joueur qui_est_ce)
{
	gotoone Le_gotoone = (gotoone) malloc(sizeof(gotoone_interne));
	/* Le_gotoone est un genre de batman super fort du hex, comme Le Batman est : Le Batman, Le Gotoone se doit d'être Le Gotoone*/
	Le_gotoone->qui_suis_je = qui_est_ce;
	Le_gotoone->mon_jeu = NULL;
	return Le_gotoone;
}

/**
 * \brief fais jouer une IA de type gotoonebot
 * \param le_gotoone // l'IA gotoonebot allant jouer
 * \param D // le damier que va manipuler l'IA
 * \param *X // @ de la coordonée X sur le plateau de jeu
 * \param *Y // @ de la coordonnée Y sur le plateau de jeu
 */
void gotoone_jouer(gotoone le_gotoone, Damier D, int *X, int *Y)
{
	arbre_mnx memoire_mnx;
	le_gotoone->mon_jeu = construir_mnx(D, le_gotoone->qui_suis_je);
	le_gotoone->mon_jeu = noter_mnx_V2(le_gotoone->mon_jeu);
	memoire_mnx = le_gotoone->mon_jeu;
	
	le_gotoone->mon_jeu = obtenir_config_gagnante_mnx(le_gotoone->mon_jeu);
	obtenir_XY_mnx(le_gotoone->mon_jeu, X, Y);
	
	suprimer_mnx(memoire_mnx);
	//on peut pas actuellement suprimer le_gotoone car on en a besoin au tours suivants, il faudrait le free a la fin de la partie, mais a quel moment est-il déjà initialisé ?
	
}


/**
 * \brief libère l'espace mémoire alloué a une IA de type gotoonebot
 * \param G // l'IA a suprimer
 */
void suprimer_gotoone(gotoone G)
{
	if(G->mon_jeu != NULL)
	{
		suprimer_mnx(G->mon_jeu);
	}
	free(G);
}

		
