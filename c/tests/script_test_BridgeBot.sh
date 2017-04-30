#! /bin/bash


# Test du bridgebot





erreur(){ 
	case $1 in
		usage)
			echo "$0: usage: $0 [-v] [NB_TESTS [DIMENSIONS [NB_COUPS_JOUES]]]" >&2
			exit 2
			;;
		fichier)
			echo "$0: fichier: $2 inexistant, ou droit insuffisants" >&2
			exit 3
			;;
	esac
}






# Répertoires
REP_IN=fichiers_in
REP_OUT=fichiers_out/BridgeBot

# Dimension des grilles
DIMENSIONS="10"

# Nombre de coups joués
NB_COUPS_JOUES="50"

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


# 2eme argument : nombre de tests
if test $# -ge 1
then
	expr $1 + 1 > /dev/null
	test $? -le 1 || erreur usage
	NB_TESTS=$1
fi 


# 3eme argument : dimensions à tester (sous forme d'une chaîne "1 3 7")
if test $# -ge 2
then
	DIMENSIONS=$2
fi 


# 4eme argument : Nombres de coups à jouer (sous forme d'une chaîne "1 3 7")
if test $# -ge 3
then
	NB_COUPS_JOUES=$3
fi 

# Plus d'arguments : erreur
test $# -ge 4 && erreur usage


# On vide le répertoire $REP_OUT
rm -fr $REP_OUT
mkdir -p $REP_IN
mkdir -p $REP_OUT





# Construction
# -----------------------------------------------

# Pattern du fichier en entree
f_in="$REP_IN/sauv_@1x@2_0.txt"

# Pattern du fichier en sortie
f_out="$REP_OUT/constr_@1x@2_@3.txt"

# Pattern de la commande pour créer le fichier en entrée
mk_f_in="./mk_sauvegardes @1 1 @2 $f_in"

# Pattern de la commande de test
commande="./main_BridgeBot -c $f_in 1 @3"

# Pattern de la commande de vérification
verif="" 


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
	./exec_serie_tests.sh $use_valgrind "$f_in" "$mk_f_in" "" "" "$f_out" "$commande" "$verif" "$largeur" "$bcl2" "0 1"
done




exit $ko






