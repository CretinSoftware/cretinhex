/**
 * \file Joueur.h
 * \brief Fichier header du type Joueur
 * \author Pierre POMERET-COQUOT
 * \version 1.0
 * \date 28 février 2017
 *
 */

/**
 * \defgroup paxk_hex_Joueur Joueur
 * \ingroup pack_hex
 * \brief Joueur d'une partie de Hex
 *
 * \par Description
 * Joueur est un type énuméré de trois valeurs : J1, J2 et J0
 * Il est développé dans le cadre du projet S4 (UPS Tlse3, L2 Info, session 2016-2017).
 *
 * \par Type abstrait de données
 *
 * <pre style="line-height:1em;">
 * SORTE :            Joueur
 * 
 * UTILISE :          Joueur
 *
 * CONSTRUCTEURS :    à la main : en utilisant les valeurs J1, J2, J0
 * 
 * OPERATEURS :       suivant               Joueur -> Joueur
 *                    
 * PRECONDITIONS :    Joueur_suivant(j)    => j ≠ J0
 *                                              
 * AXIOMES :          Joueur_suivant(J1) = J2
 *                    Joueur_suivant(J2) = J1
 *                    
 *                    J0 ne peut être obtenu qu'explicitement
 * </pre>
 *
 * @{
 */


# ifndef __CRETIN_HEX_JOUEUR__
# define __CRETIN_HEX_JOUEUR__

/**
 * \enum Joueur
 * Désigne les joueurs J1 et J2, le joueur J0 étant une sorte de zéro
 */
typedef enum Joueur { J0, J1, J2 } Joueur;

/**
 * \fn Joueur Joueur_suivant(Joueur j)
 * \param j Le joueur actuel
 * \return Le joueur suivant
 *
 * C'est l'équivalent de (j+1)%2 :-)
 *
 * \pre Le paramètre passé doit être différent de zéro
 */
Joueur Joueur_suivant(Joueur j);


/** @} */
# endif
