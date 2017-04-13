# include "tests.h"
# include <string.h>


# include "../cretinlib/Graphe.h"




/**
 * \brief Usage de la commande
 */
void erreurUsage(char * argv[]){
	fprintf(stderr, "%s: usage :\n", argv[0]);
	fprintf(stderr, "	-c  nb_noeuds nb_liens fichier_source\n");
	exit(10);
}





/**
 * \brief Scanne une ligne comme il se doit
 */
int scanStr(char * str, const char * format, int * adrv){
	int nbM;
	
	nbM = sscanf(str, format, adrv, str);
	
	return nbM;
}








void swap(int * a, int * b){
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

/** \brief Tri rapide */
void trierTab(int tab[], int deb, int fin){
	if (deb < fin){
		int iPiv = deb;
		int iCur = deb + 1;
		int iFin = fin;
	
		while (iCur <= iFin){
			if (tab[iCur] < tab[iPiv]){
				swap(&tab[iCur], &tab[iPiv]);
				++iCur;
			}
			else{
				swap(&tab[iCur], &tab[iFin]);
				--iFin;
			}
		}
		trierTab(tab, deb, iPiv - 1);
		trierTab(tab, iPiv + 1, fin);
	}
}

/**
 * \brief Affiche le graphe pour matcher les résultats : valeur du noeud et valeurs triées de ses voisins
 */
void afficherGraphe(Graphe g){
	LDC tousLesNoeuds;
	LDCIterateur it, it2;
	GrapheNoeud n, n2;
	
	tousLesNoeuds = Graphe_tousLesNoeuds(g);
	it = LDCIterateur_init(tousLesNoeuds, LDCITERATEUR_AVANT);
	
	
	int valeursVoisins[LDC_taille(tousLesNoeuds)];
	int i, nbVoisins;
	
	
	
	for (it = LDCIterateur_debut(it); ! LDCIterateur_fin(it); it = LDCIterateur_avancer(it)){
		n = (GrapheNoeud) LDCIterateur_valeur(it);
		it2 = LDCIterateur_init(GrapheNoeud_obtenirVoisins(n), LDCITERATEUR_AVANT);
		
		printf("%d : ", * (int*) GrapheNoeud_obtenirElement(n));
		
		nbVoisins = 0;
		for (it2 = LDCIterateur_debut(it2); ! LDCIterateur_fin(it2); it2 = LDCIterateur_avancer(it2)){
			n2 = (GrapheNoeud) LDCIterateur_valeur(it2);
			valeursVoisins[nbVoisins++] = * (int*) GrapheNoeud_obtenirElement(n2);
		}
		
		trierTab(valeursVoisins, 0, nbVoisins - 1);
		for (i = 0; i < nbVoisins; ++i)
			printf("%d ", valeursVoisins[i]);		
		printf("\n");
		
		LDCIterateur_libererMemoire(&it2);
	}
	
	LDCIterateur_libererMemoire(&it);
	LDC_libererMemoire(&tousLesNoeuds);
}



/** \brief Supprime un pointeur d'entier */
void int_free(int ** ptr){
	free(*ptr);
	*ptr = NULL;
}


/**
 * \brief Construction d'un graphe depuis un fichier 
 */
Graphe construireDepuisFichier(int nbNoeuds, int nbLiens, const char * fichier){
	FILE * f;
	int v, i;
	char str[256], debut[256], format[256];

	GrapheNoeud n;	
	GrapheNoeud tab[nbLiens];	
	int lg;
	Graphe g;
	int * e;
	
	f = fopen(fichier, "r");
	

	i = 0;
	while (fgets(str, sizeof(str), f) != NULL && i < nbNoeuds){
	
		/* Allocation mémoire de l'élément */
		e = (int *) malloc(sizeof(int));
		
		/* Lecture de la valeur + fomat pour la lecture des liens */
		sscanf(str, "%d :", e);
		sprintf(debut, "%d : ", *e);
		sprintf(format, "%s%%d", debut);
		
		lg = 0;
		while (sscanf(str, format, &v) == 1){
			/* Lecture du lien + format pour la lecture suivante */
			sprintf(debut, "%s%d ", debut, v);
			sprintf(format, "%s%%d", debut);
			tab[lg++] = Graphe_trouverNoeud(g, &v, (GrapheElementEgal) int_egal);
		}
		
		
		n = GrapheNoeud_init(e, (GrapheElementFree) int_free);

		if (lg == 0){
			LDC pointsEntree = LDC_init();
			pointsEntree = LDC_inserer(pointsEntree, -1, n, NULL);

			g = Graphe_init(pointsEntree);
		}
		else {
			g = Graphe_insererNoeud(g, n, tab, lg);
		}
		++i;
		
		
	}
	fclose(f);
	
	return g;

}


/**
 * \brief Test de construction
 */
void test_construction(int nbNoeuds, int nbLiens, const char * fichier){
	Graphe g;
	
	g = construireDepuisFichier(nbNoeuds, nbLiens, fichier);
	
	afficherGraphe(g);
	
	Graphe_libererMemoire(&g);
}


/**
 * \brief Test de fusion
 */
void test_fusion(int nbNoeuds, int nbLiens, const char * fichier){
	Graphe g;
	GrapheNoeud n1, n2;
	
	
	g = construireDepuisFichier(nbNoeuds, nbLiens, fichier);
	
	afficherGraphe(g);
	
	n1 = Graphe_pointEntree(g, 0);
	n2 = (GrapheNoeud) LDC_obtenir(GrapheNoeud_obtenirVoisins(n1), -1);
	
	printf("Fusion : %d et %d\n", * (int*) GrapheNoeud_obtenirElement(n1), * (int*) GrapheNoeud_obtenirElement(n2));
	
	g = Graphe_fusionner(g, n1, n2);
	
	afficherGraphe(g);
	
	Graphe_libererMemoire(&g);
}



int main(int argc, char * argv[]){

	if (argc < 2) erreurUsage(argv);
	
	switch (argv[1][1]){
		/* Construction */
		case 'c':
			if (argc != 5) erreurUsage(argv);
			test_construction(atoi(argv[2]), atoi(argv[3]), argv[4]);
			break;
		/* Fusion */
		case 'f':
			if (argc != 5) erreurUsage(argv);
			test_fusion(atoi(argv[2]), atoi(argv[3]), argv[4]);
			break;
		
		default:
			 erreurUsage(argv);
	}
	
	return 0;
}

