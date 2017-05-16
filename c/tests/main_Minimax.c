/**
 * \file     main_GrapheHex.c
 * \brief    TESTS : Construction de GrapheHex d'après une sauvegarde
 * \ingroup  pack_hex_GrapheHex
 */
# include "tests.h"
# include <string.h>

/*# include "../hex/Minimax.h"*/
# include "../hex/Damier.h"
# include "../hex/Minimax.h"




/**
 * \brief Usage de la commande
 */
void erreurUsage(const char * cmd){
	fprintf(stderr, "%s: usage :\n", cmd);
	fprintf(stderr, "	construction : -c  fichier_sauvegarde  joueur  mode\n");
	fprintf(stderr, "	notation :     -n  fichier_sauvegarde  joueur  mode\n");
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
void test_construction(const char * fichier, int joueur, char mode){
	Damier d;
	arbre_mnx a;
	
	d = Damier_construireDepuisFichier(fichier);
	a = construir_mnx(d, (Joueur) joueur);
	
	afficher_mnx(a, mode);
	
	suprimer_mnx(a);
	Damier_libererMemoire(&d);
}



/**
 * \brief Test de notation
 */
void test_notation(const char * fichier, int joueur, char mode){
	Damier d;
	arbre_mnx a;
	
	d = Damier_construireDepuisFichier(fichier);
	a = construir_mnx(d, (Joueur) joueur);
	a = noter_mnx(a);
	
	afficher_mnx(a, mode);
	
	suprimer_mnx(a);
	Damier_libererMemoire(&d);
}





int main(int argc, char * argv[]){

	if (argc < 2) erreurUsage(argv[0]);
	
	switch (argv[1][1]){
		/* Construction */
		case 'c':
			if (argc != 5) erreurUsage(argv[0]);
			test_construction(argv[2], atoi(argv[3]), argv[4][0]);
			break;
		/* Notation */
		case 'n':
			if (argc != 5) erreurUsage(argv[0]);
			test_notation(argv[2], atoi(argv[3]), argv[4][0]);
			break;
			
		default:
			 erreurUsage(argv[0]);
	}
	
	return 0;
}

