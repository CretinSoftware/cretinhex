#! /bin/bash


# Test de la Partie sur le chargement / sauvegarde





erreur(){ 
	case $1 in
		usage)
			echo "$0: usage: $0 [-v] [NB_TESTS [DIMENSIONS [NB_COUPS_JOUES]]]" >&2
			echo "$0: usage: $0 -c f_sauv f_out" >&2
			echo "$0: usage: $0 -g f_sauv f_out DIMENSION" >&2
			exit 2
			;;
		fichier)
			echo "$0: fichier: $2 inexistant, ou droit insuffisants" >&2
			exit 3
			;;
	esac
}



compare(){
	cat "$1" | grep -v "^\\\\" > tmp
	cmp tmp "$2" > /dev/null 2>&1 && rm tmp
	exit $?
}



compareGroupes(){
	ko=0
	
	cat "$1" | grep -v "^\\\\" | tr 'o*.' ',,X' > tmp
	cat "$2" | head -n $3 | tr '0-9' 'X' | tr '.' ',' | tr -s 'X' > tmp2
	cmp tmp tmp2 > /dev/null 2>&1
	test $? -eq 0 || ko=`expr $ko + 1`
	
	cat "$1" | grep -v "^\\\\" | tr 'o*.' 'X,,' > tmp
	cat "$2" | head -n `expr 2 \* $3` | tail -n $3 | tr '0-9' 'X' | tr '.' ',' | tr -s 'X' > tmp2
	cmp tmp tmp2 > /dev/null 2>&1
	test $? -eq 0 || ko=`expr $ko + 1`
	
	cat "$1" | grep -v "^\\\\" | tr 'o*.' ',X,' > tmp
	cat "$2" | tail -n $3 | tr '0-9' 'X' | tr '.' ',' | tr -s 'X' > tmp2
	cmp tmp tmp2 > /dev/null 2>&1
	test $? -eq 0 || ko=`expr $ko + 1`
	
	rm tmp tmp2
	
	return $ko
	
}






# Répertoires
REP_IN=fichiers_in
REP_OUT=fichiers_out/GrapheHex

# Dimension des grilles
DIMENSIONS="5 10"

# Nombre de coups joués
NB_COUPS_JOUES="25 100"

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
		-c)
			shift
			test $# -eq 2 || erreur usage
			test -f "$1" -a -r "$1" || erreur fichier "$1"
			test -f "$2" -a -r "$2" || erreur fichier "$2"
			compare "$1" "$2"
			exit $?
			;;
		-g)
			shift
			test $# -eq 3 || erreur usage
			test -f "$1" -a -r "$1" || erreur fichier "$1"
			test -f "$2" -a -r "$2" || erreur fichier "$2"
			compareGroupes "$1" "$2" $3
			exit $?
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
f_in="$REP_IN/sauv_@1x@2_@3.txt"

# Pattern du fichier en sortie
f_out="$REP_OUT/constr_@1x@2_@3.txt"

# Pattern de la commande pour créer le fichier en entrée
mk_f_in="./mk_sauvegardes @1 1 @2 $f_in"

# Pattern de la commande de test
commande="./main_GrapheHex -c $f_in"

# Pattern de la commande de vérification
verif="$0 -c $f_in $f_out" 


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






# Groupes
# -----------------------------------------------

# Pattern du fichier en entree
f_in="$REP_IN/sauv_@1x@2_@3.txt"

# Pattern du fichier en sortie
f_out="$REP_OUT/groupes_@1x@2_@3.txt"

# Pattern de la commande pour créer le fichier en entrée
mk_f_in="./mk_sauvegardes @1 1 @2 $f_in"

# Pattern de la commande de test
commande="./main_GrapheHex -g $f_in"

# Pattern de la commande de vérification
verif="$0 -g $f_in $f_out @1" 




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






