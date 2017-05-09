

# include "ARN.h"
# include "ABR.c"










ARN ARN_equilibrer(ARN arn, ABRCellule c){
	assert(c->param == 'R');
	if (c->pere == NULL){
		c->param = 'N';
		return arn;
	}
	if (c->pere->param == 'N'){
		return arn;
	}
	assert(c->pere != NULL);
	assert(c->pere->param == 'R');
	assert(c->pere->pere != NULL);
	/* Ici on a un père rouge et un grand-père noir (la racine ne peut pas être rouge) */
	ABRCellule p  = c->pere;
	ABRCellule gp = p->pere;
	ABRCellule o  = gp->filsG;
	if (p == o) o = gp->filsD;
	
	if (o != NULL && o->param == 'R'){
		o->param = 'N';
		p->param = 'N';
		gp->param= 'R';
		return ARN_equilibrer(arn, gp);
	}
	
	/* Le cas de l'oncle noir... Rotations, et attention à la racine :-) */
	/* 1. GG -> rotation D */
	if (c == p->filsG && p == gp->filsG){
		ABRCellule_rotationD(gp);
		p->param = 'N';
		gp->param = 'R';
		if (arn->racine == gp) arn->racine = p;
		return arn;
	}
	/* 1b. DD -> rotation G */
	if (c == p->filsD && p == gp->filsD){
		ABRCellule_rotationG(gp);
		p->param = 'N';
		gp->param = 'R';
		if (arn->racine == gp) arn->racine = p;
		return arn;
	}
	/* 2. GD -> rotation D */
	if (c == p->filsD && p == gp->filsG){
		ABRCellule_rotationG(p);
		return ARN_equilibrer(arn, p);
	}
	
	/* 2b. DG -> rotation G */
	if (c == p->filsG && p == gp->filsD){
		ABRCellule_rotationD(p);
		return ARN_equilibrer(arn, p);
	}
	
	return NULL;
}
	
	
	


/* Ca ressemble un peu à de l'héritage... */


ARN ARN_init(ARNElementEval eval){
	return (ARN) ABR_init(eval);
}

/* Sucharge */
ARN ARN_inserer(ARN arn, ARNElement e, ARNElementFree free){
	ABRCellule celluleInseree;
	
	if (arn->racine == NULL){
		arn->racine = ABRCellule_init(e, 'N', free, NULL, 0);
		return arn;
	}
	int cle = arn->eval(e);
	ABRCellule c = arn->racine;
	ABRCellule pere = NULL;
	while (c != NULL){
		pere = c;
		if (cle < arn->eval(c->element))    c = c->filsG;
		else                                c = c->filsD;
	}
	
	celluleInseree = ABRCellule_init(e, 'R', free, pere, cle < arn->eval(pere->element));

	arn = ARN_equilibrer(arn, celluleInseree);
	return arn;
}

/* Sucharge */
ARN ARN_insererSansDoublons(ARN arn, ARNElement e, ARNElementFree free){
	ABRCellule celluleInseree;
	
	if (arn->racine == NULL){
		arn->racine = ABRCellule_init(e, 'N', free, NULL, 0);
		return arn;
	}
	int cle = arn->eval(e);
	ABRCellule c = arn->racine;
	ABRCellule pere = NULL;
	while (c != NULL){
		pere = c;
		if (cle == arn->eval(c->element))   return arn;
		if (cle < arn->eval(c->element))    c = c->filsG;
		else                                c = c->filsD;
	}
	
	celluleInseree = ABRCellule_init(e, 'R', free, pere, cle < arn->eval(pere->element));

	arn = ARN_equilibrer(arn, celluleInseree);
	return arn;
}
	
	

int ARN_chercher(ARN arn, ARNElement e){
	return ABR_chercher(arn, e);
}

ARN ARN_enlever(ARN arn, ARNElement e){
	return (ARN) ABR_enlever(arn, e);
}

ARN ARN_copier(ARN arn){
	return (ARN) ABR_copier(arn);
}

void ARN_free(ARN * arn){
	ABR_free(arn);
}








ARN ARN_fusion(ARN arn1, ARN arn2){
	ABRIterateur it = ABRIterateur_init(arn2);
	
	for (it = ABRIterateur_debut(it); ! ABRIterateur_fin(it); it = ABRIterateur_avancer(it)){
		arn1 = ARN_inserer(arn1, it->curseur->element, it->curseur->free);
		it->curseur->free = NULL;
	}
	ARN_free(&arn2);
	ABRIterateur_free(&it);
	return arn1;
}

ARN ARN_fusionSansDoublons(ARN arn1, ARN arn2){
	ABRIterateur it = ABRIterateur_init(arn2);
	
	for (it = ABRIterateur_debut(it); ! ABRIterateur_fin(it); it = ABRIterateur_avancer(it)){
		if (! ARN_chercher(arn1, it->curseur->element)){
			arn1 = ARN_insererSansDoublons(arn1, it->curseur->element, it->curseur->free);
			it->curseur->free = NULL;
		}
	}
	ARN_free(&arn2);
	ABRIterateur_free(&it);
	return arn1;
}



ARN ARN_filtrer(ARN arn1, ARN arn2, ARNElementEgal filtre){
	ARN resultat = ARN_init(arn1->eval);
	ABRIterateur it = ABRIterateur_init(arn1);
	for (it = ABRIterateur_debut(it); ! ABRIterateur_fin(it); it = ABRIterateur_avancer(it))
		if (ARN_chercher(arn2, ABRIterateur_valeur(it)))
			resultat = ARN_inserer(resultat, ABRIterateur_valeur(it), NULL);
	ABRIterateur_free(&it);
	return resultat;
}


ARN ARN_exfiltrer(ARN arn1, ARN arn2, ARNElementEgal filtre){
	ARN resultat = ARN_init(arn1->eval);
	ABRIterateur it = ABRIterateur_init(arn1);
	for (it = ABRIterateur_debut(it); ! ABRIterateur_fin(it); it = ABRIterateur_avancer(it))
		if (! ARN_chercher(arn2, ABRIterateur_valeur(it)))
			resultat = ARN_inserer(resultat, ABRIterateur_valeur(it), NULL);
	ABRIterateur_free(&it);
	return resultat;
}
















