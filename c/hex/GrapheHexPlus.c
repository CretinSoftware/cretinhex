/**
 * \file GrapheHexPlus.c
 * \brief Fonctions supplémentaires pour le type GrapheHex
 * \author Pierre POMERET-COQUOT
 * \version 1.0
 * \date 25 avril 2017
 *
 */



# include "GrapheHexPlus.h"







/*
 * \brief   Donne les noeuds d'un joueur
 */
LDC GrapheHex_groupes(GrapheHex g, Joueur j){
	LDC tousLesNoeuds, resultat;
	LDCIterateur it;

	resultat = LDC_init();	
	tousLesNoeuds = Graphe_tousLesNoeuds(GrapheHex_obtenirGraphe(g));
	it = LDCIterateur_init(tousLesNoeuds, LDCITERATEUR_AVANT);
	
	for (it = LDCIterateur_debut(it); ! LDCIterateur_fin(it); it = LDCIterateur_avancer(it))
		if (GHElement_valeur((GHElement) GrapheNoeud_obtenirElement((GrapheNoeud) LDCIterateur_valeur(it))) == j)
			resultat = LDC_insererElement(resultat, -1, LDCIterateur_valeur(it), NULL);
	
	LDCIterateur_libererMemoire(&it);
	LDC_libererMemoire(&tousLesNoeuds);
	return resultat;
}



/**
 * \brief   Trouve les noeuds accessible en un coup supplémentaire
 * \param   g      Le graphe à fouiller
 * \param   ldc    Une LDC contenant la liste des noeuds à 0, à 1, ..., à n de distance
 * \param   j      Le joueur cherchant à rejoindre
 * \param   ponts  La taille des ponts à prendre en compte
 * \return  La LDC transmise en parametre à laquelle on a ajouté la liste des noeuds à n+1 de distance
 */
LDC trouverNoeudsSuivants(GrapheHex g, LDC ldc, Joueur j, int ponts){
	assert(LDC_taille(ldc) > 0);
	
	LDC tmp/*, ldcPonts*/, coucheNPlusUn, coucheN, coucheNMoinsUn;
	LDCIterateur it, it2, it3/*, it4*/;
	GrapheNoeud noeud, voisin, voisinDuVoisin;
	
	coucheNPlusUn = LDC_init();
	coucheN = (LDC) LDC_obtenirElement(ldc, -1);
	if (LDC_taille(ldc) > 1)
		coucheNMoinsUn = (LDC) LDC_obtenirElement(ldc, -2);
	else
		coucheNMoinsUn = coucheN;
	
	
	it = LDCIterateur_init(coucheN, LDCITERATEUR_AVANT);
	for (it = LDCIterateur_debut(it); ! LDCIterateur_fin(it); it = LDCIterateur_avancer(it)){
		
		/* On parcourt les noeuds de la couche n */
		noeud = (GrapheNoeud) LDCIterateur_valeur(it);
		it2 = LDCIterateur_init(GrapheNoeud_obtenirVoisins(noeud), LDCITERATEUR_AVANT);
		
		for (it2 = LDCIterateur_debut(it2); ! LDCIterateur_fin(it2); it2 = LDCIterateur_avancer(it2)){
			voisin = (GrapheNoeud) LDCIterateur_valeur(it2);
			tmp = LDC_init();
			
			/* On trouve les voisins n'appartenant pas aux couches précédentes */
			if (LDC_obtenirPosition(coucheN,        voisin, (LDCElementEgal) GrapheNoeud_estEgal) < 0 && \
			    LDC_obtenirPosition(coucheNMoinsUn, voisin, (LDCElementEgal) GrapheNoeud_estEgal) < 0){
				
				/* Ces voisins ne sont pas des noeuds adverses */
				if (GHElement_valeur(GrapheNoeud_obtenirElement(voisin)) != Joueur_suivant(j)){
					
					
					/* 1. On insère ce voisin */
					tmp = LDC_inserer(tmp, -1, voisin, NULL);
					
					/* 2. On regarde si ce voisin touche un noeud non visité du joueur : il est relié ce tour-ci */
					it3 = LDCIterateur_init(GrapheNoeud_obtenirVoisins(voisin), LDCITERATEUR_AVANT);
					for (it3 = LDCIterateur_debut(it3); ! LDCIterateur_fin(it3); it3 = LDCIterateur_avancer(it3)){
						voisinDuVoisin = (GrapheNoeud) LDCIterateur_valeur(it3);
					
						if (GHElement_valeur(GrapheNoeud_obtenirElement(voisinDuVoisin)) == j)
							if (LDC_obtenirPosition(tmp,     voisinDuVoisin, (LDCElementEgal) GrapheNoeud_estEgal) < 0 && \
							    LDC_obtenirPosition(coucheN, voisinDuVoisin, (LDCElementEgal) GrapheNoeud_estEgal) < 0)
								tmp = LDC_inserer(tmp, -1, voisinDuVoisin, NULL);
					}
					LDCIterateur_libererMemoire(&it3);
				}
			}
			/*
			if (ponts){
	*/			/* 3. Ponts : On regarde si les voisins libres d'un même noeud de la couche n+1 on un voisin en commun de la couleur du joueur */
				/*            Dans ce cas, on a un pont et on considère donc le voisin des voisins comme relié */
				/*            Note : tmp contient les voisins du noeud étudié de la couche n+1 n'appartenant pas aux couches inférieures */
		/*		ldcPonts = LDC_init();
				it3 = LDCIterateur_init(tmp, LDCITERATEUR_AVANT);
				for (it3 = LDCIterateur_debut(it3); ! LDCIterateur_fin(it3); it3 = LDCIterateur_avencer(it3)){

					voisin = (GrapheNoeud) LDCIterateur_valeur(it3);
					
					if (GHElement_valeur(GrapheNoeud_obtenirElement(voisin)) == J0){
					
						it4 = LDCIterateur_init(GrapheNoeud_obtenirVoisins(voisin), LDCITERATEUR_AVANT);
						for (it4 = LDCIterateur_init(it4); ! LDCIterateur_fin(it4); it4 = LDCIterateur_avancer(it4)){
					
							voisinDuVoisin = (GrapheNoeud) LDCIterateur_valeur(it4);
			*/			
							/* Le voisinDuVoisin est au joueur, et pas déjà dans tmp (donc pas dans la couche n+1) */
				/*			if (GHElement_valeur(GrapheNoeud_obtenirElement(voisinDuVoisin)) == j){
								if (LDC_obtenirPosition(tmp, voisinDuVoisin, (LDCElementEgal) GrapheNoeud_estEgal)){
					*/				/* Possiblement un pont : un noeud du joueur relié par un noeud libre. Est-ce le cas avec un autre ? */
									
					
			
			
			coucheNPlusUn = LDC_fusionSansDoublons(coucheNPlusUn, tmp, (LDCElementEgal) GrapheNoeud_estEgal);
		}
		LDCIterateur_libererMemoire(&it2);
	}
	LDCIterateur_libererMemoire(&it);
	
	ldc = LDC_insererElement(ldc, -1, coucheNPlusUn, (LDCElementFree) LDC_libererMemoire);
	
	
	return ldc;
}

/*
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
LDC GrapheHex_noeudsAccessiblesEnNCoups(GrapheHex g, GrapheNoeud noeud, int n, Joueur j, int ponts){
	LDC ldc;
	
	ldc = LDC_init();
	ldc = LDC_insererElement(ldc, 0, LDC_insererElement(LDC_init(), 0, noeud, NULL), (LDCElementFree) LDC_libererMemoire);
	
	while (LDC_taille(ldc) < n + 1)
		ldc = trouverNoeudsSuivants(g, ldc, j, ponts);
	
	return ldc;
}



/**
 * \brief   Trouve la distance minimale entre deux noeuds, selon le joueur
 */
int GrapheHex_distanceMini(GrapheHex g, GrapheNoeud n1, GrapheNoeud n2, Joueur j, int ponts){
	LDC ldc, sousldc;
	int retour;
	
	ldc = LDC_init();
	ldc = LDC_insererElement(ldc, 0, LDC_insererElement(LDC_init(), 0, n1, NULL), (LDCElementFree) LDC_libererMemoire);
	
	sousldc = LDC_obtenirElement(ldc, -1);
	while (LDC_obtenirPosition(sousldc, n2, (LDCElementEgal) GrapheNoeud_estEgal) < 0 && LDC_taille(sousldc) > 0){
		ldc = trouverNoeudsSuivants(g, ldc, j, ponts);
		sousldc = LDC_obtenirElement(ldc, -1);
	}		
	if (LDC_taille(sousldc) == 0)
		retour = -1;
	else
		retour = LDC_taille(ldc) - 1;
	
	LDC_libererMemoire(&ldc);
	return retour;
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
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
/* Groupes */



typedef struct Groupe {
	GrapheHex graphehex;
	GrapheNoeud noeud;
	LDC distanceAuxGroupes;
} GroupeInterne;



Groupe Groupe_init(GrapheHex g, GrapheNoeud n){
	Groupe gr = (Groupe) malloc(sizeof(GroupeInterne));
	assert(gr != NULL);
	
	gr->graphehex = g;
	gr->noeud = n;
	gr->distanceAuxGroupes = LDC_init();
	return gr;
}

void Groupe_free(Groupe * gr){
	LDC_free(&((*gr)->distanceAuxGroupes));
	free(*gr);
	gr = NULL;
}

Groupe Groupe_initDistanceAuxGroupes(Groupe gr, LDC tousLesGroupes, int ponts){
	GrapheNoeud n;
	int * d;
	
	while (LDC_taille(gr->distanceAuxGroupes) > 0)
		gr->distanceAuxGroupes = LDC_enlever(gr->distanceAuxGroupes, -1);
	
	LDCIterateur it;
	it = LDCIterateur_init(tousLesGroupes, LDCITERATEUR_AVANT);
	
	for (it = LDCIterateur_debut(it); ! LDCIterateur_fin(it); it = LDCIterateur_avancer(it)){
		n = (GrapheNoeud) LDCIterateur_valeur(it);
		d = (int *) malloc(sizeof(int));
		*d = GrapheHex_distanceMini(gr->graphehex, gr->noeud, n, GHElement_valeur(GrapheNoeud_obtenirElement(n)), ponts);
		gr->distanceAuxGroupes = LDC_inserer(gr->distanceAuxGroupes, LDCIterateur_position(it), d, LDCElement_free);
	}
	
	LDCIterateur_free(&it);
	
	return gr;
}


LDC GrapheHex_initGroupes(GrapheHex g, Joueur j, int ponts){
	Groupe groupe;
	LDC groupes, noeuds;
	LDCIterateur it;
	
	groupes = LDC_init();
	noeuds = GrapheHex_groupes(g, j);
	
	it = LDCIterateur_init(noeuds, LDCITERATEUR_AVANT);
	for (it = LDCIterateur_debut(it); ! LDCIterateur_fin(it); it = LDCIterateur_avancer(it)){
		groupe = Groupe_init(g, LDCIterateur_valeur(it));
		groupe = Groupe_initDistanceAuxGroupes(groupe, noeuds, ponts);
		groupes = LDC_inserer(groupes, -1, groupe, (LDCElementFree) Groupe_free);
	}
	LDCIterateur_free(&it);
	LDC_free(&noeuds);
	return groupes;
}


void Groupe_afficher(Groupe gr){
	const char * espaces = "         ";
	printf("Groupe : %5d ( graphehex=%5d, noeud=%5d)\n", adresse(gr), adresse(gr->graphehex), adresse(gr->noeud));
	
	LDCIterateur it = LDCIterateur_init(gr->distanceAuxGroupes, LDCITERATEUR_AVANT);
	for (it = LDCIterateur_debut(it); ! LDCIterateur_fin(it); it = LDCIterateur_avancer(it))
		printf("%sGroupe n°%d à une distance de %d\n", espaces, LDCIterateur_position(it), * (int*) LDCIterateur_valeur(it));
		LDCIterateur_free(&it);
}






