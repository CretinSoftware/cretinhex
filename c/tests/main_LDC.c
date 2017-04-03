# include "tests.h"



# include "../cretinlib/LDC.h"



/**
 * \brief Usage de la commande
 */
void erreurUsage(char * argv[]){
	fprintf(stderr, "%s: usage :\n", argv[0]);
	fprintf(stderr, "	-c dimension_n-uplet  nombre_n-uplets  fichier_source\n");
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
 * \param lgTab Le numbre d'élément par ligne
 * \param n le nombre de lgTab-uplets
 * \param fichier le chemin du fichier contenant les n lgTab-uplets
 *
 */

LDC mkLDC(int lgTab, int n, const char * fichier){
	
	FILE * f;
	int i, j, v;
	LDC ldc;
	NUplet nuplet;
	
	if ( (f = fopen(fichier, "r") ) == NULL)
		erreur(fichier, 2);
	
	ldc = LDC_init();
	
	for (i = 0; i < n; ++i){
		nuplet = NUplet_init(lgTab);
		for (j=0; j < lgTab; ++j){
			fscanf(f, "%d", &v);
			NUplet_set(nuplet, j, v);
		}
		ldc = LDC_insererElement(ldc, i, (LDCElement) nuplet, (LDCElementFree) NUplet_libererMemoire);
	}
	
	fclose(f);

	return ldc;
}




/**
 * \brief Test de construction
 */
void test_construction(int lg, int nb, const char * fichier){
	LDC ldc;
	ldc = mkLDC(lg, nb, fichier);
	afficherLDC(ldc);
	LDC_libererMemoire(&ldc);
}

int main(int argc, char * argv[]){

	if (argc < 2) erreurUsage(argv);
	
	switch (argv[1][1]){
		case 'c':
			if (argc != 5) erreurUsage(argv);
			test_construction(atoi(argv[2]), atoi(argv[3]), argv[4]);
			break;
		
		default:
			 erreurUsage(argv);
	}
	
	
	return 0;
}

