
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
void BridgeBot_jouer(Damier d, int joueur, int * x, int * y, int ponts){
	GrapheHex gh;
	Joueur moi;
	int c;
	
	GrapheNoeud A, B;
	
	gh = GrapheHex_init(d);
	
	if (BRIDGEBOT_DEBUG)
		printf("GrapheHex initialisé\n");
	
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
	LDC noeudsAPrendre, listeDepuisA, listeDepuisB;
	ARN tmpA, tmpB, tmp2A, tmp2B, tmp;
	LDCIterateur it;
	ABRIterateur at;
	GrapheNoeud n;
	
	noeudsAPrendre = LDC_init();
	distance =  GrapheHex_distanceMini(gh, A, B, moi, ponts);
	
	if (BRIDGEBOT_DEBUG)
		printf("Pôles : %4d %4d, séparés de %d\n", adresse(A), adresse(B), distance);
	
	listeDepuisA = GrapheHex_noeudsAccessiblesEnNCoups(gh, A, distance, moi, ponts);
	listeDepuisB = GrapheHex_noeudsAccessiblesEnNCoups(gh, B, distance, moi, ponts);
	
	for (i = 1; i <= distance; ++i){
		j = distance + 1 - i;
		tmpA = LDC_obtenirElement(listeDepuisA, i);
		tmpB = LDC_obtenirElement(listeDepuisB, j);
		
		tmp2A = ARN_init(ARNElement_adresse);
		tmp2B = ARN_init(ARNElement_adresse);
		
		at = ABRIterateur_init(tmpA);
		for (at = ABRIterateur_debut(at); ! ABRIterateur_fin(at); at = ABRIterateur_avancer(at)){
			n = (GrapheNoeud) ABRIterateur_valeur(at);
			if (GHElement_valeur(GrapheNoeud_obtenirElement(n)) == J0)
				tmp2A = ARN_inserer(tmp2A, n, NULL);
		}
		ABRIterateur_free(&at);
		
		at = ABRIterateur_init(tmpB);
		for (at = ABRIterateur_debut(at); ! ABRIterateur_fin(at); at = ABRIterateur_avancer(at)){
			n = (GrapheNoeud) ABRIterateur_valeur(at);
			if (GHElement_valeur(GrapheNoeud_obtenirElement(n)) == J0)
				tmp2B = ARN_inserer(tmp2B, n, NULL);
		}
		ABRIterateur_free(&at);
		
		
		tmp = ARN_filtrer(tmp2A, tmp2B);
		
		noeudsAPrendre = LDC_insererElement(noeudsAPrendre, -1, ARN_lister(tmp), (LDCElementFree) LDC_free);
		ARN_free(&tmp2A);
		ARN_free(&tmp2B);		
		ARN_free(&tmp);
	}
	
	
	
	/* Recherche du noeud le plus important (seul ou peu nombreux) */
	int taille, mini, pos;
	mini = 10000;
	pos = -1;
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
	
	
	/* Si aucun coup n'est possible : on joue sans les ponts, ou bien on a un bug */
	if (pos == -1 || mini == 0){
		if (ponts){
			if (BRIDGEBOT_DEBUG)
				printf("C'est gagné, on bouche les trous des ponts\n");
			BridgeBot_jouer(d, joueur, x, y, 0);
		}
		else{
			fprintf(stderr, "Aucun coup possible : on a perdu et cela devrait se savoir...\n");
			exit(1);
		}
	}
	else {
		GrapheNoeud noeudChoisi = LDC_obtenirElement(LDC_obtenirElement(noeudsAPrendre, pos), rand()%mini);
		LDC casesDuNoeud = GrapheHex_casesDuNoeud(gh, noeudChoisi);
		c = * (int *) LDC_obtenirElement(casesDuNoeud, 0);		
		*x = c % Damier_obtenirLargeur(d);
		*y = c / Damier_obtenirLargeur(d);
		LDC_free(&casesDuNoeud);
	}
	
	LDC_free(&noeudsAPrendre);
	LDC_free(&listeDepuisA);
	LDC_free(&listeDepuisB);
	GrapheHex_libererMemoire(&gh);
	
	if (BRIDGEBOT_DEBUG)
		printf("Retenu : x=%d, y=%d\n", *x, *y);
}

/**
 * \brief Libère la mémoire allouée à un BridgeBot
 */
void BridgeBot_libererMemoire(BridgeBot * bb){
	free(*bb);
}

/** @} */
