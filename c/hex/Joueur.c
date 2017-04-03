/**
 * \file Joueur.c
 * \brief Code source du type Joueur
 * \author Pierre POMERET-COQUOT
 * \version 1.0
 * \date 28 février 2017
 *
 *
 * Joueur est simplement un type énuméré possédant deux joueurs : J1 et J2 ; ainsi qu'une sorte de zéro : la valeur J0
 * On possède aussi la fonction Joueur_suivant qui permet d'alterner les joueurs.
 *
 *
 * Type abstrait de données dans le fichier header
 *     
 */
 
# include "Joueur.h"
# include <assert.h>




/*
 * \fn Joueur Joueur_suivant(Joueur j)
 * \param j Le joueur actuel
 * \return Le joueur suivant
 *
 * C'est l'équivalent de (j+1)%2 :-)
 */
Joueur Joueur_suivant(Joueur j){
	assert(j != J0);
	if (j == J1)
		return J2;
	else
		return J1;
}
