/**
 * \file     main_GrapheHex.c
 * \brief    TESTS : Construction de GrapheHex d'après une sauvegarde
 * \ingroup  pack_hex_GrapheHex
 */
# include "tests.h"
# include <string.h>


# include "../hex/Partie.h"
# include "../ia_bridgebot/bridgebot.h"




/**
 * \brief Usage de la commande
 */
void erreurUsage(const char * cmd){
	fprintf(stderr, "%s: usage :\n", cmd);
	fprintf(stderr, "constr:    -c  fichier_sauvegarde joueur ponts\n");
	exit(10);
}

Joueur char2joueur(char c){
	switch (c){
		case 'o': return J1;
		case '*': return J2;
		default:  return J0;
	}
}


/** \brief Construit un damier d'après un fichier de sauvegarde */
Damier Damier_construireDepuisFichier(const char * fichier){
	
	FILE * f;
	int i, l;
	char c;
	Damier d;
	
	
	/* Ouverture du fichier */
	f = fopen(fichier, "r");
	if (f == NULL){
		exit(-1);
	}
	
	/* En-tête */
	fscanf(f, "\\hex\n");
	
	/* Largeur */
	if (fscanf(f, "\\dim %d\n", &l) != 1)
		fprintf(stderr, "Impossible de lire le fichier\n");

	d = Damier_init(l);
	/* Damier */
	fscanf(f, "\\board\n");
	for (i = 0; i < l * l; ++i)
		if (fscanf(f, "%c ", &c) == 1)
			Damier_modifierCase(d, char2joueur(c), i%l, i/l);
		else
			fprintf(stderr, "Impossible de lire le fichier\n");
	fscanf(f, "\\endboard\n");
	
	fclose(f);
	
	return d;
}



/**
 * \brief Test de construction
 */
void test_construction(const char * fichier, int joueur, int ponts){
	Damier d;
	int x, y;
	
	BridgeBot_init(J1);
	
	d = Damier_construireDepuisFichier(fichier);
	
	switch (joueur){
		case 1: BridgeBot_jouer(d, J1, &x, &y, ponts); break;
		case 2: BridgeBot_jouer(d, J2, &x, &y, ponts); break;
		default: erreurUsage("");
	}
	
	printf("%d\n%d\n", x, y);
	
	Damier_libererMemoire(&d);

}




int main(int argc, char * argv[]){

	if (argc < 2) erreurUsage(argv[0]);
	
	switch (argv[1][1]){
		/* Construction */
		case 'c':
			if (argc != 5) erreurUsage(argv[0]);
			test_construction(argv[2], atoi(argv[3]), atoi(argv[4]));
			break;
		
		default:
			 erreurUsage(argv[0]);
	}
	
	return 0;
}

