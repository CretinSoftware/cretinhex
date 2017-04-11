# include "tests.h"



# include "../cretinlib/LDC.h"



/**
 * \brief Usage de la commande
 */
void erreurUsage(char * argv[]){
	fprintf(stderr, "%s: usage :\n", argv[0]);
	fprintf(stderr, "	-c  dimension_n-uplet  nombre_n-uplets  fichier_source\n");
	fprintf(stderr, "	-r  dimension_n-uplet  nombre_n-uplets  fichier_valeurs_à_rechercher  fichier_source\n");
	fprintf(stderr, "	-f  dimension_n-uplet  nombre_n-uplets  fichier_ldc1  fichier_ldc2\n");
	fprintf(stderr, "	-g  dimension_n-uplet  nombre_n-uplets  fichier_ldc1  fichier_ldc2\n");
	exit(10);
}




/**
 * \brief Affiche une LDC
 */
void afficherLDC(LDC ldc){
	LDCIterateur it;
	
	it = LDCIterateur_init(ldc, LDCITERATEUR_AVANT);
	
	for (it = LDCIterateur_debut(it); ! LDCIterateur_fin(it); it = LDCIterateur_avancer(it)){
		NUplet_afficher((NUplet) LDCIterateur_valeur(it));
	}
	LDCIterateur_libererMemoire(&it);
}





/**
 * \brief Fonction de construction depuis un fichier (façon révisions de système)
 * \param dim Le numbre d'élément par ligne
 * \param n le nombre de dim-uplets
 * \param fichier le chemin du fichier contenant les n dim-uplets
 *
 */

LDC mkLDC(int dim, int n, const char * fichier){
	
	FILE * f;
	int i, j, v;
	LDC ldc;
	NUplet nuplet;
	
	if ( (f = fopen(fichier, "r") ) == NULL)
		erreur(fichier, 2);
	
	ldc = LDC_init();
	
	for (i = 0; i < n; ++i){
		nuplet = NUplet_init(dim);
		for (j=0; j < dim; ++j){
			fscanf(f, "%d", &v);
			NUplet_set(nuplet, j, v);
		}
		ldc = LDC_inserer(ldc, i, (LDCElement) nuplet, (LDCElementFree) NUplet_libererMemoire);
	}
	
	fclose(f);

	return ldc;
}




/**
 * \brief Test de construction / insertion
 */
void test_construction(int dim, int nb, const char * fichier){
	LDC ldc;
	ldc = mkLDC(dim, nb, fichier);
	afficherLDC(ldc);
	LDC_free(&ldc);
}




/**
 * \brief Test de fusion avec / sans doublons
 */
void test_fusion(int dim, int nb, const char * fichier1, const char * fichier2, int sansDoublons){
	LDC ldc1, ldc2;
	ldc1 = mkLDC(dim, nb, fichier1);
	ldc2 = mkLDC(dim, nb, fichier2);
	if (sansDoublons)
		ldc1 = LDC_fusionSansDoublons(ldc1, ldc2, (LDCElementEgal) NUplet_egal);
	else
		ldc1 = LDC_fusion(ldc1, ldc2);
	afficherLDC(ldc1);
	LDC_free(&ldc1);
}






/**
 * \brief Test de recherche
 */
void test_recherche(int dim, int nb, const char * f_valeurs, const char * f_src){
	LDC ldc;
	int i, v;
	char str[256];
	
	NUplet nuplet;
	
	ldc = mkLDC(dim, nb, f_src);
	
	
	FILE * f_rech = fopen(f_valeurs, "r");
	assert (f_rech != NULL);
	
	
	do {
		nuplet = NUplet_init(dim);
		for (i = 0; i < dim; ++i){
			fscanf(f_rech, "%d", &v);
			nuplet = NUplet_set(nuplet, i, v);
		}
		
		fscanf(f_rech, "%s ", str);
		
		
		/* Affichage */
		NUplet_afficher(nuplet);
		if (LDC_obtenirPosition(ldc, nuplet, (LDCElementEgal) NUplet_egal) >= 0)
			printf("true\n");
		else
			printf("false\n");
		
		NUplet_libererMemoire(&nuplet);
		
	} while (!feof(f_rech));
	
	fclose(f_rech);	
	LDC_free(&ldc);
}





int main(int argc, char * argv[]){

	if (argc < 2) erreurUsage(argv);
	
	switch (argv[1][1]){
		case 'c':
			if (argc != 5) erreurUsage(argv);
			test_construction(atoi(argv[2]), atoi(argv[3]), argv[4]);
			break;
		case 'f':
			if (argc != 6) erreurUsage(argv);
			test_fusion(atoi(argv[2]), atoi(argv[3]), argv[4], argv[5], 0);
			break;
		case 'g':
			if (argc != 6) erreurUsage(argv);
			test_fusion(atoi(argv[2]), atoi(argv[3]), argv[4], argv[5], 1);
			break;
		case 'r':
			if (argc != 6) erreurUsage(argv);
			test_recherche(atoi(argv[2]), atoi(argv[3]), argv[4], argv[5]);
			break;
		
		default:
			 erreurUsage(argv);
	}
	
	
	return 0;
}

