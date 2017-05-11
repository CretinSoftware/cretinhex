

# ifndef __CRETINLIB_ARN__
# define __CRETINLIB_ARN__


# include "ABR.h"


typedef ABRElement ARNElement;                   /**< Pointeur vers un truc externe, pour être contenu dans un ARNElement */
typedef ABRElementFree ARNElementFree;           /**< Callback pour libérer la mémoire allouée à un ARNElement par un script externe */
typedef ABRElementEgal ARNElementEgal;           /**< Fonction attribuant une valeur entière à un noeud d'ARN */
typedef ABRElementEval ARNElementEval;           /**< Fonction attribuant une valeur entière à un noeud d'ARN */

int ARNElement_adresse(ARNElement e);            /**< Fonction attribuant l'adresse d'un élément comme valeur */

typedef ABR ARN;


ARN ARN_init(ARNElementEval eval);
int ARN_taille(ARN anr);
ARN ARN_inserer(ARN arn, ARNElement e, ARNElementFree free);
int ARN_chercher(ARN arn, ARNElement e);
ARN ARN_enlever(ARN arn, ARNElement e);
ARN ARN_copier(ARN arn);
void ARN_free(ARN * arn);

ARN ARN_fusion(ARN abr1, ARN abr2);
ARN ARN_fusionSansDoublons(ARN abr1, ARN abr2);

ARN ARN_filtrer(ARN arn1, ARN arn2);
ARN ARN_exfiltrer(ARN arn1, ARN arn2);

ARN ARN_filtrerCondition(ARN arn1, ARNElementEval);
ARN ARN_exfiltrerCondition(ARN arn1, ARNElementEval);



# endif
