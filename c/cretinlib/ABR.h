

# ifndef __CRETINLIB_ABR__
# define __CRETINLIB_ABR__


# include "utile.h"


/**
 * \defgroup pack_cretinlib_abr ABR
 * \ingroup pack_cretinlib
 * \author Pierre POMERET-COQUOT
 * \brief Arbre binaire de recherche
 *
 * \par Description
 * Les ABR on été implémentés pour concurrencer la LDC sur les opérations de recherches.
 * Ils sont très efficaces, car en O(log n), même si on aura tendance à utiliser les ARN
 *
 * 
 * \note La fonction d'évaluation utilisée est bien souvent celle renvoyant l'adresse d'un élément. Il est alors important de se rendre compte que,
 * les adresses mémoires étant habituellement allouées dans l'ordre croissant, on pourra observer une tendance à recevoir les éléments triés.
 * Dans ce cas extrème, la complexité des ABR est en O(n), et nous conseillons l'utilisation des [\ref ARN]
 *
 * @{
 */





/**
 * \addtogroup pack_cretinlib_abr_abrelement ABRElement
 * \brief    Elément à insérer dans un arbre
 *
 * Comme pour tous les types génériques, l'élément est un alias de pointeur void. N'importe quelle adresse mémoire peut donc être utilisée
 *
 * @{
 */

typedef void * ABRElement;                              /**< \brief Pointeur vers un truc externe, pour être contenu dans un ABRElement */
typedef void (*ABRElementFree)(ABRElement *);           /**< \brief Callback pour libérer la mémoire allouée à un ABRElement par un script externe */
typedef int (*ABRElementEgal)(ABRElement, ABRElement);  /**< \brief Egalité entre deux éléments */
typedef int (*ABRElementEval)(ABRElement);              /**< \brief Fonction attribuant une valeur entière à un noeud d'ABR */

int ABRElement_adresse(ABRElement e);                   /**< \brief Fonction attribuant l'adresse d'un élément comme valeur */

/** @} */



/** \brief Arbre binaire de recherche */
typedef struct ABR * ABR;



/** 
 * \brief    Initialisation d'un ABR
 * \param    eval Fonction évaluant (donnant une note) aux éléments
 */
ABR ABR_init(ABRElementEval eval);

/** 
 * \brief    Nombre de valeurs contenues dans un ABR
 */
int ABR_taille(ABR abr);

/**
 * \brief    Insère un élément dans un ABR
 * \param    abr  L'arbre dans lequel on insère
 * \param    e    L'élément à insérer
 * \param    free Fonction effaçant l'élément à la destruction de l'ABR, ou NULL
 */
ABR ABR_inserer(ABR abr, ABRElement e, ABRElementFree free);

/**
 * \brief    Insère un élément dans un ABR, s'il n'est pas déjà présent
 * \param    abr  L'arbre dans lequel on insère
 * \param    e    L'élément à insérer
 * \param    free Fonction effaçant l'élément à la destruction de l'ABR, ou NULL
 * \note     La présence de l'élément est testée avec la fonction d'évaluation transmise lors de l'initialisation de l'arbre
 */
ABR ABR_insererSansDoublons(ABR abr, ABRElement e, ABRElementFree free);

/** 
 * \brief    Teste la présence d'un élément
 */
int ABR_chercher(ABR abr, ABRElement e);

/** 
 * \brief    Supprime un élément de l'arbre
 */
ABR ABR_enlever(ABR abr, ABRElement e);

/** 
 * \brief    Créer une copie de l'arbre
 */
ABR ABR_copier(ABR abr);

/** 
 * \brief    Libère la mémoire allouée à un arbre (et a ses éléments si une fonction ABRElementFree a été transmise
 */
void ABR_free(ABR * abr);

/** 
 * \brief    Fusionne deux arbres
 */
ABR ABR_fusion(ABR abr1, ABR abr2);

/** 
 * \brief    Fusionne deux arbres en évitant les doublons
 */
ABR ABR_fusionSansDoublons(ABR abr1, ABR abr2);




/** 
 * \addtogroup pack_cretinlib_abr_abriterateur ABRIterateur
 * \brief    Itérateur pour arbres binaires de recherche
 *
 * \par Description
 * L'itérateur ne permet pas de profiter de la complexité moyenne en O(log n) des arbres binaires.
 * Néanmoins il peut être utile de parcourir tous les éléments d'un arbre, en O(n).
 * La méthode de parcours choisie est le parcours en profondeur infixe, qui renvoie les éléments triés dans l'ordre croissant, 
 * selon le critère de la fonction d'évaluation transmise à l'initialisation de l'arbre
 */
 
/** 
 * \struct   ABRIterateur
 * \brief    Itérateur pour arbres binaires de recherche
 */
typedef struct ABRIterateur * ABRIterateur;


/** 
 * \brief    Initialise un Itérateur d'ABR
 */
ABRIterateur ABRIterateur_init(ABR abr);

/** 
 * \brief    Place le curseur sur le premier noeud (la feuille la plus a gauche)
 */
ABRIterateur ABRIterateur_debut(ABRIterateur it);

/** 
 * \brief    Affirme qu'on a terminé le parcours (donc qu'on a dépassé la feuille la plus à droite)
 */
int ABRIterateur_fin(ABRIterateur it);

/** 
 * \brief    Fait avancer le curseur (parcours en profondeur infixe)
 */
ABRIterateur ABRIterateur_avancer(ABRIterateur it);

/** 
 * \brief    Donne l'élément contenu dans l'arbre, sous le curseur
 */
ABRElement ABRIterateur_valeur(ABRIterateur it);

/** 
 * \brief    Libède la mémoire allouée à l'itérateur
 */
void ABRIterateur_free(ABRIterateur * it);
			
			


/** @} @} */




# endif
