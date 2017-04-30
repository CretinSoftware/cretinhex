# include "tests.h"



# include "../hex/Partie.h"




/**
 * \brief Usage de la commande
 */
void erreurUsage(char * argv[]){
	fprintf(stderr, "%s: usage :\n", argv[0]);
	fprintf(stderr, "	-s  fichier_in fichier_out\n");
	exit(10);
}





/**
 * \brief Test de construction
 */
void test_sauvegarde(const char * f_in, const char * f_out){
	Partie p;
	
	p = Partie_charger(f_in);
	Partie_sauvegarder(p, f_out);
	
	Partie_libererMemoire(&p);
}



int main(int argc, char * argv[]){

	if (argc < 2) erreurUsage(argv);
	
	switch (argv[1][1]){
		/* Sauvegardes */
		case 's':
			if (argc != 4) erreurUsage(argv);
			test_sauvegarde(argv[2], argv[3]);
			break;
		
		default:
			 erreurUsage(argv);
	}
	
	return 0;
}

