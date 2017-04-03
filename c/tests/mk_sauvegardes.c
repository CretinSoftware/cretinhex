
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include "tests.h"
#include "../hex/Partie.h"

#define BORNE 20

/* Génère des sauvegardes avec Partie. Pas terribe pour tester Partie ! */



int main(int argc, char * argv[]){

	char str[128];
	
	/* Nombre d'arguments */
	if (argc != 5){
		sprintf(str, "%s: usage: %s  largeur  premier  nb_coups  fichier_out", argv[0], argv[0]);
		erreur(str, 1);
	}
	
	int largeur = atoi(argv[1]);
	int premier = atoi(argv[2]);
	int nb_coups = atoi(argv[3]);
	
	assert(nb_coups <= largeur * largeur);
	
	
	
	srand(time(NULL)); 
	
	
	FILE * f;
	int i;
	int x, y;
	
	
	if ( (f = fopen(argv[4], "w")) == NULL)
		erreurUnix(argv[4], 2);
		
	
	
	
	
	Partie p;
	p = Partie_init(largeur, premier);
	
	for (i = 0; i < nb_coups; ++i){
		x = rand() % largeur;
		y = rand() % largeur;
		while (Partie_obtenirCase(p, x, y) != 0){
			x = rand() % largeur;
			y = rand() % largeur;
		}
		p = Partie_placerPion(p, x, y);
	}
	
	Partie_sauvegarder(p, argv[4]);
	
	Partie_libererMemoire(&p);
	
	
	return 0;
}
