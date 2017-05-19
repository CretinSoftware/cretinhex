

# ifndef __CRETINLIB_ARN__
# define __CRETINLIB_ARN__


# include "ABR.h"


/**
 * \defgroup pack_cretinlib_arn ARN
 * \ingroup pack_cretinlib
 * \author Pierre POMERET-COQUOT
 * \brief Arbre rouge-noir
 *
 * \par Description
 * Les ABR on été implémentés pour concurrencer la LDC sur les opérations de recherches.
 * Ils sont très efficaces, car en O(log n)
 *
 * \par Implémentation
 * D'un point de vue technique, les ABR sont des alias d'ARN, disposant de nouveaux opérateurs
 *
 * \attention Les ARN sont des alias d'ABR, possédant d'autres opérateurs. 
 *            Si vous souhaitez utiliser les deux types simultanément, il vous faut inclure des deux fichiers *header*, mais **uniquement le code source ARN.c**.
 * 
 * \note La fonction d'évaluation utilisée est bien souvent celle renvoyant l'adresse d'un élément. Il est alors important de se rendre compte que,
 * les adresses mémoires étant habituellement allouées dans l'ordre croissant, on pourra observer une tendance à recevoir les éléments triés.
 * Dans ce cas extrème, la complexité des ABR est en O(n), et nous conseillons l'utilisation des [\ref ARN]
 *
 * @{
 */





/**
 * \addtogroup pack_cretinlib_arn_arnelement ARNElement
 * \brief    Elément à insérer dans un arbre rouge-noir
 *
 * Comme pour tous les types génériques, l'élément est un alias de pointeur void. N'importe quelle adresse mémoire peut donc être utilisée
 *
 * @{
 */

typedef ABRElement ARNElement;                   /**< Pointeur vers un truc externe, pour être contenu dans un ARNElement */
typedef ABRElementFree ARNElementFree;           /**< Callback pour libérer la mémoire allouée à un ARNElement par un script externe */
typedef ABRElementEgal ARNElementEgal;           /**< Fonction attribuant une valeur entière à un noeud d'ARN */
typedef ABRElementEval ARNElementEval;           /**< Fonction attribuant une valeur entière à un noeud d'ARN */

int ARNElement_adresse(ARNElement e);            /**< Fonction attribuant l'adresse d'un élément comme valeur */

/** @} */


/** \brief Arbre rouge-noir */
typedef ABR ARN;

/**
 * \brief    Initialise un ARN vide
 */
ARN ARN_init(ARNElementEval eval);

/**
 * \brief    Nombre d'éléments contenus dans l'ARN
 */
int ARN_taille(ARN anr);

/**
 * \brief    Insère un élément dans l'ARN
 * \param    arn  Celui dans lequel on insère
 * \param    e    L'élément à insérer
 * \param    free Fonction effaçant l'élément à la suppression de l'ARN, ou NULL
 */
ARN ARN_inserer(ARN arn, ARNElement e, ARNElementFree free);

/**
 * \brief    Test d'appartenance
 * \return   0 si la valeur est absente, différent de 0 sinon
 */
int ARN_chercher(ARN arn, ARNElement e);

/**
 * \brief    Enlève un élément de l'arbre
 * \note     La fonction ARNElementFree transmise lors de l'ajout de l'élément sera appliquée
 * \pre      si e n'appartient pas à l'arbre, aucune action n'est réalisée
 */
ARN ARN_enlever(ARN arn, ARNElement e);

/**
 * \brief    Duplique un ARN
 */
ARN ARN_copier(ARN arn);

/**
 * \brief    Libère la mémoire allouée à un ARN et appelle les fonction ARNElementFree pour chacun de ses éléments
 */
void ARN_free(ARN * arn);


/**
 * \brief    Fusionne deux ARN
 */
ARN ARN_fusion(ARN abr1, ARN abr2);

/**
 * \brief    Fusionne deux ARN en évitant les doublons (union)
 */
ARN ARN_fusionSansDoublons(ARN abr1, ARN abr2);


/**
 * \brief    Intersection de arn1 et arn2
 */
ARN ARN_filtrer(ARN arn1, ARN arn2);

/**
 * \brief    arn1 privé de arn2
 */
ARN ARN_exfiltrer(ARN arn1, ARN arn2);


/**
 * \brief    Produit un arbre contenant les éléments de arn1 validant une condition 
 */
ARN ARN_filtrerCondition(ARN arn1, ARNElementEval);

/**
 * \brief    Produit un arbre contenant les éléments de arn1 ne validant pas une condition
 */
ARN ARN_exfiltrerCondition(ARN arn1, ARNElementEval);


/** @} */
# endif
