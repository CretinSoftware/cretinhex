# MAKEFILE DES TESTS

include ../../parametres/make.txt


# Séries de tests
SERIE_TESTS   = LDC ABR ARN Graphe GrapheHex Partie BridgeBot
SERIE_TESTS_MEMOIRE =  $(foreach t,$(SERIE_TESTS), $(t)_memoire)


# Dossiers
DOS_DONNEES   = fichiers_in
DOS_OUTPUT    = fichiers_out


MAINS   = $(subst .c,,$(wildcard main_*.c))
GENERE  = $(subst .c,,$(wildcard mk_*.c))


# Tout
all: $(MAINS) $(GENERE)


# Tests
tests: $(SERIE_TESTS)

memory_tests: tests_memoire
tests_memoire: $(SERIE_TESTS_MEMOIRE)

LDC LDC_memoire: main_LDC mk_n-uplets

ABR ABR_memoire: main_ABR mk_n-uplets

ARN ARN_memoire: main_ARN mk_n-uplets

Partie Partie_memoire: main_Partie mk_sauvegardes

Graphe Graphe_memoire: main_Graphe mk_fichier_graphe

GrapheHex GrapheHex_memoire: main_GrapheHex mk_sauvegardes

BridgeBot BridgeBot_memoire: main_BridgeBot mk_sauvegardes

$(SERIE_TESTS):
	-./script_test_$@.sh

$(SERIE_TESTS_MEMOIRE):
	-./script_test_$(subst _memoire,,$@).sh --valgrind
	
	

# Dépendances
-include $(foreach f, $(MAINS:.c=.d), $(DOS_D)/$(f).o)


# Mains
main_LDC:        $(foreach f, LDC , ../$(C_CRETINLIB)/$(DOS_O)/$(f).o) \
                 $(foreach f, tests main_LDC, $(DOS_O)/$(f).o)
	$(CC) $(C_OPT) $^ -o $@
	
main_ABR:        $(foreach f, LDC ABRPlus utile, ../$(C_CRETINLIB)/$(DOS_O)/$(f).o) \
                 $(foreach f, tests main_ABR, $(DOS_O)/$(f).o)
	$(CC) $(C_OPT) $^ -o $@
	
main_ARN:        $(foreach f, LDC ARNPlus utile, ../$(C_CRETINLIB)/$(DOS_O)/$(f).o) \
                 $(foreach f, tests main_ARN, $(DOS_O)/$(f).o)
	$(CC) $(C_OPT) $^ -o $@
	
	
main_Graphe:     $(foreach f, LDC Graphe utile, ../$(C_CRETINLIB)/$(DOS_O)/$(f).o) \
                 $(foreach f, tests main_Graphe, $(DOS_O)/$(f).o)
	$(CC) $(C_OPT) $^ -o $@
	
	
main_GrapheHex:  $(foreach f, LDC Graphe utile, ../$(C_CRETINLIB)/$(DOS_O)/$(f).o) \
                 $(foreach f, Joueur Damier GrapheHex GrapheHexPlus, ../$(C_HEX)/$(DOS_O)/$(f).o) \
                 $(foreach f, tests main_GrapheHex, $(DOS_O)/$(f).o)
	$(CC) $(C_OPT) $^ -o $@
	
	
main_Partie:     $(foreach f, LDC Graphe utile , ../$(C_CRETINLIB)/$(DOS_O)/$(f).o) \
                 $(foreach f, Joueur Damier GrapheHex Partie , ../$(C_HEX)/$(DOS_O)/$(f).o) \
                 $(foreach f, tests main_Partie, $(DOS_O)/$(f).o)
	$(CC) $(C_OPT) $^ -o $@
	
	
main_BridgeBot:  $(foreach f, LDC Graphe utile , ../$(C_CRETINLIB)/$(DOS_O)/$(f).o) \
                 $(foreach f, Joueur Damier GrapheHex GrapheHexPlus, ../$(C_HEX)/$(DOS_O)/$(f).o) \
                 $(foreach f, bridgebot, ../$(C_BRIDGEBOT)/$(DOS_O)/$(f).o) \
                 $(foreach f, tests main_BridgeBot, $(DOS_O)/$(f).o)
	$(CC) $(C_OPT) $^ -o $@
	
	
	





# Générateurs
mk_sauvegardes:  $(foreach f, LDC Graphe utile , ../$(C_CRETINLIB)/$(DOS_O)/$(f).o) \
                 $(foreach f, Joueur Damier GrapheHex Partie , ../$(C_HEX)/$(DOS_O)/$(f).o) \
                 $(foreach f, tests mk_sauvegardes, $(DOS_O)/$(f).o)
	$(CC) $(C_OPT) $^ -o $@

mk_%: mk_%.c $(DOS_O)/tests.o
	$(CC) $(C_OPT) $^ -o $@





# Fichiers à tester (externes)
../$(C_CRETINLIB)/$(DOS_O)/%.o: ../$(C_CRETINLIB)/%.c
	make $(DOS_O)/$*.o -C ../$(C_CRETINLIB)
	
../$(C_HEX)/$(DOS_O)/%.o: ../$(C_HEX)/%.c
	make $(DOS_O)/$*.o -C ../$(C_HEX)
	
../$(C_BRIDGEBOT)/$(DOS_O)/%.o: ../$(C_BRIDGEBOT)/%.c
	make $(DOS_O)/$*.o -C ../$(C_BRIDGEBOT)


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
	
