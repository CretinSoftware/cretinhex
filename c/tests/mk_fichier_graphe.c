
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include "tests.h"

# define BORNE 2000


int dansTas(int v, int tas[], int tailleTas){
	int i;
	for (i = 0; i < tailleTas; ++i)
		if (tas[i] == v)
			return 1;
	return 0;
}

int main(int argc, char * argv[]){

	char str[128];
	
	/* Nombre d'arguments */
	if (argc != 4){
		sprintf(str, "%s: usage: %s nb_noeuds nb_liens_inf fichier", argv[0], argv[0]);
		erreur(str, 1);
	}
	
	int nbNoeuds = atoi(argv[1]);
	int nbLiens  = atoi(argv[2]);
	
	
	srand(time(NULL)); 
	
	
	FILE * f;
	int i, j, r;
	
	int tas[nbLiens];
	int tailleTas;
	
	
	if ( (f = fopen(argv[3], "w")) == NULL)
		erreurUnix(argv[3], 2);
	
	
	for (i = 0; i < nbNoeuds; ++i){
		/* Numéro du noeud */
		fprintf(f, "%d : ", i);
		
		/* Liens vers valeurs inférieures */
		if (i > 0){
			tailleTas = 0;
			for (j = 0; j < (rand()%nbLiens) + 1; ++j){
				r = rand() % i;
				if (! dansTas(r, tas, tailleTas)){
					fprintf(f, "%d ", r);
					tas[tailleTas] = r;
					++tailleTas;
				}
			}
		}
		fprintf(f, "\n");
	}
	
			
	fclose(f);
	
	return 0;
}
