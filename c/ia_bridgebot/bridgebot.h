/**
 * \file      bridgebot.h
 * \brief     Fichier header du BridgeBot
 * \author    Pierre Pomeret-Coquot
 * \version   1
 * \date      14 avril 2017
 */

# ifndef __CRETINHEX_BRIDGEBOT__
# define __CRETINHEX_BRIDGEBOT__

# define BRIDGEBOT_PONTS 0 
# define BRIDGEBOT_DEBUG 1


# include "../hex/Joueur.h"
# include "../hex/Damier.h"
# include "../hex/GrapheHexPlus.h"





/**
 * \defgroup pack_ia_bridgebot BridgeBot
 * \ingroup  pack_ia
 * \brief    IA jouant grâce à la détection de ponts
 *
 * \par      Description
 * BridgeBot est une IA qui trouve les plus courts chemins pour aller à la victoire, 
 * pour elle-même et son adversaire.
 * Elle cherche le meilleur compromis pour terminer son chemin en empêchant l'adversaire de faire la même chose.
 * @{
 */




typedef struct BridgeBot * BridgeBot;



/**
 * \brief    Initialise un bridgebot
 */
void BridgeBot_init();

/**
 * \brief    Demande à un BridgeBot ce qu'il ferait sur un tel damier
 */
void BridgeBot_jouer(Damier d, int joueur, int * x, int * y);


/** @} */

# endif
