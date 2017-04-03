# include "tests.h"


void erreur(const char * str, int CE){
	fprintf(stderr, "%s\n", str);
	exit(CE);
}

void erreurUnix(const char * str, int CE){
	perror(str);
	exit(CE);
}




/* n-uplet */
typedef struct s_NUplet {
	int dim;
	int * valeurs;
} NUpletInterne;

NUplet NUplet_init(int dimension){
	NUplet nuplet = (NUplet) malloc(sizeof(NUpletInterne));
	assert(nuplet != NULL);
	
	nuplet->dim = dimension;
	nuplet->valeurs = (int *) malloc(sizeof(int) * dimension);
	assert(nuplet->valeurs != NULL);
	return nuplet;
}

NUplet NUplet_set(NUplet nuplet, int position, int valeur){
	assert(position >= 0 && position < nuplet->dim);
	nuplet->valeurs[position] = valeur;
	return nuplet;
}

int NUplet_get(NUplet nuplet, int position){
	assert(position >= 0 && position < nuplet->dim);
	return nuplet->valeurs[position];
}

void NUplet_libererMemoire(NUplet * nuplet){
	free((*nuplet)->valeurs);
	free(*nuplet);
	*nuplet = NULL;
}

void NUplet_afficher(NUplet nuplet){
	int i;
	for (i = 0; i < nuplet->dim; ++i)
		printf("%d ", nuplet->valeurs[i]);
	printf("\n");
}

