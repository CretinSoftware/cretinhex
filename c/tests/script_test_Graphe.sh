#! /bin/bash


# Test de la LDC sur des NUplets d'entiers




function erreur(){ 
	case $1 in
		usage)
			echo "$0: usage: $0 [-v] [TAILLE_DONNEES [NB_LIENS [NB_TESTS]]]" >&2
			echo "$0: usage: $0 -m fichier_in fichier_resultats TAILLE_DONNEES" >&2
			echo "$0: usage: $0 -c fichier_out fichier_resultats" >&2
			exit 2
			;;
		fichier)
			echo "$0: fichier: $2 inexistant, ou droit insuffisants" >&2
			exit 3
			;;
	esac
}




# Fabrique le fichier résultat à comparer (lignes dans le désordre)
mk_f_resultat(){
	test -f "$1" -a -r "$1" || erreur fichier "$1"
	test ! -f "$2" -o -w "$2" || erreur fichier "$2"
	
	f_in="$1"
	f_res="$2"
	nbNoeuds=$3
	n=0
	
	nbNAff=`expr $nbNoeuds / 10`
	
	echo -n "mk fichier $2"
	
	echo -n "" > "$f_res"
	while test $n -lt $nbNoeuds
	do
		
		test `expr $n % $nbNAff` -eq 0 && echo -n "."
		echo -n "$n : " >> "$f_res"
		voisin=0
		while test $voisin -lt $nbNoeuds
		do
			cat "$f_in" | grep "^$n :.* $voisin " > /dev/null
			test $? -eq 0 && echo -n "$voisin " >> "$f_res"
			cat "$f_in" | grep "^$voisin :.* $n " > /dev/null
			test $? -eq 0 && echo -n "$voisin " >> "$f_res"
			voisin=`expr $voisin + 1`
		done
		echo "" >> "$f_res"
		n=`expr $n + 1`
	done
	echo ""
	
	return 0
	
}



# Compare deux fichiers dont les lignes peuvent être dans le désordre
compare(){
	f_out="$1"
	f_cmp="$2"
	
	# Autant de lignes
	test `cat "$f_out" | wc -l` -eq `cat "$f_cmp" | wc -l` || exit $?

	# Et celles de f_out sont dans f_cmp
	while read ligne
	do
		cat "$f_cmp" | grep "$ligne" > /dev/null || exit $?
	done < "$f_out"
	
	return 0
}





# Répertoires
REP_IN=fichiers_in
REP_OUT=fichiers_out/Graphe

# Nombre de n-uplets à traiter par défaut
TAILLE_DONNEES=25

# Dimension des n-uplets
NB_LIENS=10

# Nombre de tests pour une dimension donnée
NB_TESTS=2




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
			test $# -eq 3 || erreur usage
			test -f $1 -a -f $2 || mk_f_resultat "$1" "$2" $3
			exit $?
			;;
		-c)
			shift
			test $# -eq 2 || erreur usage
			test -f "$1" -a -r "$1" || erreur fichier "$1"
			test -f "$2" -a -r "$2" || erreur fichier "$2"
			compare "$1" "$2"
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

# 2eme argument : nombre de liens à la fabrication
if test $# -ge 2
then
	expr $2 + 1 > /dev/null
	test $? -le 1 || erreur usage
	NB_LIENS=$2
fi 

# 2eme argument : nombre de tests identiques
if test $# -ge 3
then
	expr $3 + 1 > /dev/null
	test $? -le 1 || erreur usage
	NB_TESTS=$2
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





# Construction
# -------------------------------------

# Pattern du fichier en entree
f_in="$REP_IN/graphe_${TAILLE_DONNEES}x${NB_LIENS}_@1.txt"

# Pattern du fichier de comparaison
f_in2="$REP_IN/graphe_results_${TAILLE_DONNEES}x${NB_LIENS}_@1.txt"

# Pattern du fichier en sortie
f_out="$REP_OUT/`basename $f_in`"

# Pattern de la commande pour créer le fichier en entrée
mk_f_in="./mk_fichier_graphe $TAILLE_DONNEES $NB_LIENS $f_in"

# Pattern de la commande pour créer le fichier de comparaison
mk_f_in2="$0 -m $f_in $f_in2 $TAILLE_DONNEES"

# Pattern de la commande de test
commande="./main_Graphe -c $TAILLE_DONNEES $NB_LIENS $f_in"

# Pattern de la commande de vérification
verif="$0 -c $f_out $f_in2" 


./exec_serie_tests.sh $use_valgrind "$f_in" "$mk_f_in" "$f_in2" "$mk_f_in2" "$f_out" "$commande" "$verif" "$bcl"

test $? -eq 0 || exit 1






