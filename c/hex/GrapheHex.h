/**
 * \file Graphe.h
 * \brief Fichier header du type GrapheHex.
 * \author Pierre POMERET-COQUOT
 * \version 1.2
 * \date 13 avril 2017
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
 * \brief   Représente le graphe simplifié à 4 points d'entrée
 * \author Pierre POMERET-COQUOT
 *
 * \par Description
 * GrapheHex est un Graphe particulier adapté à la gestion / résolution de parties de Hex.
 * Il dispose de 4 points d'entrée (les bords) appelés ici N, S, E et O.
 * Sa taille étant contrainte par la taille du damier, un tableau servira de méta-graphe.
 *
 *
 *
 *
 * @{
 */
 
 
 
typedef Joueur * GHElement;

GHElement GHElement_init(Joueur j);

Joueur GHElement_valeur(GHElement e);

int GHElement_memeJoueur(GHElement e1, GHElement e2);

int GrapheNoeud_memeJoueur(GrapheNoeud n1, GrapheNoeud n2);

void GHElement_libererMemoire(GHElement * e);



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




/*
 * \brief   Affiche un GrapheHex
 */
void GrapheHex_afficher(GrapheHex g);




GrapheNoeud GrapheHex_nord(GrapheHex g);
GrapheNoeud GrapheHex_sud(GrapheHex g);
GrapheNoeud GrapheHex_est(GrapheHex g);
GrapheNoeud GrapheHex_ouest(GrapheHex g);


/**
 * \brief   Donne le métagraphe associé.
 */
GrapheNoeud * GrapheHex_obtenirMetagraphe(GrapheHex g);

/*
 * \brief   Donne le Graphe associé.
 */
Graphe GrapheHex_obtenirGraphe(GrapheHex g);


/**
 * \brief   Donne la largeur du damier associé
 */
int GrapheHex_largeurDamier(GrapheHex g);


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

/**
 * \brief   Donne les cases correspondant à un noeud
 * \note    La LDC contient des entiers n avec n / largeur = x et n % largeur = y
 */
LDC GrapheHex_casesDuNoeud(GrapheHex g, GrapheNoeud n);


/**
 * \brief    Fusionne deux noeuds en prenant soin du métagraphe
 */
GrapheHex GrapheHex_fusionnerNoeuds(GrapheHex g, GrapheNoeud n1, GrapheNoeud n2);


/**
 * \brief   Donne les noeuds d'un joueur
 * \note    La gestion de la mémoire de la LDC renvoyée est à votre charge.
 */
LDC GrapheHex_groupes(GrapheHex g, Joueur j);

/**
 * \brief    Simplifie tout le graphe (regroupe les J1 contigus, et les J2)
 */
GrapheHex GrapheHex_simplifier(GrapheHex g);

/**
 * \brief    Donne le vainqueur d'après les points d'entrées opposés identiques
 */
Joueur GrapheHex_quiGagne(GrapheHex g);


/**
 * \brief    Donne le(s) plus court(s) chemin(s) pour aller des points d'entrée A vers B
 * \note     La fonction renvoie une LDC de LDC (LDC à deux dimensions). Sa désallocation mémoire est à votre charge.
 */
LDC GrapheHex_plusCourtsChemins(GrapheHex g, GrapheNoeud depart, GrapheNoeud arrivee, Joueur j);





/** @} */



# endif
