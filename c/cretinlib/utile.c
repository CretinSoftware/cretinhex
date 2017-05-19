# include "utile.h"
# include <stdio.h>
# include <stdlib.h>



int adresse(void * truc){
	return (int) TYPE_ADRESSE truc % 10000;
}

int adresseComplete(void * truc){
	return (int) TYPE_ADRESSE truc;
}
