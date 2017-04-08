/**
 * \file Graphe.h
 * \brief Fichier header du type GrapheHex.
 * \author Pierre POMERET-COQUOT
 * \version 1.0
 * \date 5 avril 2017
 *
 */


# ifndef __GRAPHEHEX__
# define __GRAPHEHEX__

# include "Damier.h"
# include "../cretinlib/Graphe.h"

# include <stdio.h>
# include <stdlib.h>
# include <assert.h>



/**
 * \defgroup pack_hex_GrapheHex GrapheHex
 * \ingroup pack_hex
 * \author Pierre POMERET-COQUOT
 * \version 1.0
 * \date 4 avril 2017
 *
 * \par Description
 * GrapheHex est un Graphe particulier adapté à la gestion / résolution de parties de Hex.
 * Il dispose de 4 points d'entrée (les bords) appelés N, S, E et O.
 * Sa taille étant contrainte par la taille du damier, un tableau servira de méta-graphe.
 *
 *
 * \par Type abstrait de données
 * \todo TAD
 *
 *
 * @{
 */



typedef struct GrapheHex * GrapheHex;


/**
 * \brief    Initialise un GrapheHex
 * \param    d Le damier à représenter
 *
 * \par      Description
 * L'initialisation produit, en plus de l'allocation mémoire, l'édition de
 * tous les liens reliant les noeuds du graphe.
 */
GrapheHex GrapheHex_init(Damier d);


/**
 * \brief    Libère la mémoire allouée à un GrapheHex
 */
void GrapheHex_libererMemoire(GrapheHex * g);


/**
 * \brief    Modifie la valeur d'une case, et simplifie le graphe si besoin
 * \param    g Le graphe à modifier
 * \param    x 1ère coordonnée
 * \param    y 2nde coordonnée
 * \param    j La valeur (de type Joueur) à placer dans la case
 */
GrapheHex GrapheHex_modifierCase(GrapheHex g, int x, int y, Joueur j);


/**
 * \brief    Récupère le noeud corrspondant à une case
 * \param    g Le graphe à consulter
 * \param    x 1ère coordonnée
 * \param    y 2nde coordonnée
 */
GrapheNoeud GrapheHex_obtenirNoeud(GrapheHex g, int x, int y);









/** @} */



# endif
