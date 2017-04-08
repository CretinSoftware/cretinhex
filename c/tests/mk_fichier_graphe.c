
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include "tests.h"

# define BORNE 2000
# define MIN(x, y) (x > y ? y : x)


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
	
	
	if ( (f = fopen(argv[3], "w")) == NULL)
		erreurUnix(argv[3], 2);
	
	
	for (i = 0; i < nbNoeuds; ++i){
		/* Numéro du noeud */
		fprintf(f, "%d : ", i);
		
		/* Liens inférieurs */
		for (j = 1; j < MIN(i, rand()%nbLiens); ++j){
			r = rand() % i;
			fprintf(f, "%d ", r);
		}
		fprintf(f, "\n");
	}
	
			
	fclose(f);
	
	return 0;
}
