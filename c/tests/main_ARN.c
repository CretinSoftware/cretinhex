# include "tests.h"



# include "../cretinlib/ARNPlus.h"



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
	
	for (it = ABRIterateur_debut(it); ! ABRIterateur_fin(it); it = ABRIterateur_avancer(it))
		NUplet_afficher((NUplet) ABRIterateur_valeur(it));
	ABRIterateur_free(&it);
}






/**
 * \brief Fonction de construction depuis un fichier (façon révisions de système)
 * \param dim Le numbre d'élément par ligne
 * \param n le nombre de dim-uplets
 * \param fichier le chemin du fichier contenant les n dim-uplets
 *
 */
ARN mkARN(int dim, int n, const char * fichier){
	
	FILE * f;
	int i, j, v;
	ARN arn;
	NUplet nuplet;
	
	if ( (f = fopen(fichier, "r") ) == NULL)
		erreur(fichier, 2);
	
	arn = ARN_init((ARNElementEval) NUplet_eval);
	
	for (i = 0; i < n; ++i){
		nuplet = NUplet_init(dim);
		for (j=0; j < dim; ++j){
			fscanf(f, "%d", &v);
			NUplet_set(nuplet, j, v);
		}
		arn = ARN_inserer(arn, (ARNElement) nuplet, (ARNElementFree) NUplet_libererMemoire);
	}
	
	fclose(f);

	return arn;
}



/**
 * \brief Test de construction / insertion
 */
void test_construction(int dim, int nb, const char * fichier){
	ARN arn;
	arn = mkARN(dim, nb, fichier);
	afficherABR(arn);
	ARN_free(&arn);
}


/**
 * \brief Test de duplication
 */
void test_duplication(int dim, int nb, const char * fichier){
	ARN arn1, arn2;
	arn1 = mkARN(dim, nb, fichier);
	arn2 = ARN_copier(arn1);
	afficherABR(arn2);
	ARN_free(&arn1);
	ARN_free(&arn2);
}

/**
 * \brief Test de fusion avec / sans doublons
 */
void test_fusion(int dim, int nb, const char * fichier1, const char * fichier2, int sansDoublons){
	ARN arn1, arn2;
	arn1 = mkARN(dim, nb, fichier1);
	arn2 = mkARN(dim, nb, fichier2);
	if (sansDoublons)
		arn1 = ARN_fusionSansDoublons(arn1, arn2);
	else
		arn1 = ARN_fusion(arn1, arn2);
	afficherABR(arn1);
	ARN_free(&arn1);
}


/**
 * \brief Test de filtre
 */
void test_filtre(int dim, int nb, const char * fichier1, const char * fichier2, int exfiltrer){
	ARN arn1, arn2, arn3;
	
	arn1 = mkARN(dim, nb, fichier1);
	arn2 = mkARN(dim, nb, fichier2);
	if (exfiltrer)
		arn3 = ARN_exfiltrer(arn1, arn2);
	else
		arn3 = ARN_filtrer(arn1, arn2);
	
	afficherABR(arn3);
	
	ARN_free(&arn1);
	ARN_free(&arn2);
	ARN_free(&arn3);
}






/**
 * \brief Test de recherche
 */
 
void test_recherche(int dim, int nb, const char * f_valeurs, const char * f_src){
	ARN arn;
	int i, v;
	char str[256];
	
	NUplet nuplet;
	
	arn = mkARN(dim, nb, f_src);
	
	
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
		if (ARN_chercher(arn, nuplet))
			printf("true\n");
		else
			printf("false\n");
		
		NUplet_libererMemoire(&nuplet);
		
	} while (!feof(f_rech));
	
	fclose(f_rech);	
	ARN_free(&arn);
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
		/* Filtre */
		case 'h':
			if (argc != 6) erreurUsage(argv);
			test_filtre(atoi(argv[2]), atoi(argv[3]), argv[4], argv[5], 0);
			break;
		/* Filter-out */
		case 'i':
			if (argc != 6) erreurUsage(argv);
			test_filtre(atoi(argv[2]), atoi(argv[3]), argv[4], argv[5], 1);
			break;
		
		default:
			 erreurUsage(argv);
	}
	
	
	return 0;
}

