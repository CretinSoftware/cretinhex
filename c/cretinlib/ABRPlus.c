


# include <stdio.h>
# include <stdlib.h>
# include <assert.h>

# include "ABRPlus.h"

/* On inclut le .c pour travailler "à la suite" */
# include "ABR.c"


/** Copie récursivement les valeurs dans la ldc (infixe) */
void ABR_listerRecursif(ABRCellule c, LDC * ldc){
	if (c != NULL){
		ABR_listerRecursif(c->filsG, ldc);
		*ldc = LDC_inserer(*ldc, -1, c->element, NULL);
		ABR_listerRecursif(c->filsD, ldc);
	}
}

LDC ABR_lister(ABR abr){
	LDC ldc = LDC_init();
	ABR_listerRecursif(abr->racine, &ldc);
	return ldc;
}






