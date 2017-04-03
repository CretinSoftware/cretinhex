/**
 * \file LDC.h
 * \brief Fichier header du type LDC (liste doublement chaînée).
 * \author Pierre POMERET-COQUOT
 * \version 1.0
 * \date 1 mars 2017
 *
 */
# ifndef __CRETIN_LDC__
# define __CRETIN_LDC__






/**
 * \defgroup pack_cretinlib_LDC LDC
 * \ingroup pack_cretinlib
 * \author Pierre POMERET-COQUOT
 * \version 1.0
 * \date 1 mars 2017
 *
 * \par Description
 * \todo Rapide description
 *
 *
 * \par Type abstrait de données
 *
 * <pre style="line-height:1.1em;">
 * SORTE :            LDC
 * 
 * UTILISE :          LDCElement, int
 *
 * CONSTRUCTEURS :    LDC_init                                     _____ -> LDC
 *                    LDC_insererElement            LDC, LDCElement, int -> LDC   
 *
 * OPERATEURS :       LDC_obtenirElement                        LDC, int -> LDCElement
 *                    LDC_enleverElement                        LDC, int -> LDC
 *                    LDC_taille                                     LDC -> int
 *                    LDC_libererMemoire                      LDCElement -> _____
 *
 * </pre>
 * \todo Finir le TAD     
 *
 * @{               
 */








/**
 * \defgroup pack_cretinlib_LDCElement LDCElement
 * 
 * \par Description
 * Type manipulé par les LDC, dans lesquels vous pouvez stocker vos &laquo; trucs &raquo;
 * 
 * @{               
 */

typedef void * LDCElement;                      /**< Pointeur vers un truc externe, pour être contenu dans un LDCElement */
typedef void (*LDCElementFree)(LDCElement *);     /**< Callback pour libérer la mémoire allouée à un LDCElement par un script externe */

/** @} */







/**
 * \struct LDC
 * \brief Liste doublement chaînée
 */
typedef struct LDC * LDC;





/**
 * \brief Alloue de la mémoire pour une LDC
 * \fn LDC LDC_init()
 * \return La LDC
 *
 */
LDC LDC_init();



/**
 * \brief Insère l'élément e à la position voulue
 * \fn LDC LDC_insererElement(LDC ldc, int pos, LDCElement e, LDCElementFree free)
 * \param ldc La LDC dans laquelle on insère
 * \param pos La position de l'élément inséré
 * \param e L'élément stocké
 * \param free La méthode pour supprimer l'élément
 * \return Renvoie la LDC modifiée
 *
 * \par Utilisation
 * L'indexation des valeurs est habituelle (0 désigne le premier élément). 
 *
 * Il est aussi possible d'utiliser -1 pour désigner le dernier élément, -2 pour l'avant-dernier, etc.
 * 
 * \attention Eviter les fuites de mémoires
 * Le LDCElement transmis est un pointeur (void *) vers ce que vous voulez.
 * Le bon contrôle de la mémoire est donc en partie entre vos mains.
 * Les deux comportements raisonnables sont :
 *  - Allouer dynamiquement les LDCElements, et laisser la LDC gérer <b> exclusivement </b> leur adressage mémoire 
 *     <i>(i.e. ne faire ni réallocation ni libération de mémoire) </i>
 *  - Déclarer des variables locales <b> dans un scope plus large ou identique</b> à celui de la LDC les contenant
 *
 *
 *
 *
 */
LDC LDC_insererElement(LDC ldc, int pos, LDCElement e, LDCElementFree free);



/**
 * \fn LDCElement LDC_obtenirElement(LDC ldc, int pos)
 * \brief Donne l'élément e à la position demandée
 * \return La LDC
 * Il est aussi possible d'utiliser -1 pour désigner le dernier élément, -2 pour l'avant-dernier, etc.
 *
 */
LDCElement LDC_obtenirElement(LDC ldc, int pos);



/**
 * \fn LDC LDC_enleverElement(LDC ldc, int pos)
 * \brief Insère l'élément e à la position voulue
 * \return La LDC
 *
 */
LDC LDC_enleverElement(LDC ldc, int pos);



/**
 * \fn int LDC_taille(LDC ldc)
 * \brief Insère l'élément e à la position voulue
 * \return La LDC
 *
 */
int LDC_taille(LDC ldc);



/**
 * \fn void LDC_libererMemoire(LDC ldc)
 * \brief Libère la mémoire allouée à une LDC
 * \param ldc La LDC à supprimer
 *
 */
void LDC_libererMemoire(LDC * ldc);









/**
 * \defgroup pack_cretinlib_LDCIterateur LDCIterateur
 * \brief Itérateur
 * \author Pierre POMERET-COQUOT
 * \version 1.0
 * \date 1 mars 2017
 *
 * \par Description
 * Cet itérateur se déplace sur une LDC
 *

 *
 * @{
 */


# define LDCITERATEUR_AVANT 1
# define LDCITERATEUR_ARRIERE -1

/** 
 * \struct LDCIterateur
 * \brief Itérateur pour la LDC
 */
typedef struct LDCIterateur * LDCIterateur;


/**
 * \fn LDCIterateur LDCIterateur_init(LDC ldc)
 * \brief Instancie un itérateur
 * \param ldc La LDC sur laquelle itérer
 * \param sens Utiliser LDCITERATEUR_AVANT et LDCITERATEUR_ARRIERE
 * \return L'itérateur
 */
LDCIterateur LDCIterateur_init(LDC ldc, int sens);

/**
 * \fn void LDCIterateur_libererMemoire(LDCIterateur * it)
 * \brief Libère la mémoire allouée à un itérateur
 * \param it Pointeur vers un itérateur
 */
void LDCIterateur_libererMemoire(LDCIterateur * it);

/**
 * \fn LDCIterateur LDCIterateur_avancer(int n)
 * \brief Avance d'une position
 */
LDCIterateur LDCIterateur_avancer(LDCIterateur it);

/**
 * \fn LDCIterateur LDCIterateur_debut(LDCIterateur it)
 * \brief Amène l'itérateur au début de la LDC
 */
LDCIterateur LDCIterateur_debut(LDCIterateur it);

/**
 * \fn int LDCIterateur_fin(LDCIterateur it)
 * \brief Détermine si l'itérateur est arrivé à la fin de la ldc
 * \param it L'itérateur
 * \return Vrai si l'itérateur est hors limite
 */
int LDCIterateur_fin(LDCIterateur it);

/**
 * \fn LDCElement LDCIterateur_valeur(LDCIterateur it)
 * \brief Donne la valeur à la position de l'itérateur
 */
LDCElement LDCIterateur_valeur(LDCIterateur it);

/**
 * \fn int LDCIterateur_position(LDCIterateur it)
 * \brief Donne la valeur à la position de l'itérateur
 */
int LDCIterateur_position(LDCIterateur it);
/** @} */





/** @} */
# endif
