/**
 * \file Graphe.h
 * \brief Fichier header du type Graphe.
 * \author Pierre POMERET-COQUOT
 * \version 2
 * \date 13 avril 2017
 *
 */
# ifndef __CRETIN_GRAPHE__
# define __CRETIN_GRAPHE__

# include "LDC.h"
# include "utile.h"





/**
 * \defgroup pack_cretinlib_Graphe Graphe
 * \ingroup pack_cretinlib
 * \author Pierre POMERET-COQUOT
 *
 * \par Description
 * Permet la manipulation de graphe (noeuds et liens entre les noeuds)
 * depuis leurs points d'entrée/
 *
 * La structure manipule et renvoie des LDC. D'une manière générale, la libération de la mémoire
 * se fait naturellement grâce aux fonctions spécifiques à cette structure.
 * Néanmoins, il faut parfois libérer manuellement la mémoire (avec Graphe_tousLesNoeuds par exemple).
 *
 * Merci de consulter la documentation des fonctions en question
 *
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
typedef int  (*GrapheElementEgal)(GrapheElement, GrapheElement); /**< Affirme que deux éléments sont égaux, ou non */

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




/*-
 * \brief Égalité de noeuds : même adresse
 */
int GrapheNoeud_estEgal(GrapheNoeud n1, GrapheNoeud n2);


/**
 * \brief   Initialise un GrapheNoeud
 * \param   e L'élément contenu dans ce noeud
 * \param   free Fonction pour effacer l'élément, ou NULL
 * \return  Le noeud initialisé
 */
GrapheNoeud GrapheNoeud_init(GrapheElement e, GrapheElementFree free);

void GrapheNoeud_afficher(GrapheNoeud n);


/**
 * \brief   Récupère l'élément contenu dans un noeud
 */
GrapheElement GrapheNoeud_obtenirElement(GrapheNoeud noeud);


/**
 * \brief   Donne la liste des noeuds voisins
 * \note    Il ne faut pas libérer la mémoire de la LDC renvoyée
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
 * \param   pointsEntree  Les points d'entrée sous forme d'une LDC de GrapheNoeud
 * \return  Un graphe initialisé
 */
Graphe Graphe_init(LDC pointsEntree);

void Graphe_afficher(Graphe g);
/**
 * \brief Donne ne nombre de points d'entrées (passé lors de l'initialisation)
 */
int Graphe_nbPointsEntree(Graphe g);

/**
 * \brief   Récupère un point d'entrée (un noeud sans valeur)
 * \param   g Le graphe en question
 * \param   i L'indice du point d'entrée
 * \return  Le graphe mis à jour
 * \pre     0 &le; i &lt; Graphe_nbPointsEntree(g)
 */
GrapheNoeud Graphe_pointEntree(Graphe g, int i);

/**
 * \brief   Récupère tous les points d'entrée
 * \param   g Le graphe en question
 * \return  Tous les points d'entrées
 * \note    Il ne faut pas libérer la mémoire de la LDC renvoyée.
 */
LDC Graphe_pointsEntree(Graphe g);

/**
 * \brief  Dit si un noeud est un point d'entrée
 */
int Graphe_estPointEntree(Graphe g, GrapheNoeud n);

/**
 * \brief   Renvoie tous les noeuds du graphe
 * \param   g    Le graphe à fouiller
 * \return  Une LDC contenant tous les noeuds du graphe (mais pas les points d'entrée)
 */
LDC Graphe_tousLesNoeuds(Graphe g);

/**
 * \brief   Trouve un noeud dont l'élément est égal à celui recherché
 * \param   g    Le graphe à fouiller
 * \param   e    L'élément à comparer
 * \param   egal Fonction pour comparer les éléments
 * \return  Le noeud trouvé, ou NULL
 */
GrapheNoeud Graphe_trouverNoeud(Graphe g, GrapheElement e, GrapheElementEgal egal);

/**
 * \brief   Renvoie tous les noeuds du graphe
 * \param   g    Le graphe à fouiller
 * \return  Une LDC contenant tous les noeuds du graphe (mais pas les points d'entrée)
 * \note    Il faut libérer manuellement la mémoire de la LDC renvoyée.
 */
LDC Graphe_tousLesNoeuds(Graphe g);

/**
 * \brief   Trouve un noeud dont l'élément est égal à celui recherché
 * \param   g    Le graphe à fouiller
 * \param   e    L'élément à comparer
 * \param   egal Fonction pour comparer les éléments
 * \return  Le noeud trouvé, ou NULL
 */
GrapheNoeud Graphe_trouverNoeud(Graphe g, GrapheElement e, GrapheElementEgal egal);

/**
 * \brief   Insertion d'un noeud
 * \param   g Le graphe dans lequel insérer
 * \param   noeud Le noeud à insérer, correctement initialisé
 * \param   voisins Les noeuds voisins
 * \param   nbVoisins Le nombre de voisins
 * \return  Le graphe mis à jour
 */
Graphe Graphe_insererNoeud(Graphe g, GrapheNoeud noeud, GrapheNoeud * voisins, int nbVoisins);

/**
 * \brief   Fusionne deux noeuds dans le graphe
 */
Graphe Graphe_fusionner(Graphe g, GrapheNoeud n1, GrapheNoeud n2);

/**
 * \brief   Libère la mémoire allouée à un Graphe
 * \attention Ne libère pas la mémoire allouée aux noeuds !
 * \todo    Trouver l'heuristique permettant de nettoyer tous les noeuds
 */
void Graphe_libererMemoire(Graphe * g);






/** @} */
# endif
