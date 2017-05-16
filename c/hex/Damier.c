/**
 * \file Damier.c
 * \brief Code source du type Damier permettant de manipuler des matrices carrées
 * \author Pierre POMERET-COQUOT
 * \version 1.0
 * \date 28 février 2017
 *
 *
 * Damier est un type permettant de manipuler des parties de Hex en C.
 * Il est développé dans le cadre du projet S4 (UPS Tlse3, L2 Info, session 2016-2017).
 *
 *
 * Type abstrait de données dans le fichier header
 *
 * \todo Eviter la confusion entre le type Damier et les variables de type (Joueur *)
 *                    
 */



# include <stdlib.h>
# include <stdio.h>
# include <assert.h>
# include "Damier.h"



/**
 * \struct DamierInterne
 * \brief Ce vers quoi pointe un Damier
 * - largeur : La largeur de la matrice carrée
 * - cellules : un tableau de largeur * largeur variables de type Joueur
 *
 * C'est une structure de ce type qui est utilisée dans la bibliothèque JNI produite
 */
typedef struct Damier {
	int largeur;           /**< \brief Largeur du damier (i.e; hauteur : le damier est carré) */
	Joueur * cellules;     /**< \brief Zone mémoire contenant les occupant des <i>largeur x largeur</i> cases */
} DamierInterne;




/*
 * \fn Damier Damier_init(int l)
 * \param l Largeur du damier
 * \return Le damier
 *
 * Damier_init crée un damier de l x l cases
 */
Damier Damier_init(int l){
	int i;
	
	Damier d = (Damier) malloc(sizeof(DamierInterne));
	assert(d != NULL);
	
	d->largeur = l;
	
	d->cellules = (Joueur *) malloc(l * l * sizeof(Joueur));
	assert(d->cellules != NULL);
	for (i = 0; i < l * l; ++i)
		d->cellules[i] = J0;
	
	return d;
}



/*
 * \fn Damier Damier_modifierCase(Damier d, Joueur j, int x, int y)
 * \param d Le damier à modifier
 * \param j La valeur à entrer
 * \param x Première coordonnée
 * \param y Seconde coordonnée
 * \return Le damier modifié
 *
 * Place le Joueur j dans la case (x, y).
 * Pour rappel :
 *  - x = colonne
 *  - y = ligne
 */
Damier Damier_modifierCase(Damier d, Joueur j, int x, int y){
	assert(x >= 0 && x < d->largeur);
	assert(y >= 0 && y < d->largeur);
	d->cellules[ x + (y * d->largeur) ] = j;
	return d;
}



/**
 * \fn Damier Damier_copier(Damier d)
 * \param d Le damier à copier
 * \brief Duplique un damier
 *
 */
Damier Damier_copier(Damier d){
	int i;
	
	Damier d2 = (Damier) malloc(sizeof(DamierInterne));
	assert(d2 != NULL);
	
	d2->largeur = d->largeur;
	
	d2->cellules = (Joueur *) malloc(d->largeur * d->largeur * sizeof(Joueur));
	assert(d->cellules != NULL);
	for (i = 0; i < d->largeur * d->largeur; ++i)
		d2->cellules[i] = d->cellules[i];
	
	return d2;
}




/*
 * \fn Joueur Damier_obtenirCase(Damier d, int x, int y)
 * \param d Le damier à consulter
 * \param x Première coordonnée
 * \param y Seconde coordonnée
 * \return Le joueur détenant la case (x,y)
 *
 * Obtenir le Joueur de la case (x, y).
 * Pour rappel :
 *  - x = colonne
 *  - y = ligne
 */
Joueur Damier_obtenirCase(Damier d, int x, int y){
	assert(x >= 0 && x < d->largeur);
	assert(y >= 0 && y < d->largeur);
	return d->cellules[ x + (y * d->largeur) ];
}




/*
 * \fn int Damier_obtenirLargeur(Damier d)
 * \param d Le damier à consulter
 * \return La largeur du damier (qui est aussi sa longueur)
 *
 */
int Damier_obtenirLargeur(Damier d){
	return d->largeur;
}




/*
 * \fn Joueur * Damier_obtenirTabJoueurs(Damier d)
 * \param d Le damier à consulter
 * \return Un tableau linéaire de joueur
 *
 * \brief Obtenir toutes les cases du damier sous forme d'un tableau linéaire
 * Pour rappel :
 *  - x = colonne
 *  - y = ligne
 *  - La case (x, y) est à l'indice (Damier_obtenirLargeur(d)*y + x)
 */
Joueur * Damier_obtenirTabJoueurs(Damier d){
	Joueur * tab = (Joueur *) malloc(sizeof(Joueur) * d->largeur * d->largeur);
	assert(tab != NULL);
	int i;
	for (i = 0; i < d->largeur * d->largeur; ++i)
		tab[i] = d->cellules[i];
	return tab;
}




/*
 * \fn void Damier_libererMemoire(Damier d)
 * \param d Le damier à enlever
 *
 *
 */
void Damier_libererMemoire(Damier * d){
	free((*d)->cellules);
	free(*d);
}



