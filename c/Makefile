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
C_FICHIERS_O        := $(foreach dos, $(C_SRC), $(patsubst $(dos)/%.c,$(dos)/$(DOS_O)/%.o,$(wildcard $(dos)/*.c))) \
                       $(foreach dos, $(C_SRC), $(wildcard $(dos)/$(DOS_O)/*.o))




# MAKES

all: c 

headers: 
	make headers -C ../$(JAVA)

c: $(TOUTES_LIB)

doc: $(C_DOC)/html/index.html







# Bibliothèque cretinhex
$(LIB_CRETINHEX_SO): $(foreach f, LDC Graphe utile, $(C_CRETINLIB)/$(DOS_O)/$(f).o) \
                     $(foreach f, Joueur Damier GrapheHex Partie PartieJNI, $(C_HEX)/$(DOS_O)/$(f).o)
	gcc -shared $(C_OPT) $^ -o $@
	
$(LIB_IA0_SO):  $(patsubst $(C_IA0)/%.c, $(C_IA0)/$(DOS_O)/%.o, $(wildcard $(C_IA0)/*.c))
	gcc -shared $(C_OPT) $^ -o $@
	
$(LIB_BRIDGEBOT_SO): $(foreach f, LDC ARNPlus Graphe utile, $(C_CRETINLIB)/$(DOS_O)/$(f).o) \
                     $(foreach f, Joueur Damier GrapheHex GrapheHexPlus, $(C_HEX)/$(DOS_O)/$(f).o) \
                     $(foreach f, bridgebot bridgebotJNI, $(C_BRIDGEBOT)/$(DOS_O)/$(f).o)
	gcc -shared $(C_OPT) $^ -o $@
	
$(LIB_GOTOONEBOT_SO): $(foreach f, LDC Graphe utile, $(C_CRETINLIB)/$(DOS_O)/$(f).o) \
                      $(foreach f, Joueur Damier GrapheHex Minimax, $(C_HEX)/$(DOS_O)/$(f).o) \
                      $(foreach f, gotoonebot gotoonebotJNI, $(C_GOTOONEBOT)/$(DOS_O)/$(f).o)
	gcc -shared $(C_OPT) $^ -o $@
	
	

# Windows : le fera-t'on ?
%.dll: 
	@echo "Pas de compilation pour windows actuellement"
	
	
	
	
# Appelle les makes pour fournir les .o
%.o: 
#	make $(DOS_O)/$(notdir $@) -C $(subst $(DOS_O)/,,$(dir $@))
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
	rm -f *.so *.dll
	
	

.PHONY: all c headers header doc clean maxclean

