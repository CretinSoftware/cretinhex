#! /bin/bash


# Test de la Partie sur le chargement / sauvegarde





function erreur(){ 
	case $1 in
		usage)
			echo "$0: usage: [-v] $0 [TAILLE [NB_COUPS [NB_TESTS]]]" >&2
			exit 2
			;;
	esac
}








# Répertoires
REP_IN=fichiers_in
REP_OUT=fichiers_out/Partie

# Dimension des grilles
DIMENSIONS="10 20"

# Nombre de coups joués
NB_COUPS_JOUES="100"

# Nombre de tests pour chacun de ces réglages
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


# 1er argument : taille
if test $# -ge 1
then
	DIMENSIONS=$1
fi 


# 2eme argument : NB_COUPS
if test $# -ge 2
then
	NB_COUPS_JOUES=$2
fi 


# 3eme argument : NB_TESTS
if test $# -ge 3
then
	expr $3 + 1 > /dev/null 2>&1
	test $? -le 1 || erreur usage
	NB_TESTS=$3
fi 

# Plus d'arguments : erreur
test $# -ge 4 && erreur usage


# On vide le répertoire $REP_OUT
rm -fr $REP_OUT
mkdir -p $REP_IN
mkdir -p $REP_OUT







# Pattern du fichier en entree
f_in="$REP_IN/sauv_@1x@2_@3.txt"

# Pattern du fichier en sortie
f_out="$REP_OUT/sauvegarde_@1x@2_@3.txt"

# Pattern de la commande pour créer le fichier en entrée
random_number=`cat /dev/urandom | tr -dc "0-9" | head -c 10`
mk_f_in="./mk_sauvegardes @1 `expr $random_number % 2 + 1` @2 $f_in"

# Pattern de la commande de test
commande="./main_Partie -s $f_in $f_out"

# Pattern de la commande de vérification
verif="cmp $f_in $f_out" 


ko=0


# On crée la boucle pour les tests identiques
bcl=""
i=0
while test $i -lt $NB_TESTS
do
	bcl="$bcl $i"
	i=`expr $i + 1`
done



# On limite la boucle du nombre de coups joues
for largeur in $DIMENSIONS
do
	bcl2=""
	for nb_coups in $NB_COUPS_JOUES
	do
		test $nb_coups -le `expr $largeur \* $largeur` && bcl2="$bcl2 $nb_coups"
	done
	
	# On lance la série de tests
	./exec_serie_tests.sh $use_valgrind "$f_in" "$mk_f_in" "" "" "$f_out" "$commande" "$verif" "$largeur" "$bcl2" "$bcl"
done

exit $ko






