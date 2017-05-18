#ifndef _MINIMAX_H
#define _MINIMAX_H


#include "Partie.h"
#include "Damier.h"
#include "Joueur.h"
#include "GrapheHex.h"
#include "assert.h"

/*
 * \struct arbre_mnx
 * \brief structure de l'IA minimax
 */

typedef struct Et_arbre_minimax *arbre_mnx;



arbre_mnx construir_mnx(Damier D, Joueur idIA);
void suprimer_mnx(arbre_mnx A);
arbre_mnx noter_mnx(arbre_mnx A);
arbre_mnx noter_mnx_V2(arbre_mnx A);
arbre_mnx obtenir_config_gagnante_mnx(arbre_mnx A);
void obtenir_XY_mnx(arbre_mnx A, int *X, int *Y);

void afficher_mnx(arbre_mnx A, char mode);



#endif
