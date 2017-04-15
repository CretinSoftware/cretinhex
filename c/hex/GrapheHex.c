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
 * \brief   Donne les noeuds d'un joueur
 */
LDC GrapheHex_groupes(GrapheHex g, Joueur j){
	LDC tousLesNoeuds, resultat;
	LDCIterateur it;

	resultat = LDC_init();	
	tousLesNoeuds = Graphe_tousLesNoeuds(g->graphe);
	it = LDCIterateur_init(tousLesNoeuds, LDCITERATEUR_AVANT);
	
	for (it = LDCIterateur_debut(it); ! LDCIterateur_fin(it); it = LDCIterateur_avancer(it))
		if (GHElement_valeur((GHElement) GrapheNoeud_obtenirElement((GrapheNoeud) LDCIterateur_valeur(it))) == j)
			resultat = LDC_insererElement(resultat, -1, LDCIterateur_valeur(it), NULL);
	
	LDCIterateur_libererMemoire(&it);
	LDC_libererMemoire(&tousLesNoeuds);
	return resultat;
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
	
	GHElement e;
	
	e = (GHElement) GrapheNoeud_obtenirElement(g->metagraphe[y*g->largeurDamier + x]);
	
	* (Joueur *) e = j;
	
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




/**
 * \brief  Donne toutes les façons d'avancer sur un chemin sans revenir sur ses pas ni aller sur une case adverse 
 */
LDC GrapheHex_avancerSurChemin(GrapheHex g, LDC cheminEnCours, Joueur j){
	GrapheNoeud noeud, voisin;
	LDC cheminsPossibles;
	LDC nouveauChemin;
	LDCIterateur it;
	Joueur valeurVoisin;
	
	cheminsPossibles = LDC_init();
	
	noeud = (GrapheNoeud) LDC_obtenirElement(cheminEnCours, -1);
	
	it = LDCIterateur_init(GrapheNoeud_obtenirVoisins(noeud), LDCITERATEUR_AVANT);
	
	for (it = LDCIterateur_debut(it); ! LDCIterateur_fin(it); it = LDCIterateur_avancer(it)){
		voisin = (GrapheNoeud) LDCIterateur_valeur(it);
		valeurVoisin = GHElement_valeur((GHElement) GrapheNoeud_obtenirElement(voisin));
		if (valeurVoisin == j || valeurVoisin == J0){
			if (LDC_obtenirPosition(cheminEnCours, voisin, (LDCElementEgal) GrapheNoeud_estEgal) < 0){
				nouveauChemin = LDC_copier(cheminEnCours);
				nouveauChemin = LDC_insererElement(nouveauChemin, -1, voisin, NULL);
				cheminsPossibles = LDC_insererElement(cheminsPossibles, -1, nouveauChemin, NULL);
			}
		}
	}
	
	LDCIterateur_libererMemoire(&it);
	
	return cheminsPossibles;
}


void LDC_freeElements(LDC ldc, LDCElementFree fn_free){
	LDCIterateur it;
	void * e;
	
	it = LDCIterateur_init(ldc, LDCITERATEUR_AVANT);
	for (it = LDCIterateur_debut(it); ! LDCIterateur_fin(it); it = LDCIterateur_avancer(it)){
		e =  LDCIterateur_valeur(it);
		fn_free(&e);
	}
	LDCIterateur_libererMemoire(&it);
}

/*
 * \brief    Donne le(s) plus court(s) chemin(s) pour aller des points d'entrée A vers B
 * \note     La fonction renvoie une LDC de LDC (LDC à deux dimensions). Sa désallocation mémoire est à votre charge.
 */
LDC GrapheHex_plusCourtsChemins(GrapheHex g, GrapheNoeud depart, GrapheNoeud arrivee, Joueur j){
	LDC chemins, tmp, chem;
	LDCIterateur it;
	
	int pos, termine;
	
	/* Chemins au départ : le premier noeud */
	chemins = LDC_init();
	chemins = LDC_insererElement(chemins, -1, LDC_insererElement(LDC_init(), -1, depart, NULL), NULL);
	
	termine = 0;
	while (! termine){
	
		/* On trouve tous les chemins possibles (dans tmp) */
		tmp = LDC_init();
		it = LDCIterateur_init(chemins, LDCITERATEUR_AVANT);
		for (it = LDCIterateur_debut(it); ! LDCIterateur_fin(it); it = LDCIterateur_avancer(it))
			tmp = LDC_fusion(tmp, GrapheHex_avancerSurChemin(g, (LDC) LDCIterateur_valeur(it), j));
		
		LDCIterateur_libererMemoire(&it);
		LDC_freeElements(chemins, (LDCElementFree) LDC_libererMemoire);
		LDC_libererMemoire(&chemins);
		
		/* On trouve tous les chemins menant à arrivée (dans tmp), on les place dans chemins */
		it = LDCIterateur_init(tmp, LDCITERATEUR_AVANT);
		it = LDCIterateur_debut(it);
		chemins = LDC_init();
		pos = 0;
		
		while (! LDCIterateur_fin(it)){
			chem = (LDC) LDCIterateur_valeur(it);
			if (GrapheNoeud_estEgal(arrivee, (GrapheNoeud) LDC_obtenirElement(chem, -1))){
				termine = 1;
				chemins = LDC_insererElement(chemins, -1, chem, (LDCElementFree) LDC_libererMemoire);
				it = LDCIterateur_avancer(it);
				tmp = LDC_enleverElement(tmp, pos);
			}
			else {
				it = LDCIterateur_avancer(it);
				++pos;
			}
		}
		LDCIterateur_libererMemoire(&it);
		
		/* Si chemins est vide, aucun ne mène (encore) à l'arrivée, on les ajoute tous */
		if (LDC_taille(chemins) == 0){
			LDC_libererMemoire(&chemins);
			chemins = LDC_copier(tmp);
		}
		
		/* Sinon, on a terminé le traitement et on efface les chemins encore contenus dans tmp */
		else 
			LDC_freeElements(tmp, (LDCElementFree) LDC_libererMemoire);
		
		
		/* Si chemins est encore vide, c'est aucun chemin n'existe */
		if (LDC_taille(chemins) == 0)
			termine = 1;
				
		/* Libération mémoire de tmp (mais pas de son contenu, qui est copié dans chemins ou a déjà été effacé) */
		LDC_libererMemoire(&tmp);
	}
		
	return chemins;
}
	
	
	








