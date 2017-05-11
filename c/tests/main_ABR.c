# include "tests.h"



# include "../cretinlib/ABRPlus.h"
# include "../cretinlib/ARN.h"



/**
 * \brief Usage de la commande
 */
void erreurUsage(char * argv[]){
	fprintf(stderr, "%s: usage :\n", argv[0]);
	fprintf(stderr, "   construction:	-c  dimension_n-uplet  nombre_n-uplets  fichier_source\n");
	fprintf(stderr, "	recherche:      -r  dimension_n-uplet  nombre_n-uplets  fichier_valeurs_à_rechercher  fichier_source\n");
	fprintf(stderr, "	fusion:         -f  dimension_n-uplet  nombre_n-uplets  fichier_ldc1  fichier_ldc2\n");
	fprintf(stderr, "	fusion sans db  -g  dimension_n-uplet  nombre_n-uplets  fichier_ldc1  fichier_ldc2\n");
	fprintf(stderr, "	filtre          -h  dimension_n-uplet  nombre_n-uplets  fichier_ldc1  fichier_ldc2\n");
	fprintf(stderr, "	filter-out      -i  dimension_n-uplet  nombre_n-uplets  fichier_ldc1  fichier_ldc2\n");
	exit(10);
}



/**
 * \brief Affiche un ABR
 */
void afficherABR(ABR abr){
	ABRIterateur it;
	
	it = ABRIterateur_init(abr);
	
	for (it = ABRIterateur_debut(it); ! ABRIterateur_fin(it); it = ABRIterateur_avancer(it)){
		NUplet_afficher((NUplet) ABRIterateur_valeur(it));
	}
	ABRIterateur_free(&it);
}






/**
 * \brief Fonction de construction depuis un fichier (façon révisions de système)
 * \param dim Le numbre d'élément par ligne
 * \param n le nombre de dim-uplets
 * \param fichier le chemin du fichier contenant les n dim-uplets
 *
 */
ABR mkABR(int dim, int n, const char * fichier){
	
	FILE * f;
	int i, j, v;
	ABR abr;
	NUplet nuplet;
	
	if ( (f = fopen(fichier, "r") ) == NULL)
		erreur(fichier, 2);
	
	abr = ABR_init((ABRElementEval) NUplet_eval);
	
	for (i = 0; i < n; ++i){
		nuplet = NUplet_init(dim);
		for (j=0; j < dim; ++j){
			fscanf(f, "%d", &v);
			NUplet_set(nuplet, j, v);
		}
		abr = ABR_inserer(abr, (ABRElement) nuplet, (ABRElementFree) NUplet_libererMemoire);
	}
	
	fclose(f);

	return abr;
}



/**
 * \brief Test de construction / insertion
 */
void test_construction(int dim, int nb, const char * fichier){
	ABR abr;
	abr = mkABR(dim, nb, fichier);
	afficherABR(abr);
	ABR_free(&abr);
}


/**
 * \brief Test de duplication
 */
void test_duplication(int dim, int nb, const char * fichier){
	ABR abr1, abr2;
	abr1 = mkABR(dim, nb, fichier);
	abr2 = ABR_copier(abr1);
	afficherABR(abr2);
	ABR_free(&abr1);
	ABR_free(&abr2);
}

/**
 * \brief Test de fusion avec / sans doublons
 */
void test_fusion(int dim, int nb, const char * fichier1, const char * fichier2, int sansDoublons){
	ABR abr1, abr2;
	abr2 = mkABR(dim, nb, fichier1);
	abr1 = mkABR(dim, nb, fichier2);
	if (sansDoublons)
		abr1 = ABR_fusionSansDoublons(abr1, abr2);
	else
		abr1 = ABR_fusion(abr1, abr2);
	afficherABR(abr1);
	ABR_free(&abr1);
}


/**
 * \brief Test de filtre
 */
/*void test_filtre(int dim, int nb, const char * fichier1, const char * fichier2, int exfiltrer){
	LDC ldc1, ldc2, ldc3;
	
	ldc1 = mkLDC(dim, nb, fichier1);
	ldc2 = mkLDC(dim, nb, fichier2);
	if (exfiltrer)
		ldc3 = LDC_exfiltrer(ldc1, ldc2, (LDCElementEgal) NUplet_egal);
	else
		ldc3 = LDC_filtrer(ldc1, ldc2, (LDCElementEgal) NUplet_egal);
	
	afficherLDC(ldc3);
	
	LDC_free(&ldc1);
	LDC_free(&ldc2);
	LDC_free(&ldc3);
}
*/





/**
 * \brief Test de recherche
 */
 
void test_recherche(int dim, int nb, const char * f_valeurs, const char * f_src){
	ABR abr;
	int i, v;
	char str[256];
	
	NUplet nuplet;
	
	abr = mkABR(dim, nb, f_src);
	
	
	FILE * f_rech = fopen(f_valeurs, "r");
	assert (f_rech != NULL);
	
	
	do {
		nuplet = NUplet_init(dim);
		for (i = 0; i < dim; ++i){
			fscanf(f_rech, "%d", &v);
			nuplet = NUplet_set(nuplet, i, v);
		}
		
		fscanf(f_rech, "%s ", str);
		
		
		NUplet_afficher(nuplet);
		if (ABR_chercher(abr, nuplet))
			printf("true\n");
		else
			printf("false\n");
		
		NUplet_libererMemoire(&nuplet);
		
	} while (!feof(f_rech));
	
	fclose(f_rech);	
	ABR_free(&abr);
}





int main(int argc, char * argv[]){

	if (argc < 2) erreurUsage(argv);
	
	switch (argv[1][1]){
		/* Construction */
		case 'c':
			if (argc != 5) erreurUsage(argv);
			test_construction(atoi(argv[2]), atoi(argv[3]), argv[4]);
			break;
		/* Duplication */
		case 'd':
			if (argc != 5) erreurUsage(argv);
			test_duplication(atoi(argv[2]), atoi(argv[3]), argv[4]);
			break;
		/* Fusion */
		case 'f':
			if (argc != 6) erreurUsage(argv);
			test_fusion(atoi(argv[2]), atoi(argv[3]), argv[4], argv[5], 0);
			break;
		/* Fusion sans doublons */
		case 'g':
			if (argc != 6) erreurUsage(argv);
			test_fusion(atoi(argv[2]), atoi(argv[3]), argv[4], argv[5], 1);
			break;
		/* Recherche */
		case 'r':
			if (argc != 6) erreurUsage(argv);
			test_recherche(atoi(argv[2]), atoi(argv[3]), argv[4], argv[5]);
			break;
		/* Filtre *//*
		case 'h':
			if (argc != 6) erreurUsage(argv);
			test_filtre(atoi(argv[2]), atoi(argv[3]), argv[4], argv[5], 0);
			break;*/
		/* Filter-out *//*
		case 'i':
			if (argc != 6) erreurUsage(argv);
			test_filtre(atoi(argv[2]), atoi(argv[3]), argv[4], argv[5], 1);
			break;*/
		
		default:
			 erreurUsage(argv);
	}
	
	
	return 0;
}

