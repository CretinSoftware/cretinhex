/**
 * \file Partie.h
 * \brief Fichier header du type Partie permettant de manipuler des partie de Hex
 * \author Pierre POMERET-COQUOT
 * \version 1.0
 * \date 1er mars 2017
 *
 */

/**
 * \defgroup pack_hex_Partie Partie
 * \ingroup pack_hex
 * \brief Manipulateur de partie de Hex
 *
 * \par Description
 * Partie est un type permettant de manipuler des parties de Hex en C.
 * Il est développé dans le cadre du projet S4 (UPS Tlse3, L2 Info, session 2016-2017).
 *
 * \par Type abstrait de données
 *
 * <pre style="line-height:1em;">
 * SORTE :            Partie
 * 
 * UTILISE :          Joueur, Damier, LDC, char, int
 *
 * CONSTRUCTEURS :    Partie_init                   int, Joueur -> Partie     
 *                    Partie_placerPion        Partie, int, int -> Partie
 * 
 * OPERATEURS :       Partie_aQuiDeJouer                 Partie -> Joueur
 *                    Partie_largeurDamier               Partie -> int
 *                    Partie_obtenirCase       Partie, int, int -> Joueur
 *                    Partie_obtenirDamier               Partie -> Damier
 *                    Partie_obtenirTabJoueurs           Partie -> Joueur[]
 *                    Partie_obtenirTour                 Partie -> int
 *                    Partie_quiGagne                    Partie -> Joueur 
 *                    Partie_sauvegarder         Partie, char[] -> _____
 *                    Partie_charger                     char[] -> Partie
 *                    Partie_libererMemoire              Partie -> _____
 *                    
 * PRECONDITIONS :    Partie_placerPion( p, x, y )  =>   x >= 0
 *                                                     ^ x < Partie_largeurDamier( p )
 *                                                     ^ y >= 0
 *                                                     ^ y < Partie_largeurDamier( p )
 *                                                     ^ Partie_obtenirCase( p, x, y ) = VIDE
 *                                              
 *                    Partie_obtenirCase( p, x, y ) =>   x >= 0
 *                                                     ^ x < Partie_largeurDamier( p )
 *                                                     ^ y >= 0
 *                                                     ^ y < Partie_largeurDamier( p )
 *                                              
 * AXIOMES :          aQuiDeJoueur( Partie_init(l, j) )                        = j
 *                    aQuiDeJoueur( Partie_placerPion(p, x, y) )               = joueurSuivant(j)
 *                    
 *                    Partie_largeurDamier( Partie_init(l, j) )                = l
 *                    Partie_largeurDamier( Partie_placerPion(p, x, y) )       = Partie_largeurDamier(p)
 *                    
 *                    Partie_obtenirCase( Partie_init(l, j), x, y )            = VIDE
 *                    Partie_obtenirCase( Partie_placerPion(p, x, y), x, y )   = Partie_aQuiDeJouer(p)
 *                    Partie_obtenirCase( Partie_placerPion(p, x', y'), x, y ) = Partie_obtenirCase( joueurSuivant( Partie_aQuiDeJouer(p) ), x, y )
 *
 *                    Partie_obtenirDamier(p)                                  = c[]
 *                       avec c[i] = Partie_obtenirCase(p, x%Partie_largeurDamier(p), y/Partie_largeurDamier(p))
 *
 *                    Partie_obtenirTour( Partie_init(l, j) )                  = 1
 *                    Partie_obtenirTour( Partie_placerPion(p, x, y) )         = Partie_obtenirTour(p) + 1
 *                    
 *                    Partie_quiGagne( Partie_init(l, j) )                     = J0
 *                    Partie_quiGagne( Partie_placerPion(p, x, y) )            = ?
 *                    
 *                    Partie_sauvegarder(p, str) ^ Partie_charger(str)         = p  
 *
 * Les coordonnées sont numérotées à partir de 0
 *
 * </pre>                
 *                 
 * @{   
 */





# ifndef __CRETIN_HEX_PARTIE__
# define __CRETIN_HEX_PARTIE__
# include "Joueur.h"
# include "Damier.h"


/**
 * \struct Partie
 * \brief Permet la manimulation de parties
 *
 * C'est une structure de ce type qui est utilisée dans la bibliothèque JNI produite
 *
 * TAD dans le fichier header
 * \see Partie.h
 */
typedef struct Partie * Partie;



/**
 * \fn Partie Partie_init(int l, Joueur j)
 * \param l Largeur du damier
 * \param j Premier joueur
 * \return Une nouvelle Partie
 *
 * \brief Partie_init crée une Partie, initialise toutes les cases de son damier à VIDE et le numéro de tour à 1
 */
Partie Partie_init(int l, Joueur j);



/**
 * \fn Partie Partie_aQuiDeJouer(Partie p)
 * \param p La partie en question
 * \return A qui c'est-il donc de jouer ?
 *
 * \brief ¿ A quien le toca ?
 */
Joueur Partie_aQuiDeJouer(Partie p);



/**
 * \fn int Partie_largeurDamier(Partie p)
 * \param p La partie en question
 * \return La largeur du damier de cette partie
 *
 * \brief Partie_largeurDamier renvoie la largeur du damier d'une partie.
 * N.B. Il s'agit aussi de sa hauteur :-)
 */
int Partie_largeurDamier(Partie p);



/**
 * \fn int Partie_obtenirTour(Partie p)
 * \param p La partie en cours
 * \return Le tour de jeu
 *
 * \brief Renvoie le tour de jeu actuel
 */
int Partie_obtenirTour(Partie p);



/**
 * \fn Partie Partie_placerPion(Partie p, int x, int y)
 * \param p La partie en cours (this, self, etc.)
 * \param x Première coordonnée
 * \param y Seconde coordonnée
 * \return La partie en cours
 *
 * \brief Place un pion dans la case (x, y).
 *
 * \pre 0 &le; x &lt; Partie_largeurDamier(p)
 * \pre 0 &le; y &lt; Partie_largeurDamier(p)
 * \pre Partie_obtenirCase(p, x, y) = J0
 *
 * Pour rappel :
 *  - x = colonne
 *  - y = ligne
 */
Partie Partie_placerPion(Partie p, int x, int y);



/**
 * \fn Joueur Partie_obtenirCase(Partie p, int x, int y)
 * \param p La partie en cours
 * \param x Première coordonnée
 * \param y Seconde coordonnée
 * \return La partie en cours
 *
 * \brief Renvoie le joueur qui occupe la case
 *
 * \pre 0 &le; x &lt; Partie_largeurDamier(p)
 * \pre 0 &le; y &lt; Partie_largeurDamier(p)
 
 * Pour rappel :
 *  - x = colonne
 *  - y = ligne
 */
Joueur Partie_obtenirCase(Partie p, int x, int y);



/**
 * \fn Damier Partie_obtenirDamier(Partie p)
 * \brief Le damier est représenté comme un tableau linéaire
 * \param p La partie en cours
 * \return Le damier
 *
 * Pour rappel :
 *  - x = colonne
 *  - y = ligne
 *  - la case (x, y) est à l'indice (y*Partie_largeurDamier(p) + x)
 */
Damier Partie_obtenirDamier(Partie p);



/**
 * \fn Joueur * Partie_obtenirTabJoueurs(Partie p)
 * \brief Le damier est représenté comme un tableau linéaire
 * \param p La partie en cours
 * \return Le damier
 *
 * Pour rappel :
 *  - x = colonne
 *  - y = ligne
 *  - la case (x, y) est à l'indice (y*Partie_largeurDamier(p) + x)
 */
Joueur * Partie_obtenirTabJoueurs(Partie p);



/**
 * \fn Joueur * Partie_obtenirTabJoueursHisto(Partie p, int n)
 * \brief Le damier tel qu'il était au tour n
 * \param p La partie en cours
 * \param n Le tour demandé
 * \return Le damier du tour n
 *
 * \pre 0 < n &le; Partie_obtenirTour(p)
 *
 * Pour rappel :
 *  - x = colonne
 *  - y = ligne
 *  - la case (x, y) est à l'indice (y*Partie_largeurDamier(p) + x)
 */
Joueur * Partie_obtenirTabJoueursHisto(Partie p, int n);



/**
 * \fn Joueur Partie_quiGagne(Partie p)
 * \param p La partie en cours
 * \return Le gagnant (ou J0 si personne ne gagne)
 *
 * \brief Donne le gagnant d'une partie terminée, J0 sinon
 */
Joueur Partie_quiGagne(Partie p);



/**
 * \fn void Partie_sauvegarder(Partie p, char * nomFichier)
 * \param p La partie en cours
 * \param nomFichier Le fichier dans lequel effectuer la sauvegarde
 * \return -1 en cas d'échec, >= 0 en cas de succès
 *
 * \brief Sauvegarde la partie dans un fichier
 * Si le fichier existe, il sera écrasé
 */
int Partie_sauvegarder(Partie p, const char * nomFichier);



/**
 * \fn Partie Partie_charger(char * nomFichier)
 * \param nomFichier Le fichier dans lequel lire la partie
 * \return La partie lue
 *
 * \brief Charge une partie depuis un fichier
 * Le fichier doit être un fichier de sauvegarde valide
 * (i.e. créé avec Partie_sauvegarder)
 */
Partie Partie_charger(const char * nomFichier);




/**
 * \fn void Partie_libererMemoire(Partie p)
 * \param p La partie à supprimer
 *
 * \brief Libère la mémoire allouée à une Partie
 */
void Partie_libererMemoire(Partie * p);




/** @} */

# endif


