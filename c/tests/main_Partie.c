# include "tests.h"



# include "../hex/Partie.h"




/**
 * \brief Usage de la commande
 */
void erreurUsage(char * argv[]){
	fprintf(stderr, "%s: usage :\n", argv[0]);
	fprintf(stderr, "	-s  fichier_source\n");
	exit(10);
}





/**
 * \brief Test de construction
 */
void test_sauvegarde(const char * fichier){
	Partie p;
	char f_in[256];
	char f_out[256];
	
	sprintf(f_in, "%s/%s", INPUTS, fichier);
	sprintf(f_out, "%s/Partie/%s", OUTPUTS, fichier);
	
	p = Partie_charger(f_in);
	Partie_sauvegarder(p, f_out);
	
	Partie_libererMemoire(&p);
}



int main(int argc, char * argv[]){

	if (argc < 2) erreurUsage(argv);
	
	switch (argv[1][1]){
		/* Sauvegardes */
		case 's':
			if (argc != 3) erreurUsage(argv);
			test_sauvegarde(argv[2]);
			break;
		
		default:
			 erreurUsage(argv);
	}
	
	return 0;
}

