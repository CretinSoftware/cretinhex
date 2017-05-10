
# ifndef __CRETINLIB_ABR_SOURCE__
# define __CRETINLIB_ABR_SOURCE__

# include <stdio.h>
# include <stdlib.h>
# include <assert.h>

# include "ABR.h"








typedef struct ABRCellule {
	struct ABRCellule * pere, * filsG, * filsD;
	ABRElement element;
	ABRElementFree free;
	char param;
} * ABRCellule;

struct ABR {
	ABRCellule racine;
	ABRElementEval eval;
	int taille;
};

struct ABRIterateur {
	ABR abr;
	ABRCellule curseur;
	char direction;
};




ABRCellule ABRCellule_init(ABRElement e, char param, ABRElementFree free, ABRCellule pere, int estFilsG){
	ABRCellule cellule = (ABRCellule) malloc(sizeof(struct ABRCellule));
	assert(cellule != NULL);
	
	cellule->element = e;
	cellule->param = param;
	cellule->free = free;
	cellule->pere = pere;
	cellule->filsG = NULL;
	cellule->filsD = NULL;
	
	/* Modification du père par effet de bord */
	if (pere != NULL){
		if (estFilsG)
			pere->filsG = cellule;
		else
			pere->filsD = cellule;
	}
	
	return cellule;
}

void ABRCellule_free(ABRCellule * c){
	if ((*c)->free != NULL)
		(*c)->free(&((*c)->element));
	free(*c);
	*c = NULL;
}

void ABRCellule_freeRecursif(ABRCellule * c){
	if ((*c)->filsG != NULL)  ABRCellule_freeRecursif(&((*c)->filsG));
	if ((*c)->filsD != NULL)  ABRCellule_freeRecursif(&((*c)->filsD));
	ABRCellule_free(c);
}

ABRCellule ABRCellule_dupliRecursif(ABRCellule c, ABRCellule pere, int estFilsG){
	ABRCellule c2 = NULL;
	if (c != NULL){
		c2 = ABRCellule_init(c->element, c->param, NULL, pere, estFilsG);
		c2->filsG = ABRCellule_dupliRecursif(c->filsG, c2, 1);
		c2->filsD = ABRCellule_dupliRecursif(c->filsD, c2, 0);
		/*printf("DupliRecursif : %4d (%4d, %4d, %4d) ->  %4d (%4d, %4d, %4d)\n", \
		       adresse(c), \
		       adresse(c->pere), \
		       adresse(c->filsG), \
		       adresse(c->filsD), \
		       adresse(c2), \
		       adresse(c2->pere), \
		       adresse(c2->filsG), \
		       adresse(c2->filsD));*/
	}
	return c2;
}


ABRCellule ABRCellule_rotationD(ABRCellule a){
	ABRCellule b = a->filsG;
	assert(b != NULL);
	
	b->pere = a->pere;
	if (a->pere != NULL){
		if (a->pere->filsG == a)  a->pere->filsG = b;
		else                      a->pere->filsD = b;
	}
	
	a->filsG = b->filsD;
	if (a->filsG != NULL) a->filsG->pere = a;
	
	b->filsD = a;
	a->pere = b;
	
	return b;
}


ABRCellule ABRCellule_rotationG(ABRCellule a){
	ABRCellule b = a->filsD;
	assert(b != NULL);
	
	b->pere = a->pere;
	if (a->pere != NULL){
		if (a->pere->filsG == a)  a->pere->filsG = b;
		else                      a->pere->filsD = b;
	}
	
	a->filsD = b->filsG;
	if (a->filsD != NULL) a->filsD->pere = a;
	
	b->filsG = a;
	a->pere = b;
	
	return b;
}






int ABRElement_adresse(ABRElement e){
	return (int) (unsigned long long int) e;
}



ABR ABR_init(ABRElementEval eval){
	ABR abr = (ABR) malloc(sizeof(struct ABR));
	assert(abr != NULL);
	
	abr->eval = eval;
	abr->racine = NULL;
	abr->taille = 0;
		
	return abr;
}

int ABR_taille(ABR abr){
	return abr->taille;
}


ABR ABR_inserer(ABR abr, ABRElement e, ABRElementFree free){
	++abr->taille;
	if (abr->racine == NULL){
		abr->racine = ABRCellule_init(e, 0, free, NULL, 0);
		return abr;
	}
	int cle = abr->eval(e);
	ABRCellule c = abr->racine;
	ABRCellule pere = NULL;
	while (c != NULL){
		pere = c;
		if (cle < abr->eval(c->element))    c = c->filsG;
		else                                c = c->filsD;
	}
	c = ABRCellule_init(e, 0, free, pere, cle < abr->eval(pere->element));
	return abr;
}


ABR ABR_insererSansDoublons(ABR abr, ABRElement e, ABRElementFree free){
	if (abr->racine == NULL){
		abr->racine = ABRCellule_init(e, 0, free, NULL, 0);
		++abr->taille;
		return abr;
	}
	int cle = abr->eval(e);
	ABRCellule c = abr->racine;
	ABRCellule pere = NULL;
	while (c != NULL){
		pere = c;
		if (cle == abr->eval(c->element))   return abr;
		if (cle < abr->eval(c->element))    c = c->filsG;
		else                                c = c->filsD;
	}
	++abr->taille;
	ABRCellule_init(e, 0, free, pere, cle < abr->eval(pere->element));
	return abr;
}
	
ABRCellule ABR_chercherCellule(ABR abr, ABRElement e){
	ABRCellule c = abr->racine;
	int cle = abr->eval(e);
	while (c != NULL && cle != abr->eval(c->element))
		if (cle < abr->eval(c->element))    c = c->filsG;
		else                                c = c->filsD;
	return c;
}

int ABR_chercher(ABR abr, ABRElement e){
	return ABR_chercherCellule(abr, e) != NULL;
}
		
ABR ABR_enlever(ABR abr, ABRElement e){
	ABRCellule c = ABR_chercherCellule(abr, e);
	if (c == NULL)
		return abr;
	
	/* Algo : on remonte le fils gauche et on greffe le fils droit à droite du sous-arbre gauche */
	ABRCellule cAux = c->filsG;
	if (c == abr->racine)       abr->racine = cAux;
	while (cAux->filsD != NULL) cAux = cAux->filsD;
	cAux->filsD = c->filsD;
	cAux->filsD->pere = cAux;
	ABRCellule_free(&c);
	
	--abr->taille;
	return abr;
}

ABR ABR_copier(ABR abr){
	ABR abr2 = ABR_init(abr->eval);
	abr2->racine = ABRCellule_dupliRecursif(abr->racine, NULL, 0);
	return abr2;
}
	
	
void ABR_free(ABR * abr){
	if ((*abr)->racine != NULL) ABRCellule_freeRecursif(&((*abr)->racine));
	free(*abr);
}








ABR ABR_fusion(ABR abr1, ABR abr2){
	ABRIterateur it = ABRIterateur_init(abr2);
	
	for (it = ABRIterateur_debut(it); ! ABRIterateur_fin(it); it = ABRIterateur_avancer(it)){
		abr1 = ABR_inserer(abr1, it->curseur->element, it->curseur->free);
		it->curseur->free = NULL;
	}
	ABR_free(&abr2);
	ABRIterateur_free(&it);
	return abr1;
}

ABR ABR_fusionSansDoublons(ABR abr1, ABR abr2){
	ABRIterateur it = ABRIterateur_init(abr2);
	
	for (it = ABRIterateur_debut(it); ! ABRIterateur_fin(it); it = ABRIterateur_avancer(it)){
		if (! ABR_chercher(abr1, it->curseur->element)){
			abr1 = ABR_insererSansDoublons(abr1, it->curseur->element, it->curseur->free);
			it->curseur->free = NULL;
		}
	}
	ABR_free(&abr2);
	ABRIterateur_free(&it);
	return abr1;
}













ABRIterateur ABRIterateur_init(ABR abr){
	ABRIterateur it = (ABRIterateur) malloc(sizeof(struct ABRIterateur));
	assert(it != NULL);
	it->abr = abr;
	return it;
}

ABRIterateur ABRIterateur_debut(ABRIterateur it){
	it->curseur = it->abr->racine;
	if (it->curseur != NULL){
		while (it->curseur->filsG != NULL)
			it->curseur = it->curseur->filsG;
		if (it->curseur->filsD != NULL)
			it->direction = 'D';
		else
			it->direction = 'P';
	}
	else
		it->direction = 'P';
	return it;
}
int ABRIterateur_fin(ABRIterateur it){
	return it->curseur == NULL;
}
ABRIterateur ABRIterateur_avancer(ABRIterateur it){
	ABRCellule f;
	switch (it->direction){
		case 'P' :
			do {
				f = it->curseur;
				it->curseur = it->curseur->pere;
			} while (it->curseur != NULL && f == it->curseur->filsD);
			if (it->curseur != NULL && it->curseur->filsD != NULL)
				it->direction = 'D';
			break;
		case 'D' :
			it->curseur = it->curseur->filsD;
			while (it->curseur->filsG != NULL)
				it->curseur = it->curseur->filsG;
			if (it->curseur->filsD == NULL)
				it->direction = 'P';
			break;
	}
	return it;
}

ABRElement ABRIterateur_valeur(ABRIterateur it){
	return it->curseur->element;
}

void ABRIterateur_free(ABRIterateur * it){
	free(*it);
}
				









# endif
