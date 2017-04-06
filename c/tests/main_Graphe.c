# include "tests.h"
# include <string.h>


# include "../cretinlib/Graphe.h"




/**
 * \brief Usage de la commande
 */
void erreurUsage(char * argv[]){
	fprintf(stderr, "%s: usage :\n", argv[0]);
	fprintf(stderr, "	-c  nb_noeuds fichier_source\n");
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

/**
 * \brief Construction d'un graphe depuis un fichier 
 */
Graphe construireDepuisFichier(const char * fichier){
	FILE * f;
	int v1, v2;
	char str[256], debut[256], format[256];
	
	Graphe g;
	
	f = fopen(fichier, "r");


	while (fgets(str, sizeof(str), f) != NULL){
	
		printf("%s", str);
	
		sscanf(str, "%d :", &v1);
		sprintf(debut, "%d : ", v1);
		sprintf(format, "%s%%d", debut);
		
		printf("%d : ", v1);

		
		while (sscanf(str, format, &v2) == 1){
			sprintf(debut, "%s%d ", debut, v2);
			sprintf(format, "%s%%d", debut);
			printf("%d ", v2);
		}
		printf("\n");
	}
	fclose(f);
	return g;

}


/**
 * \brief Test de construction
 */
void test_construction(int nbNoeuds, const char * fichier){
	Graphe g;
	
	g = construireDepuisFichier(fichier);
}



int main(int argc, char * argv[]){

	if (argc < 2) erreurUsage(argv);
	
	switch (argv[1][1]){
		/* Construction */
		case 'c':
			if (argc != 4) erreurUsage(argv);
			test_construction(atoi(argv[2]), argv[3]);
			break;
		
		default:
			 erreurUsage(argv);
	}
	
	return 0;
}

