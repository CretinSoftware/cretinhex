# MAKEFILE DE CRETINLIB
# \author Pierre Pomeret-Coquot
# \version 1.2


include ../../parametres/make.txt



# Tous les fichiers
FICHIERS_C = $(wildcard *.c)




# Tout
all: selon_archi $(foreach f, $(FICHIERS_C:.c=.o), $(DOS_O)/$(f))

# Dépendances
-include $(foreach f, $(FICHIERS_C:.c=.d), $(DOS_D)/$(f))




# .o standard
$(DOS_O)/%.o: %.c | $(DOS_O) $(DOS_D)
	$(CC) $(C_OPT) -c $< -o $@
	$(CC) -MM -MP $< -o $(DOS_D)/$*.d -MT $@ 


# Dossiers
$(DOS_O):
	mkdir $(DOS_O)

$(DOS_D):
	mkdir $(DOS_D)
	
selon_archi:
	cp utile_$(ARCHITECTURE).h utile.h


	

# Nettoyage
clean:
	rm -fr $(DOS_O) $(DOS_D)
maxclean: clean

.PHONY: selon_archi all clean maxclean


