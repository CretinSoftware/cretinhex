#! /bin/bash


# Test de la LDC sur des NUplets d'entiers




function erreur(){ 
	case $1 in
		usage)
			echo "$0: usage: $0 [-v] [TAILLE_DONNEES [NB_TESTS [DIMENSIONS]]]" >&2
			echo "$0: usage: $0 -m fichier_donnees fichier_recherche taille_donnees dimension" >&2
			echo "$0: usage: $0 -f fichier1 fichier2 fichier_fusion" >&2
			echo "$0: usage: $0 -g fichier1 fichier2 fichier_fusionSansDoublons" >&2
			exit 2
			;;
		fichier)
			echo "$0: fichier: $2 inexistant, ou droit insuffisants" >&2
			exit 3
			;;
	esac
}




# Fabrique le fichier in de recherche
mk_f_rech(){
	test -f "$1" -a -r "$1" || erreur fichier "$1"
	test ! -f "$2" -o -w "$2" || erreur fichier "$2"
	
	f_donnees="$1"
	f_recherche="$2"
	taille=$3
	dim=$4
	
	
	echo -n "" > tmp
	echo -n "" > "$f_recherche"
	sleep 1
	./mk_n-uplets $dim $taille tmp
	
	
	
	while read ligne
	do
		echo "$ligne " >> "$f_recherche"
		grep "^$ligne " "$f_donnees" > /dev/null
		if test $? -eq 0
		then
			echo "true" >> "$f_recherche"
		else
			echo "false" >> "$f_recherche"
		fi
	done < tmp
	
	rm tmp
	
	return 0
	
}



verif_fusion(){
	f1="$1"
	f2="$2"
	ff="$3"
	
	cat $f1 $f2 > tmp
	cmp tmp $ff
	code=$?
	rm tmp
	exit $code
}



verif_fusionSansDoublons(){
	f1="$1"
	f2="$2"
	ff="$3"
	ok="oui"
	
	while read ligne
	do
		grep -e "$ligne" $ff > /dev/null
		test $? -ne 0 && ok=""
	done < $f1
	
	while read ligne
	do
		grep -e "$ligne" $ff > /dev/null
		test $? -ne 0 && ok=""
	done < $f2
	
	test ok && exit 0
	exit 1
}






# Répertoires
REP_IN=fichiers_in
REP_OUT=fichiers_out/LDC

# Nombre de n-uplets à traiter par défaut
TAILLE_DONNEES=1000

# Dimension des n-uplets
DIMENSIONS=1

# Nombre de tests pour une dimension donnée
NB_TESTS=1




use_valgrind=""

# Option : 1er parametre, shifté
if test $# -ge 1
then
	case $1 in 
		-v|--valgrind)
			use_valgrind="-v"
			shift
			;;
		-m)
			shift
			test $# -eq 4 || erreur usage
			test -f $1 -a -f $2 || mk_f_rech "$1" "$2" $3 $4
			exit $?
			;;
		-f)
			shift
			test $# -eq 3 || erreur usage
			verif_fusion "$1" "$2" "$3"
			exit $?
			;;
		-g)
			shift
			test $# -eq 3 || erreur usage
			verif_fusionSansDoublons "$1" "$2" "$3"
			exit $?
			;;
	esac
fi


# 1er argument : taille de données
if test $# -ge 1
then
	expr $1 + 1 > /dev/null
	test $? -le 1 || erreur usage
	TAILLE_DONNEES=$1
fi 

# 2eme argument : nombre de tests
if test $# -ge 2
then
	expr $2 + 1 > /dev/null
	test $? -le 1 || erreur usage
	NB_TESTS=$2
fi 


# 3eme argument : dimensions à tester (sous forme d'une chaîne "1 3 7")
if test $# -ge 3
then
	DIMENSIONS=$3
fi 

# Plus d'arguments : erreur
test $# -ge 4 && erreur usage





# On vide le répertoire $REP_OUT
rm -fr $REP_OUT
mkdir -p $REP_IN
mkdir -p $REP_OUT









# On crée la boucle pour les tests identiques
bcl=""
i=0
while test $i -lt $NB_TESTS
do
	bcl="$bcl $i"
	i=`expr $i + 1`
done




# On lance les séries de tests

ko=0



# Construction / insertion 
# -------------------------------------

# Pattern du fichier en entree
f_in="$REP_IN/n-uplets_@1x${TAILLE_DONNEES}_@2.txt"

# Pattern du fichier en sortie
f_out="$REP_OUT/`basename $f_in`"

# Pattern de la commande pour créer le fichier en entrée
mk_f_in="./mk_n-uplets @1 $TAILLE_DONNEES $f_in"

# Pattern de la commande de test
commande="./main_LDC -c @1 $TAILLE_DONNEES $f_in"

# Pattern de la commande de vérification
verif="cmp $f_in $f_out" 


./exec_serie_tests.sh $use_valgrind "$f_in" "$mk_f_in" "" "" "$f_out" "$commande" "$verif" "$DIMENSIONS" "$bcl"

test $? -eq 0 || ko=`expr $ko + 1`



# Duplication
# -------------------------------------

# Pattern du fichier en entree
f_in="$REP_IN/n-uplets_@1x${TAILLE_DONNEES}_@2.txt"

# Pattern du fichier en sortie
f_out="$REP_OUT/`basename $f_in`"

# Pattern de la commande pour créer le fichier en entrée
mk_f_in="./mk_n-uplets @1 $TAILLE_DONNEES $f_in"

# Pattern de la commande de test
commande="./main_LDC -d @1 $TAILLE_DONNEES $f_in"

# Pattern de la commande de vérification
verif="cmp $f_in $f_out" 


./exec_serie_tests.sh $use_valgrind "$f_in" "$mk_f_in" "" "" "$f_out" "$commande" "$verif" "$DIMENSIONS" "$bcl"

test $? -eq 0 || ko=`expr $ko + 1`




# Fusion
# -------------------------------------

# Pattern des fichiers en entree
f_in="$REP_IN/n-uplets_fusion_@1x${TAILLE_DONNEES}_@2_a.txt"
f_in2="$REP_IN/n-uplets_fusion_@1x${TAILLE_DONNEES}_@2_b.txt"

# Pattern du fichier en sortie
f_out="$REP_OUT/n-uplets_fusion_@1x${TAILLE_DONNEES}_@2.txt"

# Pattern des commandes pour créer les fichiers en entrée
mk_f_in="./mk_n-uplets @1 $TAILLE_DONNEES $f_in"
mk_f_in2="./mk_n-uplets @1 $TAILLE_DONNEES $f_in2"

# Pattern de la commande de test
commande="./main_LDC -f @1 $TAILLE_DONNEES $f_in $f_in2"

# Pattern de la commande de vérification
verif="$0 -f $f_in $f_in2 $f_out" 


./exec_serie_tests.sh $use_valgrind "$f_in" "$mk_f_in" "$f_in2" "$mk_f_in2" "$f_out" "$commande" "$verif" "$DIMENSIONS" "$bcl"

test $? -eq 0 || ko=`expr $ko + 1`




# Fusion sans doublons
# -------------------------------------

# Pattern de la commande de test
commande="./main_LDC -g @1 $TAILLE_DONNEES $f_in $f_in2"

# Pattern de la commande de vérification
verif="$0 -g $f_in $f_in2 $f_out"


./exec_serie_tests.sh $use_valgrind "$f_in" "$mk_f_in" "$f_in2" "$mk_f_in2" "$f_out" "$commande" "$verif" "$DIMENSIONS" "$bcl"
test $? -eq 0 || exit 1






# Recherche
# -------------------------------------

f_in2="$REP_IN/n-uplets_@1x${TAILLE_DONNEES}_@2.txt"
mk_f_in2=""

f_in="$REP_IN/n-uplets_@1x${TAILLE_DONNEES}_recherche_@2.txt"
f_out="$REP_OUT/`basename $f_in`"

mk_f_in="$0 -m $f_in2 $f_in $TAILLE_DONNEES @1"
#mk_f_in2="./mk_n-uplets @1 $TAILLE_DONNEES $f_in2"

commande="./main_LDC -r @1 $TAILLE_DONNEES $f_in $f_in2"
verif="cmp $f_in $f_out" 

./exec_serie_tests.sh $use_valgrind "$f_in" "$mk_f_in" "$f_in2" "$mk_f_in2" "$f_out" "$commande" "$verif" "$DIMENSIONS" "$bcl"

test $? -eq 0 || ko=`expr $ko + 1`







exit $ko




