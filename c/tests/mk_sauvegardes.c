/**
 * \file     mk_sauvegardes.c
 * \brief    TESTS : Création de fichiers de sauvegarde
 * \ingroup  pack_hex_Partie
 *
 * \par      Commande
 * <pre>./mk_sauvegardes largeur pemier nb_coups fichier_out</pre>
 */

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include "tests.h"
#include "../hex/Partie.h"
#include "../cretinlib/LDC.h"

#define BORNE 20



/* Supprime un entier malloqué */
void free_int(int ** v){
	free(*v);
	*v = NULL;
}



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
	int rd, i;
	int * v;
	
	printf("mk fichier %s ", argv[4]);
	
	if ( (f = fopen(argv[4], "w")) == NULL)
		erreurUnix(argv[4], 2);
		
	
	Partie p;
	p = Partie_init(largeur, premier);
	
	/* Toutes les cases sont libres */
	LDC casesLibres = LDC_init();
	for (i = 0; i < largeur * largeur; ++i){
		v = (int *) malloc(sizeof(int));
		*v = i;
		casesLibres = LDC_insererElement(casesLibres, -1, v, (LDCElementFree) free_int);
	}
	
	
	for (i = 0; i < nb_coups; ++i){
		if (nb_coups < 10 || i % (nb_coups / 10) == 0){
			printf(".");
			fflush(stdout);
		}
		/* On trouve une case libre au hasard, on la joue et on l'enlève de la liste */
		rd = rand() % LDC_taille(casesLibres);
		v = (int *) LDC_obtenirElement(casesLibres, rd);
		p = Partie_placerPion(p, *v % largeur, *v / largeur);
		casesLibres = LDC_enleverElement(casesLibres, rd);
	}
	
	printf("\n");
	
	Partie_sauvegarder(p, argv[4]);
	
	LDC_libererMemoire(&casesLibres);
	Partie_libererMemoire(&p);
	
	
	fclose(f);
	
	return 0;
}
