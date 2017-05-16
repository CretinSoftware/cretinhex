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

int GrapheNoeud_estJ0(GrapheNoeud n);
int GrapheNoeud_estJ1(GrapheNoeud n);
int GrapheNoeud_estJ2(GrapheNoeud n);

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
 * \brief   Trouve les noeuds accessibles en n coups
 * \param   g      Le graphe à fouiller
 * \param   noeud  Le noeud depuis lequel on cherche
 * \param   n      Le nombre de coups pour atteindre les cases
 * \param   j      Le joueur qui cherche à poser ses pions
 * \param   ponts  La taille des ponts à prendre en compte
 * \return  Une LDC de (n+1) LDC de noeuds, où :
 *            - la 0ème contient le noeud passé en argument
 *            - les ièmes contiennent les noeuds joignables en i coup minimum
 */
LDC GrapheHex_noeudsAccessiblesEnNCoups(GrapheHex g, GrapheNoeud noeud, int n, Joueur j, int ponts);

/**
 * \brief    Fusionne deux noeuds en prenant soin du métagraphe
 */
GrapheHex GrapheHex_fusionnerNoeuds(GrapheHex g, GrapheNoeud n1, GrapheNoeud n2);

/**
 * \brief    Simplifie tout le graphe (regroupe les J1 contigus, et les J2)
 */
GrapheHex GrapheHex_simplifier(GrapheHex g);

/**
 * \brief    Donne le vainqueur d'après les points d'entrées opposés identiques
 */
Joueur GrapheHex_quiGagne(GrapheHex g);




/** @} */



# endif
