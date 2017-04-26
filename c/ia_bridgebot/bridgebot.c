
# include "bridgebot.h"
# include <time.h>






/**
 * \brief    Initialise un bridgebot
 */
void BridgeBot_init(){
	srand(time(NULL)); 
}

/**
 * \brief    Demande à un BridgeBot ce qu'il ferait sur un tel damier
 */
void BridgeBot_jouer(Damier d, int joueur, int * x, int * y){
	GrapheHex gh;
	Joueur moi;
	
	GrapheNoeud A, B;
	
	gh = GrapheHex_init(d);
	
	assert(joueur == 1 || joueur == 2);
	if (joueur == 1){
		moi = J1;
		A = GrapheHex_nord(gh);
		B = GrapheHex_sud(gh);
	}
	else {
		moi = J2;
		A = GrapheHex_ouest(gh);
		B = GrapheHex_est(gh);
	}
	
	/* On cherche les noeuds à prendre : ils sont à i de NORD, j de SUD, tels que i + j - 1 = distanceMini(NORD, SUD) */
	int i, j, distance;
	LDC noeudsAPrendre, listeDepuisA, listeDepuisB, tmpA, tmpB, tmp2A, tmp2B;
	LDCIterateur it;
	GrapheNoeud n;
	
	noeudsAPrendre = LDC_init();
	distance =  GrapheHex_distanceMini(gh, A, B, moi, BRIDGEBOT_PONTS);
	
	if (BRIDGEBOT_DEBUG)
		printf("Pôles : %4d %4d\n", adresse(A), adresse(B));
	
	listeDepuisA = GrapheHex_noeudsAccessiblesEnNCoups(gh, A, distance, moi, BRIDGEBOT_PONTS);
	listeDepuisB = GrapheHex_noeudsAccessiblesEnNCoups(gh, B, distance, moi, BRIDGEBOT_PONTS);
	
	for (i = 1; i <= distance; ++i){
		j = distance + 1 - i;
		tmpA = LDC_obtenirElement(listeDepuisA, i);
		tmpB = LDC_obtenirElement(listeDepuisB, j);
		
		tmp2A = LDC_init();
		tmp2B = LDC_init();
		
		it = LDCIterateur_init(tmpA, LDCITERATEUR_AVANT);
		for (it = LDCIterateur_debut(it); ! LDCIterateur_fin(it); it = LDCIterateur_avancer(it)){
			n = (GrapheNoeud) LDCIterateur_valeur(it);
			if (GHElement_valeur(GrapheNoeud_obtenirElement(n)) == J0)
				tmp2A = LDC_insererElement(tmp2A, -1, n, NULL);
		}
		LDCIterateur_free(&it);
		
		it = LDCIterateur_init(tmpB, LDCITERATEUR_AVANT);
		for (it = LDCIterateur_debut(it); ! LDCIterateur_fin(it); it = LDCIterateur_avancer(it)){
			n = (GrapheNoeud) LDCIterateur_valeur(it);
			if (GHElement_valeur(GrapheNoeud_obtenirElement(n)) == J0)
				tmp2B = LDC_insererElement(tmp2B, -1, n, NULL);
		}
		LDCIterateur_free(&it);
		
		
		noeudsAPrendre = LDC_insererElement(noeudsAPrendre, -1, LDC_filtrer(tmp2A, tmp2B, (LDCElementEgal) GrapheNoeud_estEgal), (LDCElementFree) LDC_free);
		LDC_free(&tmp2A);
		LDC_free(&tmp2B);		
	}
	
	
	
	/* Recherche du noeud le plus important (seul ou peu nombreux) */
	int taille, mini, pos;
	mini = 10000;
	it = LDCIterateur_init(noeudsAPrendre, LDCITERATEUR_AVANT);
	for (it = LDCIterateur_debut(it); ! LDCIterateur_fin(it); it = LDCIterateur_avancer(it)){
		taille = LDC_taille(LDCIterateur_valeur(it));
		if (taille < mini || (taille == mini && rand()%3 == 0)){
			mini = taille;
			pos = LDCIterateur_position(it);
		}
	}
	LDCIterateur_free(&it);
	
	if (BRIDGEBOT_DEBUG)
		printf("%d noeuds à %d de distance (mini)\n", mini, pos+1);
	
	GrapheNoeud noeudChoisi = LDC_obtenirElement(LDC_obtenirElement(noeudsAPrendre, pos), rand()%mini);
	LDC casesDuNoeud = GrapheHex_casesDuNoeud(gh, noeudChoisi);
	int c = * (int *) LDC_obtenirElement(casesDuNoeud, 0);
	
	LDC_free(&casesDuNoeud);
	LDC_free(&noeudsAPrendre);
	LDC_free(&listeDepuisA);
	LDC_free(&listeDepuisB);
	GrapheHex_libererMemoire(&gh);
	
	*x = c % Damier_obtenirLargeur(d);
	*y = c / Damier_obtenirLargeur(d);
}

/**
 * \brief Libère la mémoire allouée à un BridgeBot
 */
void BridgeBot_libererMemoire(BridgeBot * bb){
	free(*bb);
}

/** @} */
