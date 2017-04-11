# include "utile.h"
# include <stdio.h>
# include <stdlib.h>



int adresse(void * truc){
	return (int) (unsigned long int) truc % 10000;
}
