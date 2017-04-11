# Makefile de la bibliothèque
# Compile tout le c pour produire la bibliothèque C_SO
# Fait la doc du c
#
# \author Pierre Pomeret-Coquot
# \version 3
# \date 30 mars 2017
#
# Différentes commandes :
#  - c           : compile le c -> .so
#  - headers     : crée le fichier .h avec javah
#  - doc         : crée la documentation avec doxygen
#
#
# 





# Réglages 
include ../parametres/make.txt

C_SRC                = $(C_CRETINLIB) $(C_HEX)
C_DOC                = ../$(DOC)/c
C_FICHIERS_C        := $(foreach dos, $(C_SRC), $(wildcard $(dos)/*.c))
C_FICHIERS_O        := $(foreach dos, $(C_SRC), $(patsubst $(dos)/%.c,$(dos)/$(DOS_O)/%.o,$(wildcard $(dos)/*.c)))




# MAKES

all: c 

headers: 
	make headers -C ../$(JAVA)

c: $(LIB_CRETINHEX)

doc: $(C_DOC)/html/index.html







# Bibliothèque cretinhex
$(LIB_CRETINHEX_SO): $(C_FICHIERS_O)
	echo $^
	gcc -shared $(C_OPT) $(C_FICHIERS_O) -o $(LIB_CRETINHEX_SO)
	
$(LIB_CRETINHEX_DLL): 
	@echo "Pas de compilation pour windows actuellement"


# Appelle les makes pour fournir les .o
%.o: 
#	make $(C_OBJ)/$(notdir $@) -C $(subst $(C_OBJ)/,,$(dir $@))
	make -C $(subst $(DOS_O)/,,$(dir $@))











# Doc c
$(C_DOC)/html/index.html: $(C_SO)
	rm -fr $(C_DOC)
	mkdir -p $(C_DOC)
	doxygen ../$(PARAMS)/doxygen_c.txt




# NETTOYAGE

# Efface les fichiers objets
clean: 
	@$(foreach dos, $(C_TOUT), make clean -C $(dos); )
	
# Efface la doc
doc-clean:
	rm -fr $(C_DOC)/html

# Efface tout ce qui peut être regénéré
maxclean: 
	@$(foreach dos, $(C_TOUT), make maxclean -C $(dos); )
	rm -f $(LIB_CRETINHEX)
	
	

.PHONY: all c headers header doc clean maxclean

