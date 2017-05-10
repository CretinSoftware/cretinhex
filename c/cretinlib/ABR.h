

# ifndef __CRETINLIB_ABR__
# define __CRETINLIB_ABR__


# include "utile.h"



typedef void * ABRElement;                              /**< Pointeur vers un truc externe, pour être contenu dans un ABRElement */
typedef void (*ABRElementFree)(ABRElement *);           /**< Callback pour libérer la mémoire allouée à un ABRElement par un script externe */
typedef int (*ABRElementEgal)(ABRElement, ABRElement);  /**< Egalité entre deux éléments */
typedef int (*ABRElementEval)(ABRElement);              /**< Fonction attribuant une valeur entière à un noeud d'ABR */

int ABRElement_adresse(ABRElement e);                   /**< Fonction attribuant l'adresse d'un élément comme valeur */

typedef struct ABR * ABR;


ABR ABR_init(ABRElementEval eval);
int ABR_taille(ABR abr);
ABR ABR_inserer(ABR abr, ABRElement e, ABRElementFree free);
ABR ABR_insererSansDoublons(ABR abr, ABRElement e, ABRElementFree free);
int ABR_chercher(ABR abr, ABRElement e);
ABR ABR_enlever(ABR abr, ABRElement e);
ABR ABR_copier(ABR abr);
void ABR_free(ABR * abr);

ABR ABR_fusion(ABR abr1, ABR abr2);
ABR ABR_fusionSansDoublons(ABR abr1, ABR abr2);




typedef struct ABRIterateur * ABRIterateur;

ABRIterateur ABRIterateur_init(ABR abr);
ABRIterateur ABRIterateur_debut(ABRIterateur it);
int ABRIterateur_fin(ABRIterateur it);
ABRIterateur ABRIterateur_avancer(ABRIterateur it);
ABRElement ABRIterateur_valeur(ABRIterateur it);
void ABRIterateur_free(ABRIterateur * it);
			
			







# endif
