/**
 * \file Graphe.h
 * \brief Fichier header du type Graphe.
 * \author Pierre POMERET-COQUOT
 * \version 1.0
 * \date 3 avril 2017
 *
 */
# ifndef __CRETIN_GRAPHE__
# define __CRETIN_GRAPHE__

# include "LDC.h"





/**
 * \defgroup pack_cretinlib_Graphe Graphe
 * \ingroup pack_cretinlib
 * \author Pierre POMERET-COQUOT
 * \version 1.0
 * \date 3 avril 2017
 *
 * \par Description
 * \todo Rapide description
 *
 *
 * \par Type abstrait de données
 *
 * <pre style="line-height:1.1em;">
 * Sorte :            Graphe
 * 
 * Utilise :          GrapheNoeud, LDC
 *
 * Constructeurs :    init :                            pointsEntree[] → Graphe
 *                    insererNoeud :       GrapheNoeud x GrapheNoeud[] → Graphe
 *
 * Opérateurs :       libererMemoire :                          Graphe → __
 *
 * </pre>
 *
 * @{               
 */


typedef struct Graphe * Graphe;





/**
 * \defgroup pack_cretinlib_GrapheElement GrapheElement
 * 
 * \par Description
 * Type manipulé par les Graphes, dans lesquels vous pouvez stocker vos &laquo; trucs &raquo;
 *
 * 
 * @{               
 */

typedef void * GrapheElement;                           /**< Pointeur vers un truc externe, pour être contenu dans un LDCElement */
typedef void (*GrapheElementFree)(GrapheElement *);     /**< Callback pour libérer la mémoire allouée à un LDCElement par un script externe */
/** @} */











/**
 * \defgroup pack_cretinlib_GrapheNoeud GrapheNoeud
 * 
 * \par Description
 * Type manipulé par les Graphes, dans lesquels vous pouvez stocker vos &laquo; trucs &raquo;
 *
 * \par Type abstrait de données
 * <pre style="line-height: 1em;">
 *
 * Sorte :           GrapheNoeud
 *
 * Utilise :         GrapheElement (void *)
 *                   GrapheElementFree (fonction supprimant l'élément)
 *
 * Constructeur :    init :                GrapheElement, GrapheElementFree → GrapheNoeud
 *
 * Opérateurs :      obtenirElement :                           GrapheNoeud → GrapheElement
 *                   obtenirVoisins :                           GrapheNoeud → LDC (GrapheNoeud[])
 *                   fusionner :                  GrapheNoeud x GrapheNoeud → GrapheNoeud
 *                   libererMemoire :                           GrapheNoeud → __
 *
 * </pre>
 * 
 * @{               
 */

typedef struct GrapheNoeud * GrapheNoeud;                           /**< Noeud d'un Graphe */




/**
 * \brief   Initialise un GrapheNoeud
 * \param   e L'élément contenu dans ce noeud
 * \param   free Fonction pour effacer l'élément, ou NULL
 * \return  Le noeud initialisé
 */
GrapheNoeud GrapheNoeud_init(GrapheElement e, GrapheElementFree free);


/**
 * \brief   Récupère l'élément contenu dans un noeud
 */
GrapheElement GrapheNoeud_obtenirElement(GrapheNoeud noeud);


/**
 * \brief   Donne la liste des noeuds voisins
 */
LDC GrapheNoeud_obtenirVoisins(GrapheNoeud noeud);


/**
 * \brief   Fusionne deux noeuds dans le premier
 * \param   n1 Le premier noeud
 * \param   n2 Le noeud à fusionner dans le premier
 * \return  Le premier noeud fusionné avec le second
 */
GrapheNoeud GrapheNoeud_fusionner(GrapheNoeud n1, GrapheNoeud n2);


/**
 * \brief   Libère la mémoire allouée à un noeud
 * \note    Libère aussi la mémoire allouée à l'élément avec la fonction GrapheElementFree fournit à l'initialisation, si différente de NULL
 */
void GrapheNoeud_libererMemoire(GrapheNoeud * noeud);


 
/** @} */









/* Graphe */

/**
 * \param   nbPointsEntree  Le nombre de points d'entrée du graphe
 * \return  Un graphe initialisé
 */
Graphe Graphe_init(int nbPointsEntree);

/**
 * \brief Donne ne nombre de points d'entrées (passé lors de l'initialisation)
 */
int Graphe_nbPointsEntree(Graphe g);

/**
 * \brief   Récupère un point d'entrée (un noeud sans valeur)
 * \param   g Le graphe en question
 * \param   i L'indice du point d'entrée
 * \return  Le graphe mis à jour
 * \req     0 &le; i &lt; Graphe_nbPointsEntree(g)
 */
GrapheNoeud Graphe_pointEntree(Graphe g, int i);

/**
 * \brief   Insertion d'un noeud
 * \param   noeud Le noeud à insérer, correctement initialisé
 * \param   voisins Une LDC contenant les noeuds voisins
 * \return  Le graphe mis à jour
 * \todo    Faire la fonction Graphe_insererNoeud()
 */
Graphe Graphe_insererNoeud(Graphe g, GrapheNoeud noeud, GrapheNoeud * voisins, int nbVoisins);

/**
 * \brief   Libère la mémoire allouée à un Graphe
 * \attention Ne libère pas la mémoire allouée aux noeuds !
 * \todo    Trouver l'heuristique permettant de nettoyer tous les noeuds
 */
void Graphe_libererMemoire(Graphe * g);






/** @} */
# endif
