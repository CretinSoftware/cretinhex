/**
 * \file      gotoonebot.h
 * \brief     Fichier header du gotoonebot
 * \author    Francois Mahe
 * \version   1
 */

#ifndef _GOTOONEBOT_H
#define _GOTOONEBOT_H

#include "../hex/Damier.h"
#include "../hex/Minimax.h"
#include "../hex/Joueur.h"

typedef struct Et_gotoone *gotoone;

gotoone gotoone_init(Joueur qui_est_ce);
void gotoone_jouer(gotoone le_gotoone, Damier D, int *X, int *Y);
void suprimer_gotoone(gotoone G);



#endif
