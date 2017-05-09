/**
 * \file Partie.c
 * \brief Code source du type Partie permettant de manipuler des parties de Hex
 * \author Pierre POMERET-COQUOT
 * \version 1.0
 * \date 1er mars 2017
 *
 * \todo Gestion des sauvegardes
 * \todo Historique
 * \todo Détermination du gagnant
 * \todo Graphe simplifié
 *
 *
 *
 * Partie est un type permettant de manipuler des parties de Hex en C.
 * Il est développé dans le cadre du projet S4 (UPS Tlse3, L2 Info, session 2016-2017).
 *
 *
 * Type abstrait de données dans le fichier header
 * \see Partie.h
 *     
 */

# include "Partie.h"
# include "GrapheHex.h"
# include <stdlib.h>
# include <stdio.h>
# include <assert.h>
# include "Damier.h"
# include "../cretinlib/LDC.h"





/** 
 * \defgroup pack_hex_ElemHistp ElemHisto
 * \ingroup pack_hex
 * \brief Element de l'historique d'une partie.
 * @{
 */

/**
 * \struct ElemHisto 
 * \brief Stocke l'information d'un tour de jeu
 */
typedef struct ElemHisto {
	Joueur joueur;          /**< \brief Le joueur qui à joué ce tour */
	int x;                  /**< \brief Première coordonnée du coup joué */
	int y;                  /**< \brief Seconde coordonnée du coup joué */
} * ElemHisto;

/**
 * \brief Instancie un ElemHisto
 * \param j Le joueur ayant joué ce tour
 * \param x 1ère coordonnée
 * \param y 2nde coordonnée
 * \pre joueur &ne; J0
 * \note les coordonnées x et y ne sont pas véifiées
 */
ElemHisto ElemHisto_init(Joueur j, int x, int y){
	ElemHisto eh = (ElemHisto) malloc(sizeof(struct ElemHisto));
	eh->joueur = j;
	eh->x = x;
	eh->y = y;
	return eh;
}

/**
 * \brief Libère la mémoire allouée à un ElemHisto
 * \param eh Adresse de l'ElemHisto à supprimer
 */
void ElemHisto_libererMemoire(ElemHisto * eh){
	free(*eh);
}

/** @} */



/**
 * \struct PartieInterne
 * \brief Ce vers quoi pointe une Partie
 * @{
 */
typedef struct Partie {
	Joueur premierJoueur;    /**< \brief Le joueur qui à commencé la partie (différent de J0) */
	Joueur aQuiDeJouer;      /**< \brief Le joueur qui doit faire le prochain mouvement (différent de J0) */
	Damier damier;           /**< \brief L'occupation de toutes les cases */
	int tour;                /**< \brief Compteur de tour */
	LDC historique;          /**< \brief Historique : tous les movements joués */
	GrapheHex graphehex;     /**< \brief GrapheHex : le graphe simplifié */
} PartieInterne;

/** @} */
	





/*
 * \fn Partie Partie_init(int l, Joueur j)
 * \param l Largeur du damier
 * \param j Premier joueur
 * \return Une nouvelle partie
 *
 * Partie_init crée une Partie, initialise toutes les cases de son damier à VIDE et le numéro de tour à 1
 */
Partie Partie_init(int l, Joueur j){
	Partie p = (Partie) malloc( sizeof(PartieInterne) );
	assert(p != NULL);
	
	p->tour = 1;
	p->premierJoueur = j;
	p->aQuiDeJouer = j;
	p->damier = Damier_init(l);
	p->historique = LDC_init();
	p->graphehex = GrapheHex_init(p->damier);
	
	return p;
}





/*
 * \fn Partie Partie_aQuiDeJouer(Partie p)
 * \param p La partie en question
 * \return a qui c'est donc de jouer ?
 *
 * ¿ A quien le toca ?
 */
Joueur Partie_aQuiDeJouer(Partie p){
	return p->aQuiDeJouer;
}





/*
 * \fn int Partie_largeurDamier(Partie p)
 * \param p La artie en question
 * \return La largeur du damier de cette partie
 *
 * Partie_largeurDamier renvoie la largeur du damier d'une partie.
 * N.B. Il s'agit aussi de sa hauteur :-)
 */
int Partie_largeurDamier(Partie p){
	return Damier_obtenirLargeur(p->damier);
}





/*
 * \fn int Partie_obtenirTour(Partie p)
 * \param p La partie en cours
 * \return Le tour de jeu
 *
 * Renvoie le tour de jeu actuel
 */
int Partie_obtenirTour(Partie p){
	return p->tour;
}





/*
 * \fn Partie Partie_placerPion(Partie p, int x, int y)
 * \param p La partie en cours (this, self, etc.)
 * \param x Première coordonnée
 * \param y Seconde coordonnée
 * \return La partie en cours
 *
 * Place un pion dans la case (x, y).
 * Pour rappel :
 *  - x = colonne
 *  - y = ligne
 */
Partie Partie_placerPion(Partie p, int x, int y){
	assert(Damier_obtenirCase(p->damier, x, y) == J0);
	/* Placement du pion */
	p->damier = Damier_modifierCase(p->damier, p->aQuiDeJouer, x, y);
	p->graphehex = GrapheHex_modifierCase(p->graphehex, x, y, p->aQuiDeJouer);
	
	/* Ajoute à l'historique */
	ElemHisto eh = ElemHisto_init(p->aQuiDeJouer, x, y);
	p->historique = LDC_insererElement(p->historique, -1, eh, (LDCElementFree) ElemHisto_libererMemoire);
	
	/* Avance d'un tour */
	p->aQuiDeJouer = Joueur_suivant(p->aQuiDeJouer);
	++p->tour;
	return p;
}





/*
 * \fn Joueur Partie_obtenirCase(Partie p, int x, int y)
 * \param p La partie en cours (this, self, etc.)
 * \param x Première coordonnée
 * \param y Seconde coordonnée
 * \return La partie en cours
 *
 * Renvoie le joueur qui occupe la case
 * Pour rappel :
 *  - x = colonne
 *  - y = ligne
 */
Joueur Partie_obtenirCase(Partie p, int x, int y){
	return Damier_obtenirCase(p->damier, x, y);
}





/*
 * \fn Damier Partie_obtenirDamier(Partie p)
 * \param p La partie en cours
 * \return Le damier
 *
 * \brief Le damier est représenté comme un tableau linéaire
 * Pour rappel :
 *  - x = colonne
 *  - y = ligne
 *  - la case (x, y) est à l'indice (y*Partie_largeurDamier(p) + x)
 */
Damier Partie_obtenirDamier(Partie p){
	return p->damier;
}





/*
 * \fn Joueur * Partie_obtenirTabJoueurs(Partie p)
 * \param p La partie en cours
 * \return Le damier
 *
 * \brief Le damier est représenté comme un tableau linéaire
 * Pour rappel :
 *  - x = colonne
 *  - y = ligne
 *  - la case (x, y) est à l'indice (y*Partie_largeurDamier(p) + x)
 */
Joueur * Partie_obtenirTabJoueurs(Partie p){
	return Damier_obtenirTabJoueurs(p->damier);
}



/**
 * \fn Joueur * Partie_obtenirTabJoueursHisto(Partie p)
 * \brief Le damier tel qu'il était au tour n
 * \param p La partie en cours
 * \param n Le tour demandé
 * \return Le damier du tour n
 *
 * \req 0 < n &le; Partie_obtenirTour(p)
 *
 * \todo Travailler avec un itérateur !
 */
Joueur * Partie_obtenirTabJoueursHisto(Partie p, int n){
	Damier d = Damier_init(Damier_obtenirLargeur(p->damier));
	LDCIterateur it = LDCIterateur_init(p->historique, LDCITERATEUR_AVANT);
	ElemHisto eh;
	for (it = LDCIterateur_debut(it); LDCIterateur_position(it) < n - 1; it = LDCIterateur_avancer(it)){
		eh = (ElemHisto) LDCIterateur_valeur(it);
		d = Damier_modifierCase(d, eh->joueur, eh->x, eh->y);
	}
	LDCIterateur_libererMemoire(&it);
	return Damier_obtenirTabJoueurs(d);
}
	






/*
 * \fn Joueur Partie_quiGagne(Partie p)
 * \param p La partie en cours
 * \return Le gagnant (ou J0 si personne ne gagne)
 *
 * \brief Donne le gagnant d'une partie terminée, J0 sinon
 */
Joueur Partie_quiGagne(Partie p){
	return GrapheHex_quiGagne(p->graphehex);
}







char joueur2char(Joueur j){
	switch (j){
		case J1: return 'o';
		case J2: return '*';
		default: return '.';
	}
}

Joueur char2joueur(char c){
	switch (c){
		case 'o': return J1;
		case '*': return J2;
		default:  return J0;
	}
}




/*
 * \fn void Partie_sauvegarder(Partie p, char * nomFichier)
 * \param p La partie en cours
 * \param nomFichier Le fichier dans lequel effectuer la sauvegarde
 * \return Le gagnant (ou J0 si personne ne gagne)
 *
 * \brief Sauvegarde la partie dans un fichier
 * Si le fichier existe, il sera écrasé
 *
 * \bug Ne gère pas les fichiers vides
 *
 */
int Partie_sauvegarder(Partie p, const char * nomFichier){
	FILE * f;
	int i;
	int l = Damier_obtenirLargeur(p->damier);
	Joueur * damier = Damier_obtenirTabJoueurs(p->damier);
	
	/* Ouverture du fichier */
	f = fopen(nomFichier, "w");
	if (f == NULL)
		return -1;
	
	
	/* En-tête */
	fprintf(f, "\\hex\n");
	
	/* Largeur */
	fprintf(f, "\\dim %d\n", l);
	
	/* Damier */
	/* On crée la chaine avant de l'envoyer dans le fichier (moins d'accès système) */
	char str[2 * l * l];
	for (i = 0; i < l * l; ++i){
		str[2*i] = joueur2char(damier[i]);
		if ((i+1) % l == 0)
			str[2*i+1] = '\n';
		else
			str[2*i+1] = ' ';
	}
	str[2*i-1] = '\0';
	fprintf(f, "\\board\n%s\n\\endboard\n", str);
	
	/* Historique */
	ElemHisto eh;
	fprintf(f, "\\game\n");
	for (i = 1; i < p->tour; ++i){
		eh = (ElemHisto) LDC_obtenirElement(p->historique, i-1);
		fprintf(f, "\\play %c %d %d\n", joueur2char(eh->joueur), eh->x, eh->y);
	}
	fprintf(f, "\\endgame\n");
	
	/* Pied de page */
	fprintf(f, "\\endhex\n");
	
	
	/* Fermeture du fichier */	
	fclose(f);
	
	/* Désalloc */
	free(damier);
	
	return 0;
}





void formatFichierIncorrect(const char * nomFichier){
	fprintf(stderr, "Impossible de lire le fichier %s : format incorrect\n", nomFichier);
	exit(2);
}



/*
 * \fn Partie Partie_charger(char * nomFichier)
 * \param nomFichier Le fichier dans lequel lire la partie
 * \return La partie lue
 *
 * \brief Charge une partie depuis un fichier
 * Le fichier doit être un fichier de sauvegarde valide
 * (i.e. créé avec Partie_sauvegarder)
 *
 * \attention Impossible de charger des sauvegardes du tour 0 ! Que faire ?
 * \todo Trouver comment charger des sauvegardes du tour 0, ou l'interdire...
 */
Partie Partie_charger(const char * nomFichier){

	FILE * f;
	int i, l, x, y;
	char c;
	Partie p;
	/*ElemHisto eh;
	Joueur j;*/
	
	
	/* Ouverture du fichier */
	f = fopen(nomFichier, "r");
	if (f == NULL){
		exit(-1);
	}
	
	
	/* En-tête */
	fscanf(f, "\\hex\n");
	
	/* Largeur */
	if (fscanf(f, "\\dim %d\n", &l) != 1)
		formatFichierIncorrect(nomFichier);
	
	p = Partie_init(l, J1);
	

	/* Damier */
	
	fscanf(f, "\\board\n");
	for (i = 0; i < l * l; ++i)
		if (fscanf(f, "%c ", &c) == 1)
			;/*Damier_modifierCase(p->damier, char2joueur(c), i%l, i/l);*/
		else
			formatFichierIncorrect(nomFichier);
	fscanf(f, "\\endboard\n");
	
	
	/* Les pions sont placés d'après l'historique. Plus de vérif... */
	/** \todo Vérification de la correspondance damier / historique */
	
	/* Historique + premier joueur + aQuiDeJouer + vérification des coups ! */
	fscanf(f, "\\game\n");
	i = 1;
	while (fscanf(f, "\\play %c %d %d\n", &c, &x, &y)){
		/*j = char2joueur(c);
		assert(Partie_obtenirCase(p, x, y) == j);*/
		
		if (i == 1){
			p->premierJoueur = char2joueur(c);
			p->aQuiDeJouer = p->premierJoueur;
		}
		
		p = Partie_placerPion(p, x, y);
		/*eh = ElemHisto_init(j, x, y);
		p->historique = LDC_insererElement(p->historique, -1, eh, (LDCElementFree) ElemHisto_libererMemoire); */
		++i;
	}
	fscanf(f, "\\game\n");
/*	p->aQuiDeJouer = Joueur_suivant(j);
	p->tour = i;
	*/
		
	
	
	/* Fermeture du fichier */	
	fclose(f);
	
	return p;
}




/*
 * \fn Partie Partie_annuler(int nombreDeTours)
 * \param p La partie à modifier
 * \param nombreDeTours Le nombre de tours à annuler
 * \return La partie lue
 *
 * \brief Annule les nombreDeTours derniers tours
 *
 * \pre  nomBreDeTours < Partie_obtenirTour(p)
 */
Partie Partie_annuler(Partie p, int nombreDeTours){
	assert(nombreDeTours < Partie_obtenirTour(p));
	int i;
	ElemHisto eh;
	
	for (i = 0; i < nombreDeTours; ++i){
		eh = (ElemHisto) LDC_obtenirElement(p->historique, -1);
		Damier_modifierCase(p->damier, J0, eh->x, eh->y);
		-- p->tour;
		p->aQuiDeJouer = Joueur_suivant(p->aQuiDeJouer);
		p->historique = LDC_enleverElement(p->historique, -1);
	}
	
	return p;
}



/**
 * \fn void Partie_libererMemoire(Partie p)
 * \param p La partie à supprimer
 *
 * \brief Libère la mémoire allouée à une Partie
 */
void Partie_libererMemoire(Partie * p){
	Damier_libererMemoire(&((*p)->damier));
	LDC_libererMemoire(&((*p)->historique));
	GrapheHex_libererMemoire(&((*p)->graphehex));
	free(*p);
	*p = NULL;
}



