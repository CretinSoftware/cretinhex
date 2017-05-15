#ifndef _MINIMAX_H
#define _MINIMAX_H


#include "Partie.h"
#include "Damier.h"
#include "Joueur.h"

/*
 * \struct arbre_mnx
 * \brief structure de l'IA minimax
 */

typedef struct Et_arbre_minimax *arbre_mnx;



arbre_mnx construir_mnx(Damier D, Joueur idIA);


#endif