/**
 * \file Graphe.c
 * \brief Implémentation du type GrapheHex.
 * \author Pierre POMERET-COQUOT
 * \version 1.0
 * \date 5 avril 2017
 *
 */



# include "GrapheHex.h"



/**
 * Constantes perso, juste pour ne pas se mélanger les pinceaux.
 * 
 * D'un point de vue technique, l'ordre n'importe pas, tant qu'on le respecte.
 */
# define NORD  0
# define SUD   1
# define EST   2
# define OUEST 3


/**
 * \struct GrapheHex
 * \ingroup pack_hex_GrapeHex
 * @{
 */

typedef struct GrapheHex {
	Graphe graphe;                /**< Graphe : le support */
	GrapheNoeud * metagraphe;     /**< Métagraphe : tableau de pointeurs vers les noeuds */
	int largeurDamier;            /**< La largeur du métagraphe */
} GrapheHexInterne;
/** @} */



/**
 * \fn       GrapheHex GrapheHex_init(Damier d)
 * \brief    Initialise un GrapheHex
 * \param    d Le damier à représenter
 *
 * \par      Description
 * L'initialisation produit, en plus de l'allocation mémoire, l'édition de
 * tous les liens reliant les noeuds du graphe.
 *
 * \par      Orientation du damier
 * Les connections des noeuds sont faites pour un damier orienté comme suit :
 * <pre>
 *  # # # #
 *   # # # #
 *    # # # #
 *     # # # #
 * </pre>
 * @{
 */

void free_Joueur(Joueur ** ptr){
	free(*ptr);
	*ptr = NULL;
}

GrapheHex GrapheHex_init(Damier d){
	GrapheHex g;
	GrapheNoeud noeud;
	GrapheNoeud voisins[4];    /*< Dans l'algo qui suit, on ajoute les noeuds par 4 maximum */
	Joueur * ptJ;
	int n, x, y;
	
	/* Allocation mémoire */
	g = (GrapheHex) malloc(sizeof(GrapheHexInterne));
	assert(g != NULL);
	g->graphe = Graphe_init(4);
	
	g->largeurDamier = Damier_obtenirLargeur(d);
	
	g->metagraphe = (GrapheNoeud *) malloc(sizeof(GrapheNoeud) * g->largeurDamier * g->largeurDamier);
	assert(g->metagraphe != NULL);
	
	
	
	/* Placement des noeuds */
	for (y = 0; y < g->largeurDamier; ++y){
		for (x = 0; x < g->largeurDamier; ++x){
			
			/* Nombre de noeuds */
			n = 0;
			
			/* Allocation mémoire */
			ptJ = (Joueur *) malloc(sizeof(Joueur));
			assert(ptJ != NULL);
			*ptJ = Damier_obtenirCase(d, x, y);
			
			noeud = GrapheNoeud_init(ptJ, (GrapheElementFree) free_Joueur);
			
			g->metagraphe[y*g->largeurDamier + x] = noeud;
			
			/* Première ligne : ajout de NORD */
			if (y == 0){
				voisins[n++] = Graphe_pointEntree(g->graphe, NORD);
			}
			/* Autres lignes : ajout du voisin de dessus (en haut à gauche) */
			else {
				voisins[n++] = g->metagraphe[(y-1)*g->largeurDamier + x];
			}
			/* Première colonne : ajout OUEST */
			if (x == 0){
				voisins[n++] = Graphe_pointEntree(g->graphe, OUEST);
			}
			/* Autres colonnes : ajout du voisin de gauche */
			else {
				voisins[n++] = g->metagraphe[y*g->largeurDamier + x - 1];
			}
			/* Dernière ligne, ajout de SUD */
			if (y == g->largeurDamier-1){
				voisins[n++] = Graphe_pointEntree(g->graphe, SUD);
			}
			/* Dernière colonne, ajout de EST */
			if (x == g->largeurDamier-1){
				voisins[n++] = Graphe_pointEntree(g->graphe, EST);
			}
			/* Autres colonnes, sauf la première ligne : ajout du voisin de dessus (en haut à droite) */
			else if (y != 0){
				voisins[n++] = g->metagraphe[(y-1)*g->largeurDamier + x + 1];
			}
			
			g->graphe = Graphe_insererNoeud(g->graphe, noeud, voisins, n);
		}
	}
	
	return g;
}
/** @} */


/**
 * \brief    Libère la mémoire allouée à un GrapheHex
 */
void GrapheHex_libererMemoire(GrapheHex * g){
	Graphe_libererMemoire(&(*g)->graphe);
	free((*g)->metagraphe);
	free(*g);
	*g = NULL;
}


/**
 * \brief    Modifie la valeur d'une case, et simplifie le graphe si besoin
 * \param    g Le graphe à modifier
 * \param    x 1ère coordonnée
 * \param    y 2nde coordonnée
 * \param    j La valeur (de type Joueur) à placer dans la case
 */
GrapheHex GrapheHex_modifierCase(GrapheHex g, int x, int y, Joueur j){
	GrapheNoeud noeud/*, voisin*/;
	Joueur * ptJ;
	/*LDCIterateur it;*/
	
	/* Noeud d'après le métagraphe */
	noeud = g->metagraphe[y * g->largeurDamier + x];
	
	/* Modification de la valeur */
	ptJ = (Joueur *) GrapheNoeud_obtenirElement(noeud);
	*ptJ = j;
	
	/* Fusion avec les voisins */
	/*it = LDCIterateur_init(GrapheNoeud_obtenirVoisins(noeud), LDCITERATEUR_AVANT);
	for (it = LDCIterateur_debut(it); ! LDCIterateur_fin(it); it = LDCIterateur_avancer(it)){
		voisin = (GrapheNoeud) LDCIterateur_valeur(it);
		if (  * (Joueur *) GrapheNoeud_obtenirElement(voisin) == j )
			noeud = GrapheNoeud_fusionner(noeud, voisin);
	}
	LDCIterateur_libererMemoire(&it);*/
	
	return g;
}


/**
 * \brief    Récupère le noeud corrspondant à une case
 * \param    g Le graphe à consulter
 * \param    x 1ère coordonnée
 * \param    y 2nde coordonnée
 */
GrapheNoeud GrapheHex_obtenirNoeud(GrapheHex g, int x, int y){
	return g->metagraphe[y * g->largeurDamier + x];
}








