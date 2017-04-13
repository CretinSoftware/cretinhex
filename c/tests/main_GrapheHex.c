# include "tests.h"
# include <string.h>


# include "../hex/Partie.h"
# include "../hex/GrapheHex.h"




/**
 * \brief Usage de la commande
 */
void erreurUsage(char * argv[]){
	fprintf(stderr, "%s: usage :\n", argv[0]);
	fprintf(stderr, "	-c  fichier_sauvegarde\n");
	fprintf(stderr, "	-g  fichier_sauvegarde\n");
	exit(10);
}




/**
 * \brief    Affiche un damier d'après le GrapheHex
 */
void afficherGrapheHex(GrapheHex g){
	int i, lgDamier;
	GrapheNoeud * metagraphe;
	
	lgDamier = GrapheHex_largeurDamier(g);
	metagraphe = GrapheHex_obtenirMetagraphe(g);
	
	for (i = 0; i < lgDamier * lgDamier; ++i){
		switch (GHElement_valeur(GrapheNoeud_obtenirElement(metagraphe[i]))){
			case 1:  printf("o");  break;
			case 2:  printf("*");  break;
			default: printf(".");  break;
		}
		if ( (i+1) % lgDamier == 0)
			printf("\n");
		else 
			printf(" ");
	}
}




/**
 * \brief    Affiche les pions d'un joueur d'après les groupes du grapheHex
 */
void afficherGroupes(GrapheHex g, Joueur j){
	int i, lgDamier;
	int cpt;
	LDC groupes;
	LDCIterateur it;
	GrapheNoeud * metagraphe;
	
	lgDamier = GrapheHex_largeurDamier(g);
	metagraphe = GrapheHex_obtenirMetagraphe(g);
	
	char affichage[lgDamier*lgDamier];
	for (i = 0; i < lgDamier * lgDamier; ++i)
		affichage[i] = 0;
	
	groupes = GrapheHex_groupes(g, j);
	it = LDCIterateur_init(groupes, LDCITERATEUR_AVANT);
	cpt = 1;
	
	for(it = LDCIterateur_debut(it); ! LDCIterateur_fin(it); it = LDCIterateur_avancer(it)){		
		for (i = 0; i < lgDamier * lgDamier; ++i)
			if (LDCIterateur_valeur(it) == metagraphe[i])
				affichage[i] = cpt;
		++cpt;
	}
	
	LDCIterateur_libererMemoire(&it);
	LDC_libererMemoire(&groupes);
	
	for (i = 0; i < lgDamier * lgDamier; ++i){
		if (affichage[i] > 0)
			printf("%d", affichage[i]); 
		else
			printf(".");
			
		if ( (i+1) % lgDamier == 0)
			printf("\n");
		else 
			printf(" ");
	}
}



/**
 * \brief Construction d'un graphe depuis un fichier 
 */
GrapheHex construireDepuisFichier(const char * fichier){
	
	GrapheHex gh;
	Partie p;
	
	p = Partie_charger(fichier);
	gh = GrapheHex_init(Partie_obtenirDamier(p));
	
	Partie_libererMemoire(&p);
	
	
	return gh;

}


/**
 * \brief Test de construction
 */
void test_construction(const char * fichier){
	GrapheHex gh;
	
	gh = construireDepuisFichier(fichier);
	
	afficherGrapheHex(gh);
	
	GrapheHex_libererMemoire(&gh);
}


/**
 * \brief Test des groupes
 */
void test_groupes(const char * fichier){
	GrapheHex gh;
	
	gh = construireDepuisFichier(fichier);
	
	afficherGroupes(gh, 0);
	afficherGroupes(gh, 1);
	afficherGroupes(gh, 2);
	
	GrapheHex_libererMemoire(&gh);
}



int main(int argc, char * argv[]){

	if (argc < 2) erreurUsage(argv);
	
	switch (argv[1][1]){
		/* Construction */
		case 'c':
			if (argc != 3) erreurUsage(argv);
			test_construction(argv[2]);
			break;
		/* Groupes */
		case 'g':
			if (argc != 3) erreurUsage(argv);
			test_groupes(argv[2]);
			break;
		
		default:
			 erreurUsage(argv);
	}
	
	return 0;
}
