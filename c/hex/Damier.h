/**
 * \file Damier.h
 * \brief Fichier header du type Damier permettant de manipuler des matrices carrées
 * \author Pierre POMERET-COQUOT
 * \version 1.0
 * \date 28 février 2017
 *
 */

/**
 * \defgroup pack_hex_Damier Damier
 * \ingroup pack_hex 
 * \brief Plateau de Hex
 *
 * \par Description
 * Damier est un type permettant de manipuler des parties de Hex en C.
 * Il est développé dans le cadre du projet S4 (UPS Tlse3, L2 Info, session 2016-2017).
 *
 * \par Type abstrait de données
 *
 * <pre style="line-height:1em;">
 * SORTE :            Damier
 * 
 * UTILISE :          Joueur, int
 *
 * CONSTRUCTEURS :    Damier_init                                   int -> Damier     
 *                    Damier_modifierCase      Damier, Joueur, int, int -> Damier
 * 
 * OPERATEURS :       Damier_obtenirLargeur                      Damier -> int
 *                    Damier_obtenirCase               Damier, int, int -> Joueur
 *                    Damier_obtenirTabJoueurs                   Damier -> Joueur[]
 *                    Damier_libererMemoire                      Damier -> _____
 *                    
 * PRECONDITIONS :    Damier_modifierCase( d, x, y )  =>   x >= 0
 *                                                       ^ x < obtenirLargeur( p )
 *                                                       ^ y >= 0
 *                                                       ^ y < obtenirLargeur( p )
 *                                              
 *                    Damier_obtenirCase( p, x, y )   =>   x >= 0
 *                                                       ^ x < obtenirLargeur( p )
 *                                                       ^ y >= 0
 *                                                       ^ y < obtenirLargeur( p )
 *                                              
 * AXIOMES :          Damier_obtenirLargeur( Damier_init(l) )                       = l
 *                    Damier_obtenirLargeur( Damier_modifierCase(d, j, x, y) )      = obtenirLargeur(d)
 *                    
 *                    Damier_obtenirCase( Damier_init(l), x, y )                    = VIDE
 *                    Damier_obtenirCase( Damier_modifierCase(d, j, x, y), x, y )   = j
 *                    Damier_obtenirCase( Damier_modifierCase(d, j, x', y'), x, y ) = obtenirCase( d, x, y )
 *
 * Les coordonnées sont numérotées à partir de 0
 *
 * </pre>                
 *           
 *
 * @{         
 */





# ifndef __CRETIN_HEX_DAMIER__
# define __CRETIN_HEX_DAMIER__
# include "Joueur.h"



/**
 * \struct Damier
 * \brief Manipulateur de matrices carrées de type Joueur *
 */
typedef struct Damier * Damier;



/**
 * \fn Damier Damier_init(int l)
 * \param l Largeur du damier
 * \return Le damier
 *
 * \brief Damier_init crée un damier de l x l cases
 *
 * \note Les cases sont mise à J0.
 */
Damier Damier_init(int l);



/**
 * \fn Damier Damier_modifierCase(Damier d, Joueur j, int x, int y)
 * \param d Le damier à modifier
 * \param j La valeur à entrer
 * \param x Première coordonnée
 * \param y Seconde coordonnée
 * \return Le damier modifié
 *
 * \brief Place le Joueur j dans la case (x, y).
 *
 * \pre 0 &le; x &lt; Damier_obtenirLargeur(d)
 * \pre 0 &le; y &lt; Damier_obtenirLargeur(d)
 *
 * Pour rappel :
 *  - x = colonne
 *  - y = ligne
 */
Damier Damier_modifierCase(Damier d, Joueur j, int x, int y);




/**
 * \fn Joueur Damier_obtenirCase(Damier d, int x, int y)
 * \param d Le damier à consulter
 * \param x Première coordonnée
 * \param y Seconde coordonnée
 * \return Le joueur détenant la case (x,y)
 *
 * \brief Obtenir le Joueur de la case (x, y).
 *
 * \pre 0 &le; x &lt; Damier_obtenirLargeur(d)
 * \pre 0 &le; y &lt; Damier_obtenirLargeur(d)
 *
 * Pour rappel :
 *  - x = colonne
 *  - y = ligne
 */
Joueur Damier_obtenirCase(Damier d, int x, int y);




/**
 * \fn int Damier_obtenirLargeur(Damier d)
 * \param d Le damier à consulter
 * \return La largeur du damier (qui est aussi sa longueur)
 *
 * \brief Pour connaître la largeur du Damier (qui est aussi sa hauteur)
 *
 */
int Damier_obtenirLargeur(Damier d);




/**
 * \fn Joueur * Damier_obtenirTabJoueurs(Damier d)
 * \param d Le damier à consulter
 * \return Un tableau linéaire de joueur
 *
 * \brief Obtenir toutes les cases du damier sous forme d'un tableau linéaire
 *
 * \attention L'allocation du retour étant dynamique, il faudra penser à le supprimer manuellement avec <i>free()</i>
 *
 * Le pointeur retourné désigne un tableau de taille Damier_obtenirLargeur(d) ^ 2 
 */
Joueur * Damier_obtenirTabJoueurs(Damier d);




/**
 * \fn void Damier_libererMemoire(Damier d)
 * \param d Le damier à enlever
 *
 * \brief Libère l'espace mémoire alloué au Damier.
 */
void Damier_libererMemoire(Damier * d);



/** @} */

# endif
