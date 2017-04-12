# include "tests.h"
# include <string.h>


# include "../hex/Partie.h"
# include "../hex/GrapheHex.c"




/**
 * \brief Usage de la commande
 */
void erreurUsage(char * argv[]){
	fprintf(stderr, "%s: usage :\n", argv[0]);
	fprintf(stderr, "	-c  fichier_sauvegarde\n");
	exit(10);
}



/**
 * \brief Construction d'un graphe depuis un fichier 
 */
GrapheHex construireDepuisFichier(const char * fichier){
	
	GrapheHex gh;
	Partie p;
	
	p = Partie_charger(fichier);
	gh = GrapheHex_init(Partie_obtenirDamier(p));
	
	Partie_libererMemoire(&p);
	
	return gh;

}


/**
 * \brief Test de construction
 */
void test_construction(const char * fichier){
	GrapheHex gh;
	
	gh = construireDepuisFichier(fichier);
	
	Graphe_afficher(gh->graphe);
	
	GrapheHex_libererMemoire(&gh);
}



int main(int argc, char * argv[]){

	if (argc < 2) erreurUsage(argv);
	
	switch (argv[1][1]){
		/* Construction */
		case 'c':
			if (argc != 3) erreurUsage(argv);
			test_construction(argv[2]);
			break;
		
		default:
			 erreurUsage(argv);
	}
	
	return 0;
}

