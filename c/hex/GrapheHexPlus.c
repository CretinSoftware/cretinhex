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



int GrapheNoeud_estDifferent(GrapheNoeud n1, GrapheNoeud n2){
	return n1 != n2;
}



/**
 * \brief   Touve tous les noeuds considérés comme reliés
 * \param   noeud Le noeud auquel on rattache les autres.
 * \param   indicateurJoueur  Un GrapheNoeud dont la seule utilité est de désigner le joueur j concerné. On considère que <i>noeud<i> lui appartient
 * \param   ponts Activer les ponts : les cases pontées sont considérées comme reliées
 * \return  Une liste contenant :
 *            - Le noeud passé en paramètre
 *            - Tous les voisins de la couleur de <i>j</i>
 *            - Si <i>ponts</i> != 0, toutes les cases pontées, et récursivement tous les voisins et les cases pontées de ces cases
 */
LDC noeudsRelies(GrapheNoeud noeud, GrapheNoeud indicateurJoueur, int ponts){
	LDC resultat, casesLibres, indicateurJ, tmp, tmp2;
	LDCIterateur it, it2, it3;
	GrapheNoeud voisin, caseLibre, caseLibre2;
	Joueur j, joueurNoeud;
	int modifiesCeTour;
	
	j = GHElement_valeur(GrapheNoeud_obtenirElement(indicateurJoueur));
	indicateurJ = LDC_inserer(LDC_init(), 0, indicateurJoueur, NULL);
	
	resultat = LDC_init();
	
	/* 1. Le noeud passé en paramètre */
	resultat = LDC_inserer(resultat, 0, noeud, NULL);
	casesLibres = LDC_init();
	
	
	/* 2. Les voisins jamais visités */
	it = LDCIterateur_init(GrapheNoeud_obtenirVoisins(noeud), LDCITERATEUR_AVANT);
	for (it = LDCIterateur_debut(it); ! LDCIterateur_fin(it); it = LDCIterateur_avancer(it)){
		voisin = (GrapheNoeud) LDCIterateur_valeur(it);
		
		if (LDC_chercher(resultat, voisin, (LDCElementEgal) GrapheNoeud_estEgal) < 0){
		
			joueurNoeud = GHElement_valeur(GrapheNoeud_obtenirElement(voisin));

			/* On veut tous les voisins appartenant à j */
			if (joueurNoeud == j)
				resultat = LDC_inserer(resultat, -1, voisin, NULL);
	
			/* On conserve les cases libres pour trouver les ponts */
			else if (joueurNoeud == J0)
				if (ponts)
					casesLibres = LDC_inserer(casesLibres, -1, voisin, NULL);
		}
	}
	LDCIterateur_free(&it);
	
	/* 3. Récursivement, en cas de ponts, les deux-fois-voisins-d'une-case-libre appartenant à j */
	modifiesCeTour = 1;
	while (ponts && modifiesCeTour){
		modifiesCeTour = 0;
		
		it = LDCIterateur_init(casesLibres, LDCITERATEUR_AVANT);
		for (it = LDCIterateur_debut(it); ! LDCIterateur_fin(it); it = LDCIterateur_avancer(it)){
			caseLibre = (GrapheNoeud) LDCIterateur_valeur(it);
			
			
			/* Noeuds appartenant au joueur, n'étant pas déjà dans resultat  */
			tmp = LDC_filtrer(GrapheNoeud_obtenirVoisins(caseLibre), indicateurJ, (LDCElementEgal) GrapheNoeud_memeJoueur);
			tmp2 = LDC_exfiltrer(tmp, resultat, (LDCElementEgal) GrapheNoeud_estEgal);
			LDC_free(&tmp);
			
			/* S'ils ont au moins deux voisins dans casesLibres, ils sont pontés */
			it2 = LDCIterateur_init(tmp2, LDCITERATEUR_AVANT);
			for (it2 = LDCIterateur_debut(it2); ! LDCIterateur_fin(it2); it2 = LDCIterateur_avancer(it2)){
				voisin = (GrapheNoeud) LDCIterateur_valeur(it2);
				tmp = LDC_filtrer(GrapheNoeud_obtenirVoisins(voisin), casesLibres, (LDCElementEgal) GrapheNoeud_estEgal);
				if (LDC_taille(tmp) >= 2){
					resultat = LDC_inserer(resultat, -1, voisin, NULL);
					++modifiesCeTour;
					it3 = LDCIterateur_init(GrapheNoeud_obtenirVoisins(voisin), LDCITERATEUR_AVANT);
					for (it3 = LDCIterateur_debut(it3); ! LDCIterateur_fin(it3); it3 = LDCIterateur_avancer(it3)){
						caseLibre2 = (GrapheNoeud) LDCIterateur_valeur(it3);
						if (GHElement_valeur(GrapheNoeud_obtenirElement(caseLibre2)) == J0 && \
						    LDC_obtenirPosition(casesLibres, caseLibre2, (LDCElementEgal) GrapheNoeud_estEgal) < 0){
						    casesLibres = LDC_inserer(casesLibres, 0, caseLibre2, NULL);
						}
					}
					LDCIterateur_free(&it3);
				}
				LDC_free(&tmp);
			}
			
			LDC_free(&tmp2);
			LDCIterateur_free(&it2);
			
		}
		LDCIterateur_free(&it);
		
	}
	
	LDC_free(&casesLibres);
	LDC_free(&indicateurJ);
	
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
LDC noeudsSuivants(GrapheHex g, LDC ldc, Joueur j, int ponts){
	assert(LDC_taille(ldc) > 0);
	
	LDC coucheNPlusUn, coucheN, coucheNMoinsUn;
	LDC casesPontees, tmp, tmp2, tmp3;
	LDCIterateur it, it2;
	GrapheNoeud noeud, voisin, voisinDuVoisin;
	GrapheNoeud indicJoueur;
	
	if (j == J1)
		indicJoueur = GrapheHex_nord(g);
	else
		indicJoueur = GrapheHex_ouest(g);
	
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
			
			/* On trouve les voisins n'appartenant pas aux couches précédentes */
			if (LDC_obtenirPosition(coucheN,        voisin, (LDCElementEgal) GrapheNoeud_estEgal) < 0 && \
			    LDC_obtenirPosition(coucheNMoinsUn, voisin, (LDCElementEgal) GrapheNoeud_estEgal) < 0){
				
				/* Ces voisins sont libres */
				if (GHElement_valeur(GrapheNoeud_obtenirElement(voisin)) == J0){
					
					/* On insère ce voisin et toutes les cases reliées n'appartenant pas aux couches précédentes */
					tmp  = noeudsRelies(voisin, indicJoueur, ponts);
					tmp2 = LDC_exfiltrer(tmp, coucheN, (LDCElementEgal) GrapheNoeud_estEgal);
					tmp3 = LDC_exfiltrer(tmp2, coucheNMoinsUn, (LDCElementEgal) GrapheNoeud_estEgal); 
					
					coucheNPlusUn = LDC_fusion(coucheNPlusUn, tmp3);
					
					LDC_free(&tmp);
					LDC_free(&tmp2);
				}
			}
		}
		LDCIterateur_libererMemoire(&it2);
	}
	LDCIterateur_libererMemoire(&it);
	
	/* Ponts : on cherche les noeuds pontables */
	if (ponts){
		
		it = LDCIterateur_init(coucheNPlusUn, LDCITERATEUR_ARRIERE);
		casesPontees = LDC_init();
		
		for (it = LDCIterateur_debut(it); ! LDCIterateur_fin(it); it = LDCIterateur_avancer(it)){
			voisin = (GrapheNoeud) LDCIterateur_valeur(it);
			
			
			/* tmp2 = pseudo-couche n+2 */
			tmp = LDC_exfiltrer(GrapheNoeud_obtenirVoisins(voisin), coucheN, (LDCElementEgal) GrapheNoeud_estEgal);
			tmp2 = LDC_exfiltrer(tmp, coucheNPlusUn, (LDCElementEgal) GrapheNoeud_estEgal);
			LDC_free(&tmp);
		
		
			it2 = LDCIterateur_init(tmp2, LDCITERATEUR_AVANT);
			for (it2 = LDCIterateur_debut(it2); ! LDCIterateur_fin(it2); it2 = LDCIterateur_avancer(it2)){
				voisinDuVoisin = (GrapheNoeud) LDCIterateur_valeur(it2);
			
				if (GHElement_valeur(GrapheNoeud_obtenirElement(voisinDuVoisin)) == J0){
					tmp3 = LDC_filtrer(GrapheNoeud_obtenirVoisins(voisinDuVoisin), coucheNPlusUn, (LDCElementEgal) GrapheNoeud_estEgal);
			
					if (LDC_taille(tmp3) >= 2){
						LDC_free(&tmp3);
						tmp = noeudsRelies(voisinDuVoisin, indicJoueur, ponts);
						tmp3 = LDC_exfiltrer(tmp, coucheN, (LDCElementEgal) GrapheNoeud_estEgal);
						casesPontees = LDC_fusion(casesPontees, tmp3);
						LDC_free(&tmp);
					}
					else
						LDC_free(&tmp3);
				}
			}
			LDCIterateur_free(&it2);
			LDC_free(&tmp2);
		}
		LDCIterateur_free(&it);
		coucheNPlusUn = LDC_fusionSansDoublons(coucheNPlusUn, casesPontees, (LDCElementEgal) GrapheNoeud_estEgal);
	}
	
	
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
	GrapheNoeud indicJoueur;
	
	if (j == J1)
		indicJoueur = GrapheHex_nord(g);
	else
		indicJoueur = GrapheHex_ouest(g);
	
	ldc = LDC_init();
	ldc = LDC_inserer(ldc, 0, noeudsRelies(noeud, indicJoueur, ponts), (LDCElementFree) LDC_free);
	/*ldc = LDC_insererElement(ldc, 0, LDC_insererElement(LDC_init(), 0, noeud, NULL), (LDCElementFree) LDC_libererMemoire);*/
	
	while (LDC_taille(ldc) < n + 1)
		ldc = noeudsSuivants(g, ldc, j, ponts);
	
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
		ldc = noeudsSuivants(g, ldc, j, ponts);
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






