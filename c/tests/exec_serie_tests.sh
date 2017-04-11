#! /bin/bash

# Execute une série de tests
#
# usage: $0 [-v] parttern_f_in "pattern_mk_f_in" pattern_f_out "pattern_commande" "boucle_1" ["boucle_2" ["boucle_3"]]
#
# Renvoie 0 si tout est OK, 1 si certains tests échouent, 2 ou plus en cas d'erreur



function erreur(){ 
	case $1 in
		usage)
			echo "$0 [-v] pattern_f_in \"pattern_mk_f_in\" pattern_f_in2 \"pattern_mk_f_in2\" pattern_fichier_out \"pattern_commande\" \"verif\" [\"boucle_1\" [\"boucle_2\"]]" >&2
			exit 2
			;;
		fichier)
			echo "$0: fichier: $2 inexistant, ou droit insuffisants" >&2
			exit 3
			;;
	esac
}






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


# Au moins 4 paramètres restants : 
test $# -ge 4 || erreur usage
pattern_f_in="$1"
shift
pattern_mk_f_in="$1"
shift
pattern_f_in2="$1"
shift
pattern_mk_f_in2="$1"
shift
pattern_f_out="$1"
shift
pattern_commande="$1"
shift
pattern_verif="$1"
shift



ok=0
ko=0

# Boucle par défaut = un élément unique (par exemple : 1)
test $# -le 0 && set 1
test $# -le 1 && set "$1" 1
test $# -le 2 && set "$1" "$2" 1

for e1 in $1
do
	for e2 in $2
	do
		for e3 in $3
		do
			f_in=`echo $pattern_f_in | sed -r "s/@1/$e1/g"`
			f_in2=`echo $pattern_f_in2 | sed -r "s/@1/$e1/g"`
			f_out=`echo $pattern_f_out | sed -r "s/@1/$e1/g"`
			mk_f_in=`echo $pattern_mk_f_in | sed -r "s/@1/$e1/g"`
			mk_f_in2=`echo $pattern_mk_f_in2 | sed -r "s/@1/$e1/g"`
			commande=`echo $pattern_commande | sed -r "s/@1/$e1/g"`
			verif=`echo $pattern_verif | sed -r "s/@1/$e1/g"`
			
			f_in=`echo $f_in | sed -r "s/@2/$e2/g"`
			f_in2=`echo $f_in2 | sed -r "s/@2/$e2/g"`
			f_out=`echo $f_out | sed -r "s/@2/$e2/g"`
			mk_f_in=`echo $mk_f_in | sed -r "s/@2/$e2/g"`
			mk_f_in2=`echo $mk_f_in2 | sed -r "s/@2/$e2/g"`
			commande=`echo $commande | sed -r "s/@2/$e2/g"`
			verif=`echo $verif | sed -r "s/@2/$e2/g"`
			
			f_in=`echo $f_in | sed -r "s/@3/$e3/g"`
			f_in2=`echo $f_in2 | sed -r "s/@3/$e3/g"`
			f_out=`echo $f_out | sed -r "s/@3/$e3/g"`
			mk_f_in=`echo $mk_f_in | sed -r "s/@3/$e3/g"`
			mk_f_in2=`echo $mk_f_in2 | sed -r "s/@3/$e3/g"`
			commande=`echo $commande | sed -r "s/@3/$e3/g"`
			verif=`echo $verif | sed -r "s/@3/$e3/g"`
			
			
			
			test -f "$f_in"  || $mk_f_in
			
			if test "$f_in2"!="" -a ! -f "$f_in2"
			then
				$mk_f_in2
				sleep 1
			fi
			
			
			./exec_test.sh $use_valgrind "$f_in" "$f_in2" "$f_out" "$commande" "$verif"
			
			if test $? -eq 0
			then
				ok=`expr $ok + 1`
			else
				ko=`expr $ko + 1`
			fi			
		done
	done
done

#if test $ko -eq 0
#then
#	echo -e "\x1B[1;32mTests OK : $ok / `expr $ok + $ko`\x1B[0m"
#else
#	echo -e "\x1B[1;31mTests OK : $ok / `expr $ok + $ko`\x1B[0m"
#fi

exit $ko
















