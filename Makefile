# Makefile général.
# Fait plein de choses
#
# \author Pierre Pomeret-Coquot
# \version 3
# \date 30 mars 2017
#
# Différentes commandes :
#  - java        : compile le java
#  - c           : compile le c et place une copie de la bibliothèque dans JAVA_BIN/JAVA_SO_PATH
#  - doc         : crée la documentation avec doxygen
#  - raccourci   : crée un exécutable lançant le java en utilisant la bibliothèque
#
#
# 


# RÉGLAGES
include parametres/make.txt




# MAKES

all: c java raccourci

java: $(JAVA)/$(JAVA_APP)

c: $(foreach lib, $(TOUTES_LIB), $(C)/$(lib))

raccourci: $(EXE)

doc: javadoc cdoc
	rm -fr doc/html && doxygen $(PARAMS)/doxygen_all.txt
	echo '<!doctype html><html><meta http-equiv="refresh" content="0;URL=html/index.html"></html>' > doc/index.html





# L'application java
$(JAVA)/$(JAVA_APP): 
	make -C $(JAVA)

# La bibliothèque dans le dossier lib
$(JAVA)/$(JAVA_BIN)/lib%: $(C)/%
	cp $^ $@





# Compilation de la bibliothèque (.so)
$(C)/%: 
	make $* -C $(C)






# Génère le raccourci
$(EXE): $(JAVA)/$(JAVA_APP) $(foreach lib, $(TOUTES_LIB), $(JAVA)/$(JAVA_BIN)/lib$(lib))
	echo "(cd \"$(CURDIR)/$(JAVA)/$(JAVA_BIN)\" && java -Djava.library.path=./ $(JAVA_CLASS_APP) \$$@)" > $(EXE) && chmod 751 $(EXE)




# Doc java
javadoc: 
	make doc -C $(JAVA)

# Doc c
cdoc:
	make doc -C $(C)




# NETTOYAGE

doc-clean:
	rm -fr doc/html
	make $@ -C $(JAVA)
	make $@ -C $(C)
	
clean maxclean:
	make $@ -C $(JAVA)
	make $@ -C $(C)
	rm -fr $(EXE)

maxmaxclean: maxclean doc-clean
	rm -fr doc $(RACCOURCI_APP)
	rm -fr $(JAVA)/$(JAVA_BIN)/lib*.so

	

.PHONY: all java c raccourci doc javadoc cdoc clean maxclean maxmaxclean

