#! /bin/bash

# Execute les tests
#
# usage: $0 [-v] fichier_in fichier_out "commande" "verif"
#
# Renvoie 0 si tout est OK, 1 si certains tests échouent, 2 ou plus en cas d'erreur

erreur(){ 
	case $1 in
		usage)
			echo "$0: usage: $0 [-v] fichier_in fichier_in2 fichier_out \"commande\"" >&2
			exit 2
			;;
		fichier)
			echo "$0: fichier: $2 inexistant, ou droit insuffisants" >&2
			exit 3
			;;
	esac
}



# Facilité d'écriture
OK="[\x1B[1;32mOK\x1B[0m]"
KO="[\x1B[1;31mKO\x1B[0m]"
NON_TESTE="[\x1B[1;33m??\x1B[0m]"

# donne une taille en o / ko / Mo
echo_taille(){
	u="o"
	taille=$1
	
	# Divise par 1024
	if test $taille -ge 1024
	then
		u="ko"
		taille=`expr $taille / 1024`
	fi
	
	# Et encore...
	if test $taille -ge 1024
	then
		u="Mo"
		taille=`expr $taille / 1024`
	fi
	
	chaine="$taille $u"
	
	# Ajoute des espaces pour la présentation
	cpt=`expr length "$chaine"`
	while test $cpt -lt 7
	do
		chaine="$chaine "
		cpt=`expr $cpt + 1`
	done
	
	# Affichage
	echo -n "$chaine"
	return 0
}



# Par défaut

use_valgrind=""

# Option : 1er parametre, shifté
if test $# -ge 1
then
	case $1 in 
		-v|--valgrind)
			use_valgrind="1"
			shift
			;;
	esac
fi



# 4 parametres restants
test $# -eq 5 || erreur usage

f_in="$1"
f_in2="$2"
f_out="$3"
f_log="`dirname "$f_out"`/log_`basename "$f_out"`"
commande="$4"
verif="$5"

test -f "$f_in" -a -r "$f_in" || erreur fichier "$f_in"
test ! "$f_in2" || test -f "$f_in2" -a -r "$f_in" || erreur fichier "$f_in2"
test ! -f "$f_out" -o -w "$f_out" || erreur fichier "$f_out"

mkdir -p `dirname "$f_out"`





# AFFICHAGE : fichier en sortie (taille : 40c)
chaine="$f_out"
cpt=`expr length "$chaine"`
while test $cpt -lt 40
do
	chaine="$chaine "
	cpt=`expr $cpt + 1`
done
echo -n "$chaine"


memOK=0
resOK=0

# Execution
if test "$use_valgrind"
then
	tps_dep=`date +%s.%N`
	valgrind --log-file="$f_log" $commande > "$f_out"
	tps_fin=`date +%s.%N`

	# Recherche de la ligne qui fait plaisir dans le log valgrind
	grep "in use at exit: 0 bytes in 0 blocks" "$f_log" > /dev/null 2>&1
	
	# AFFICHAGE : tests memoire
	if test $? -eq 0
	then
		echo -ne "	mémoire : $OK"
		memOK=1
		# Mémoire utilisée
		echo -n " (utilisé: "
		echo_taille `grep "total heap usage" "$f_log" | tr -s " " | cut -d  " " -f 9 | tr -d ","`
		echo -n ")"
	else
		echo -ne "	mémoire : $KO"
		# Mémoire utilisée
		echo -n " (utilisé: "
		echo_taille `grep "total heap usage" "$f_log" | tr -s " " | cut -d  " " -f 9 | tr -d ","`
		echo -n ", perdu: "
		echo_taille `grep "in use at exit" "$f_log" | tr -s " " | cut -d  " " -f 6 | tr -d ","`
		echo -n ")"
	fi
	
	
else
	tps_dep=`date +%s.%N`
	$commande > "$f_out"
	tps_fin=`date +%s.%N`
fi



tps=$(echo "$tps_fin - $tps_dep" | bc)
test "`echo $tps|cut -c 1`" = "." && tps="0$tps"
tps=`echo $tps | head -c 5`




# Vérification

if test "$verif" 
then

	$verif

	if test $? -eq 0
	then
		echo -e "	resultat : $OK   (tps: $tps s)"
		resOK=1
	else
		echo -e "	resultat : $KO   (tps: $tps s)"
	fi

	test $resOK -eq 1 && test ! "$use_valgrind" -o $memOK -eq 1 && exit 0
else
	echo -e "	resultat : $NON_TESTE   (tps: $tps s)"
	test ! "$use_valgrind" -o $memOK -eq 1 && exit 0
fi


exit 1








