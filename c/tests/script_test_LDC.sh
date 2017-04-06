#! /bin/bash


# Test de la LDC sur des NUplets d'entiers




function erreur(){ 
	case $1 in
		usage)
			echo "$0: usage: [-v] $0 [TAILLE_DONNEES [NB_TESTS [DIMENSIONS]]]" >&2
			exit 2
			;;
	esac
}








# Répertoires
REP_IN=fichiers_in
REP_OUT=fichiers_out/LDC

# Nombre de n-uplets à traiter par défaut
TAILLE_DONNEES=1000

# Dimension des n-uplets
DIMENSIONS="1 3 5 7 9"

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






# Pattern du fichier en entree
f_in="$REP_IN/n-uplets_@1x${TAILLE_DONNEES}_@2.txt"

# Pattern du fichier en sortie
f_out="$REP_OUT/`basename $f_in`"

# Pattern de la commande pour créer le fichier en entrée
mk_f_in="./mk_n-uplets @1 $TAILLE_DONNEES $f_in"

# Pattern de la commande de test
commande="./main_LDC -c @1 $TAILLE_DONNEES $f_in"




# On crée la boucle pour les tests identiques
bcl=""
i=0
while test $i -lt $NB_TESTS
do
	bcl="$bcl $i"
	i=`expr $i + 1`
done




# On lance la série de tests
./exec_serie_tests.sh $use_valgrind "$f_in" "$mk_f_in" "$f_out" "$commande" "$DIMENSIONS" "$bcl"

#exit $?






