# MAKEFILE DES TESTS

include ../../parametres/make.txt


# Séries de tests
SERIE_TESTS   = LDC Graphe GrapheHex Partie
SERIE_TESTS_MEMOIRE =  $(foreach t,$(SERIE_TESTS), $(t)_memoire)


# Dossiers
DOS_DONNEES   = fichiers_in
DOS_OUTPUT    = fichiers_out
DOS_CRETINLIB = ../$(C_CRETINLIB)
DOS_HEX       = ../$(C_HEX)


MAINS   = $(subst .c,,$(wildcard main_*.c))
GENERE  = $(subst .c,,$(wildcard mk_*.c))


# Tout
all: $(MAINS) $(GENERE)


# Tests
tests: $(SERIE_TESTS)

memory_tests: tests_memoire
tests_memoire: $(SERIE_TESTS_MEMOIRE)

LDC LDC_memoire: main_LDC mk_n-uplets

Partie Partie_memoire: main_Partie mk_sauvegardes

Graphe Graphe_memoire: main_Graphe mk_fichier_graphe

GrapheHex GrapheHex_memoire: main_GrapheHex mk_sauvegardes

$(SERIE_TESTS):
	-./script_test_$@.sh

$(SERIE_TESTS_MEMOIRE):
	-./script_test_$(subst _memoire,,$@).sh --valgrind
	
	

# Dépendances
-include $(foreach f, $(MAINS:.c=.d), $(DOS_D)/$(f))


# Mains
main_LDC:        $(foreach f, LDC.o , $(DOS_CRETINLIB)/$(DOS_O)/$(f)) \
                 $(foreach f, tests.o main_LDC.o, $(DOS_O)/$(f))
	$(CC) $(C_OPT) $^ -o $@
	
	
main_Graphe:     $(foreach f, LDC.o Graphe.o utile.o, $(DOS_CRETINLIB)/$(DOS_O)/$(f)) \
                 $(foreach f, tests.o main_Graphe.o, $(DOS_O)/$(f))
	$(CC) $(C_OPT) $^ -o $@
	
	
main_GrapheHex:  $(foreach f, LDC.o Graphe.o utile.o, $(DOS_CRETINLIB)/$(DOS_O)/$(f)) \
                 $(foreach f, Joueur.o Damier.o GrapheHex.o, $(DOS_HEX)/$(DOS_O)/$(f)) \
                 $(foreach f, tests.o main_GrapheHex.o, $(DOS_O)/$(f))
	$(CC) $(C_OPT) $^ -o $@
	
	
main_Partie:     $(foreach f, LDC.o Graphe.o utile.o , $(DOS_CRETINLIB)/$(DOS_O)/$(f)) \
                 $(foreach f, Joueur.o Damier.o GrapheHex.o Partie.o , $(DOS_HEX)/$(DOS_O)/$(f)) \
                 $(foreach f, tests.o main_Partie.o, $(DOS_O)/$(f))
	$(CC) $(C_OPT) $^ -o $@
	
	
	





# Générateurs
mk_sauvegardes:  $(foreach f, LDC.o Graphe.o utile.o , $(DOS_CRETINLIB)/$(DOS_O)/$(f)) \
                 $(foreach f, Joueur.o Damier.o GrapheHex.o Partie.o , $(DOS_HEX)/$(DOS_O)/$(f)) \
                 $(foreach f, tests.o mk_sauvegardes.o, $(DOS_O)/$(f))
	$(CC) $(C_OPT) $^ -o $@

mk_%: mk_%.c $(DOS_O)/tests.o
	$(CC) $(C_OPT) $^ -o $@





# Fichiers à tester (externes)
$(DOS_CRETINLIB)/$(DOS_O)/%.o: $(DOS_CRETINLIB)/%.c
	make $(DOS_O)/$*.o -C $(DOS_CRETINLIB)
	
$(DOS_HEX)/$(DOS_O)/%.o: $(DOS_HEX)/%.c
	make $(DOS_O)/$*.o -C $(DOS_HEX)


# Fichiers de tests (internes)
$(DOS_O)/%.o: %.c | $(DOS_O) $(DOS_D)
	$(CC) $(C_OPT) -c $< -o $@
	$(CC) -MM -MP $< -o $(DOS_D)/$*.d -MT $@ 
	

# Dossiers
$(DOS_O):
	mkdir $(DOS_O) 
	
$(DOS_D):
	mkdir $(DOS_D)






clean:
	rm -fr $(DOS_O) $(DOS_D)

maxclean: clean 
	rm -fr $(DOS_DONNEES)
	rm -fr $(DOS_OUTPUT)
	rm -f $(MAINS)
	rm -f $(GENERE)


.PHONY: all tests $(SERIE_TESTS) tests_memoire $(SERIE_TESTS_MEMOIRE) clean maxclean
	
