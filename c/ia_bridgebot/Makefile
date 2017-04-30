# MAKEFILE DE BridgeBot
# \author Pierre Pomeret-Coquot
# \version 0




# Paramètres communs
include ../../parametres/make.txt


# Tous les fichiers
FICHIERS_C   = $(wildcard *.c)




# Par défaut : tout !
all: $(foreach f, $(FICHIERS_C:.c=.o), $(DOS_O)/$(f))

# Dépendances
-include $(foreach f, $(FICHIERS_C:.c=.d), $(DOS_D)/$(f))





# Fichier(s) utilisant JNI
$(DOS_O)/bridgebotJNI.o: bridgebotJNI.c | $(DOS_O) $(DOS_D)
	$(CC) $(C_OPT) $(JNI_OPT) -c $< -o $@
	$(CC) -MM -MP $< -o $(DOS_D)/bridgebotJNI.d -MT $@ 
	
	
# Standard
$(DOS_O)/%.o: %.c | $(DOS_O) $(DOS_D)
	$(CC) $(C_OPT) -c $< -o $@
	$(CC) -MM -MP $< -o $(DOS_D)/$*.d -MT $@ 



# Dossiers manquants
$(DOS_O):
	mkdir $(DOS_O)

$(DOS_D):
	mkdir $(DOS_D)
	
	
	

# Nettoyage
clean:
	rm -fr $(DOS_O) $(DOS_D)
maxclean: clean

.PHONY: all clean maxclean



