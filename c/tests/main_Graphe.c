# include "tests.h"
# include <string.h>


# include "../cretinlib/Graphe.h"




/**
 * \brief Usage de la commande
 */
void erreurUsage(char * argv[]){
	fprintf(stderr, "%s: usage :\n", argv[0]);
	fprintf(stderr, "	-c  nb_noeuds nb_liens fichier_source\n");
	exit(10);
}





/**
 * \brief Scanne une ligne comme il se doit
 */
int scanStr(char * str, const char * format, int * adrv){
	int nbM;
	
	nbM = sscanf(str, format, adrv, str);
	
	return nbM;
}



void afficherTab(void * e[], int lg){
	int i;
	printf("tab @%4d : ", (int) (unsigned long int) e % 10000);
	for (i = 0; i < lg; ++i)
		printf("%4d ", (int) (unsigned long int) e[i] % 10000);
	printf("\n");
}



/**
 * \brief Construction d'un graphe depuis un fichier 
 */
Graphe construireDepuisFichier(int nbNoeuds, int nbLiens, const char * fichier){
	FILE * f;
	int v, i;
	char str[256], debut[256], format[256];

	GrapheNoeud n;	
	GrapheNoeud tab[nbLiens];	
	int lg;
	Graphe g;
	int * e;
	
	f = fopen(fichier, "r");

	printf("\nInit\n");
	g = Graphe_init(1);
	Graphe_afficher(g);

	i = 0;
	while (fgets(str, sizeof(str), f) != NULL && i < nbNoeuds){
	
		printf("\n%s-----------------\n", str);
		
		/* Allocation mémoire de l'élément */
		e = (int *) malloc(sizeof(int));
		
		printf("Elément : %4d ", (int) (unsigned long int) e % 10000);
	
		/* Lecture de la valeur + fomat pour la lecture des liens */
		sscanf(str, "%d :", e);
		sprintf(debut, "%d : ", *e);
		sprintf(format, "%s%%d", debut);
		
		printf("(valeur %d)\n", *e);
		
		lg = 0;
		while (sscanf(str, format, &v) == 1){
			/* Lecture du lien + format pour la lecture suivante */
			sprintf(debut, "%s%d ", debut, v);
			sprintf(format, "%s%%d", debut);
			tab[lg++] = Graphe_trouverNoeud(g, &v, (GrapheElementEgal) int_egal);
		}
		if (lg == 0){
			tab[lg++] = Graphe_pointEntree(g, 0);
		}
		
		n = GrapheNoeud_init(e, (GrapheElementFree) free);
		
		GrapheNoeud_afficher(n);
		afficherTab((void **) tab, lg);
		
		printf("\nAjout du noeud\n");
		g = Graphe_insererNoeud(g, n, tab, lg);
		Graphe_afficher(g);
		++i;
		
	}
	fclose(f);
	return g;

}


/**
 * \brief Test de construction
 */
void test_construction(int nbNoeuds, int nbLiens, const char * fichier){
	Graphe g;
	
	g = construireDepuisFichier(nbNoeuds, nbLiens, fichier);
	
	Graphe_libererMemoire(&g);
}



int main(int argc, char * argv[]){

	if (argc < 2) erreurUsage(argv);
	
	switch (argv[1][1]){
		/* Construction */
		case 'c':
			if (argc != 5) erreurUsage(argv);
			test_construction(atoi(argv[2]), atoi(argv[3]), argv[4]);
			break;
		
		default:
			 erreurUsage(argv);
	}
	
	return 0;
}

