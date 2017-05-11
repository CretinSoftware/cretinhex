/**
 * \file GrapheHex.c
 * \brief Implémentation du type GrapheHex.
 * \author Pierre POMERET-COQUOT
 * \version 1.2
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


GHElement GHElement_init(Joueur j){
	GHElement e = (GHElement) malloc(sizeof(Joueur));
	assert(e != NULL);
	
	* (Joueur*) e = j;
	return e;
}

Joueur GHElement_valeur(GHElement e){
	return * (Joueur *) e;
}

int GHElement_memeJoueur(GHElement e1, GHElement e2){
	return * (Joueur *) e1 == * (Joueur *) e2 && * (Joueur *) e1 != J0;
}

int GrapheNoeud_memeJoueur(GrapheNoeud n1, GrapheNoeud n2){
	return GHElement_memeJoueur((GHElement) GrapheNoeud_obtenirElement(n1), (GHElement) GrapheNoeud_obtenirElement(n2));
}

int GrapheNoeud_estJ0(GrapheNoeud n){
	return GHElement_valeur((GHElement) GrapheNoeud_obtenirElement(n)) == J0;
}

int GrapheNoeud_estJ1(GrapheNoeud n){
	return GHElement_valeur((GHElement) GrapheNoeud_obtenirElement(n)) == J1;
}

int GrapheNoeud_estJ2(GrapheNoeud n){
	return GHElement_valeur((GHElement) GrapheNoeud_obtenirElement(n)) == J2;
}

void GHElement_libererMemoire(GHElement * e){
	free(*e);
	*e = NULL;
}



GrapheHex GrapheHex_init(Damier d){
	GrapheHex g;
	GrapheNoeud noeud;
	GrapheNoeud voisins[4];    /*< Dans l'algo qui suit, on ajoute les noeuds par 4 maximum */
	GHElement e;
	int n, x, y;
	
	/* Allocation mémoire */
	g = (GrapheHex) malloc(sizeof(GrapheHexInterne));
	assert(g != NULL);
	
	
	/* Graphe : Points d'entrée dans l'ordre : N S E O */
	LDC pointsEntree = LDC_init();
	/* N et S */
	pointsEntree = LDC_insererElement(pointsEntree, -1, (LDCElement) GrapheNoeud_init(GHElement_init(J1), (GrapheElementFree) GHElement_libererMemoire), NULL);
	pointsEntree = LDC_insererElement(pointsEntree, -1, (LDCElement) GrapheNoeud_init(GHElement_init(J1), (GrapheElementFree) GHElement_libererMemoire), NULL);
	/* E et O */
	pointsEntree = LDC_insererElement(pointsEntree, -1, (LDCElement) GrapheNoeud_init(GHElement_init(J2), (GrapheElementFree) GHElement_libererMemoire), NULL);
	pointsEntree = LDC_insererElement(pointsEntree, -1, (LDCElement) GrapheNoeud_init(GHElement_init(J2), (GrapheElementFree) GHElement_libererMemoire), NULL);
	
	/* Graphe : init */
	g->graphe = Graphe_init(pointsEntree);
	
	
	
	g->largeurDamier = Damier_obtenirLargeur(d);
	
	g->metagraphe = (GrapheNoeud *) malloc(sizeof(GrapheNoeud) * g->largeurDamier * g->largeurDamier);
	assert(g->metagraphe != NULL);
	
	
	
	/* Placement des noeuds dans le métagraphe et dans le graphe */
	for (y = 0; y < g->largeurDamier; ++y){
		for (x = 0; x < g->largeurDamier; ++x){
			
			/* Nombre de noeuds */
			n = 0;
			
			/* Allocation mémoire */
			e = GHElement_init(Damier_obtenirCase(d, x, y));
			
			noeud = GrapheNoeud_init(e, (GrapheElementFree) GHElement_libererMemoire);
			
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
	
	g = GrapheHex_simplifier(g);
	
	return g;
}
/** @} */




GrapheNoeud GrapheHex_nord(GrapheHex g){   return Graphe_pointEntree(g->graphe, 0);   }
GrapheNoeud GrapheHex_sud(GrapheHex g){    return Graphe_pointEntree(g->graphe, 1);   }
GrapheNoeud GrapheHex_est(GrapheHex g){    return Graphe_pointEntree(g->graphe, 2);   }
GrapheNoeud GrapheHex_ouest(GrapheHex g){  return Graphe_pointEntree(g->graphe, 3);   }



/*
 * \brief   Affiche un GrapheHex
 */
void GrapheHex_afficher(GrapheHex g){
	Graphe_afficher(g->graphe);
}

/*
 * \brief   Donne le métagraphe associé.
 */
GrapheNoeud * GrapheHex_obtenirMetagraphe(GrapheHex g){
	return g->metagraphe;
}

/*
 * \brief   Donne le Graphe associé.
 */
Graphe GrapheHex_obtenirGraphe(GrapheHex g){
	return g->graphe;
}


/*
 * \brief   Donne la largeur du damier associé
 */
int GrapheHex_largeurDamier(GrapheHex g){
	return g->largeurDamier;
}


/*
 * \brief    Simplifie tout le graphe (regroupe les J1 contigus, et les J2)
 */
GrapheHex GrapheHex_simplifier(GrapheHex g){
	int estSimplifie, pos;
	LDC tousLesNoeuds, voisins;
	LDCIterateur it;
	GrapheNoeud n1, n2;
	
	estSimplifie = 0;
	while (! estSimplifie){
		estSimplifie = 1;
		
		
		tousLesNoeuds = Graphe_tousLesNoeuds(g->graphe);
		it = LDCIterateur_init(tousLesNoeuds, LDCITERATEUR_AVANT);
		
		for (it = LDCIterateur_debut(it); estSimplifie && ! LDCIterateur_fin(it); it = LDCIterateur_avancer(it)){
			n1 = (GrapheNoeud) LDCIterateur_valeur(it);
			voisins = GrapheNoeud_obtenirVoisins(n1);
			
			if ( (pos = LDC_obtenirPosition(voisins, n1, (LDCElementEgal) GrapheNoeud_memeJoueur)) >= 0){
				n2 = (GrapheNoeud) LDC_obtenirElement(voisins, pos);
				g = GrapheHex_fusionnerNoeuds(g, n1, n2);				
				estSimplifie = 0;
			}
		}
		LDCIterateur_libererMemoire(&it);
		LDC_libererMemoire(&tousLesNoeuds);
		
	}

	return g;
}



GrapheHex GrapheHex_fusionnerNoeuds(GrapheHex g, GrapheNoeud n1, GrapheNoeud n2){
	int i;
	
	/* On corrige les cases du metagraphe pointant vers n2 */
	for (i = 0; i < g->largeurDamier * g->largeurDamier; ++i)
		if (g->metagraphe[i] == n2)
			g->metagraphe[i] = n1;
	
	/* On fusionne les noeuds du graphe */
	g->graphe = Graphe_fusionner(g->graphe, n1, n2);
	
	return g;
}


/*
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
	LDCIterateur it;
	GrapheNoeud n, v;
	GHElement e;
	int pos, casComplique;
	
	n = (GrapheNoeud) g->metagraphe[y*g->largeurDamier + x];
	e = (GHElement) GrapheNoeud_obtenirElement(n);
	
	* (Joueur *) e = j;
	
	it = LDCIterateur_init(GrapheNoeud_obtenirVoisins(n), LDCITERATEUR_ARRIERE);
	casComplique = 0;
	
	for (it = LDCIterateur_debut(it); ! LDCIterateur_fin(it); ){
		v = (GrapheNoeud) LDCIterateur_valeur(it);
		it = LDCIterateur_avancer(it);
		
		if (GHElement_valeur(GrapheNoeud_obtenirElement(v)) == j){
			pos = LDC_obtenirPosition(Graphe_pointsEntree(g->graphe), v, (LDCElementEgal) GrapheNoeud_estEgal);
			if (pos >= 0)
				casComplique = 1;
			else
				g = GrapheHex_fusionnerNoeuds(g, n, v);
		}
			
	}
	LDCIterateur_free(&it);
	
	if (casComplique)
		g = GrapheHex_simplifier(g);
			
	
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



/*
 * \brief   Donne les cases correspondant à un noeud
 * \note    La LDC contient les adresses d'entiers n avec n / largeur = x et n % largeur = y
 */
LDC GrapheHex_casesDuNoeud(GrapheHex g, GrapheNoeud noeud){
	int i;
	int * n;
	LDC ldc;
	
	ldc = LDC_init();
	for(i = 0; i < g->largeurDamier * g->largeurDamier; ++i){
		if (GrapheNoeud_estEgal(g->metagraphe[i], noeud)){
			n = (int *) malloc(sizeof(int));
			*n = i;
			ldc = LDC_insererElement(ldc, -1, n, LDCElement_free);
		}
	}
	
	return ldc;
}






/*
 * \ brief Donne le vainqueur d'après les points d'entrées opposés identiques
 */
Joueur GrapheHex_quiGagne(GrapheHex g){
	LDC pointsEntree;
	
	pointsEntree = Graphe_pointsEntree(g->graphe);
	
	if (LDC_obtenirElement(pointsEntree, 0) == LDC_obtenirElement(pointsEntree, 1))
		return J1;
	if (LDC_obtenirElement(pointsEntree, 2) == LDC_obtenirElement(pointsEntree, 3))
		return J2;
	return J0;
}


	








