#! /bin/bash


# Test de ABR sur des NUplets d'entiers




function erreur(){ 
	case $1 in
		usage)
			echo "$0: usage: $0 [-v] [TAILLES_DAMIER [JOUEURS [NB_TESTS]]]" >&2
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
REP_OUT=fichiers_out/Minimax

# Taille du damier par défaut
TAILLE_DAMIER="2"

# Joueur
JOUEURS="1 2"

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


# 1er argument : taille de damier (sous forme d'une chaîne "2 4 6")
if test $# -ge 1
then
	TAILLE_DAMIER="$1"
fi 

# 2eme argument : Joueur (sous forme d'une chaîne "1 3 7")
if test $# -ge 2
then
	JOUEUR="$2"
fi 

# 3eme argument : nombre de tests
if test $# -ge 3
then
	expr $3 + 1 > /dev/null
	test $? -le 1 || erreur usage
	NB_TESTS=$3
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



# Construction
# -------------------------------------

# Pattern du fichier en entree
f_in="$REP_IN/sauv_@1x0_@3.txt"

# Pattern du fichier en sortie
f_out="$REP_OUT/construction_@1x0_j@2_@3.txt"

# Pattern de la commande pour créer le fichier en entrée
mk_f_in="./mk_sauvegardes @1 1 0 $f_in"

# Pattern de la commande de test
commande="./main_Minimax -c $f_in @2 n"

# Pattern de la commande de vérification
verif="" 


./exec_serie_tests.sh $use_valgrind "$f_in" "$mk_f_in" "" "" "$f_out" "$commande" "$verif" "$TAILLE_DAMIER" "$JOUEURS" "$bcl"


test $? -eq 0 || ko=`expr $ko + 1`



# Notation
# -------------------------------------

# Pattern du fichier en entree
#idem

# Pattern du fichier en sortie
f_out="$REP_OUT/notation_@1x@2_@3.txt"

# Pattern de la commande pour créer le fichier en entrée
mk_f_in="./mk_sauvegardes @1 1 0 $f_in"

# Pattern de la commande de test
commande="./main_Minimax -n $f_in @2 n"

# Pattern de la commande de vérification
verif="" 


# Désactiové pour l'instant...
# ./exec_serie_tests.sh $use_valgrind "$f_in" "$mk_f_in" "" "" "$f_out" "$commande" "$verif" "$TAILLE_DAMIER" "$JOUEURS" "$bcl"
# test $? -eq 0 || ko=`expr $ko + 1`








exit $ko




