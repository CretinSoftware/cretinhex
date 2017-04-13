# Makefile du java
# Compile le java et fait la doc du java aussi, ainsi que les headers pour JNI
#
# \author Pierre Pomeret-Coquot
# \version 3
# \date 30 mars 2017
#
# Différentes commandes :
#  - java        : compile le java
#  - headers     : crée le fichier .h avec javah
#  - doc         : crée la documentation avec doxygen
#
#
# 


# RÉGLAGES

include ../parametres/make.txt


FICHIERS_JAVA        = $(wildcard $(JAVA_SRC)/*/*.java $(JAVA_SRC)/ihm/*/*.java)
JAVA_DOC             = ../$(DOC)/java



# MAKES
all: $(JAVA_APP)
headers: header_PartieJNI header_IA0
doc: $(JAVA_DOC)/html/index.html





# Compilation
$(JAVA_APP): $(FICHIERS_JAVA) | $(JAVA_BIN)
	javac -sourcepath $(JAVA_SRC) -d $(JAVA_BIN) $(JAVA_SRC)/*/*.java





# Crée le header des bibliothèques natives (c)
header_PartieJNI:
	rm -f ../$(C)/$(C_HEADER_PARTIEJNI)
	javah  -sourcepath $(JAVA_SRC) -o ../$(C)/$(C_HEADER_PARTIEJNI) $(JAVA_CLASS_PARTIEJNI)
	
header_IA0:
	rm -f ../$(C)/$(C_HEADER_IA0)
	javah  -sourcepath $(JAVA_SRC) -o ../$(C)/$(C_HEADER_IA0) $(JAVA_CLASS_IA0)




# Dossiers
$(JAVA_BIN):
	mkdir -p $(JAVA_BIN)






# DOCUMENTATION

javadoc: $(JAVA_DOC)/html/index.html

$(JAVA_DOC)/html/index.html: 
	rm -fr $(JAVA_DOC)
	mkdir -p $(JAVA_DOC)
	doxygen ../$(PARAMS)/doxygen_java.txt




# Nettoyage
clean:
	rm -fr $(JAVA_BIN)

doc-clean:
	rm -fr $(JAVA_DOC)/html

maxclean: clean	


.PHONY: all java doc javadoc headers header_PartieJNI header_IA0 clean maxclean maxmaxclean

