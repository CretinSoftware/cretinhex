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




int fn_egal(int * a, int * b){
	printf("fn_egal(%d, %d)\n", *a, *b);
	return (*a == *b);
}

/**
 * \brief Construction d'un graphe depuis un fichier 
 */
Graphe construireDepuisFichier(int nbLiens, const char * fichier){
	FILE * f;
	int v;
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

	while (fgets(str, sizeof(str), f) != NULL){
	
		printf("\n%s-----------------\n", str);
		
		e = (int *) malloc(sizeof(int));
		
		printf("Elément : %4d ", (int) (unsigned long int) e % 10000);
	
		sscanf(str, "%d :", e);
		sprintf(debut, "%d : ", *e);
		sprintf(format, "%s%%d", debut);
		
		printf("(valeur %d)\n", *e);
		
		lg = 0;
		while (sscanf(str, format, &v) == 1){
			sprintf(debut, "%s%d ", debut, v);
			sprintf(format, "%s%%d", debut);
			tab[lg++] = Graphe_trouverNoeud(g, &v, (GrapheElementEgal) fn_egal);
		}
		
		n = GrapheNoeud_init(e, (GrapheElementFree) free);
		if (lg == 0)
			tab[lg++] = Graphe_pointEntree(g, 0);
		
		GrapheNoeud_afficher(n);
/*		printf("1er voisin : @%d\n", (int) (unsigned long int) tab[0]);
		printf("Dans @%d\n", (int) (unsigned long int) tab);
*/
		printf("\nAjout du noeud\n");
		g = Graphe_insererNoeud(g, n, tab, lg);
		Graphe_afficher(g);
		
	}
	fclose(f);
	printf("n   @%d\n", (int) (unsigned long int) n);
	printf("tab @%d\n", (int) (unsigned long int) tab);
	return g;

}


/**
 * \brief Test de construction
 */
void test_construction(int nbNoeuds, int nbLiens, const char * fichier){
	Graphe g;
	
	g = construireDepuisFichier(nbNoeuds, fichier);
	
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

