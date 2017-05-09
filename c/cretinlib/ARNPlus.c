


# include <stdio.h>
# include <stdlib.h>
# include <assert.h>


/* On inclut les .c pour travailler "à la suite" */
# include "ARN.c"
# include "ABRPlus.c"


LDC ARN_lister(ARN arn){
	return ABR_lister(arn);
}


ARN ARN_fromLDC(LDC ldc, ARNElementEval eval){
	ARN arn = ARN_init(eval);
	LDCIterateur it = LDCIterateur_init(ldc, LDCITERATEUR_AVANT);
	for (it = LDCIterateur_debut(it); ! LDCIterateur_fin(it); it = LDCIterateur_avancer(it))
		arn = ARN_inserer(arn, LDCIterateur_valeur(it), NULL);
	return arn;
}


ARN ARN_fromLDCSansDoublons(LDC ldc, ARNElementEval eval){
	ARN arn = ARN_init(eval);
	LDCIterateur it = LDCIterateur_init(ldc, LDCITERATEUR_AVANT);
	for (it = LDCIterateur_debut(it); ! LDCIterateur_fin(it); it = LDCIterateur_avancer(it))
		arn = ARN_insererSansDoublons(arn, LDCIterateur_valeur(it), NULL);
	return arn;
}


ARN ARN_insererLDC(ARN arn, LDC ldc){
	LDCIterateur it = LDCIterateur_init(ldc, LDCITERATEUR_AVANT);
	for (it = LDCIterateur_debut(it); ! LDCIterateur_fin(it); it = LDCIterateur_avancer(it))
		arn = ARN_inserer(arn, LDCIterateur_valeur(it), NULL);
	return arn;
}


ARN ARN_insererLDCSansDoublons(ARN arn, LDC ldc){
	LDCIterateur it = LDCIterateur_init(ldc, LDCITERATEUR_AVANT);
	for (it = LDCIterateur_debut(it); ! LDCIterateur_fin(it); it = LDCIterateur_avancer(it))
		arn = ARN_insererSansDoublons(arn, LDCIterateur_valeur(it), NULL);
	return arn;
}


