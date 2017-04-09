
# ifndef __TESTS__
# define __TESTS__

# define DONNEES_TESTS "fichiers_in"
# define INPUTS DONNEES_TESTS
# define OUTPUTS "fichiers_out"


# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <assert.h>



void erreur(const char * str, int CE);
void erreurUnix(const char * str, int CE);


/* int */
int int_egal(int * a, int * b);

/* n-uplet */
typedef struct s_NUplet * NUplet;
NUplet NUplet_init(int dimension);
int NUplet_dimension(NUplet nuplet);
NUplet NUplet_set(NUplet nuplet, int position, int valeur);
int NUplet_get(NUplet nuplet, int position);
void NUplet_libererMemoire(NUplet * nuplet);
void NUplet_afficher(NUplet nuplet);
int NUplet_egal(NUplet nu1, NUplet nu2);

# endif
