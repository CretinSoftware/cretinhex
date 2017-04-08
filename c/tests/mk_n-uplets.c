
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#include "tests.h"

#define BORNE 20000


int main(int argc, char * argv[]){

	char str[128];
	
	/* Nombre d'arguments */
	if (argc != 4){
		sprintf(str, "%s: usage: %s taille_n-uplet nombre_de_ligne fichier_dest", argv[0], argv[0]);
		erreur(str, 1);
	}
	
	int lg = atoi(argv[1]);
	int nb = atoi(argv[2]);
	
	
	srand(time(NULL)); 
	
	
	FILE * f;
	int i, j;
	
	
	if ( (f = fopen(argv[3], "w")) == NULL)
		erreurUnix(argv[3], 2);
	
	for (i = 0; i < nb; ++i){
		for (j = 0; j < lg; ++j){
			fprintf(f, "%d ", (rand()%BORNE) - (BORNE/2) + 1);
		}
		fprintf(f, "\n");
	}
	
			
	fclose(f);
	
	return 0;
}
