/** 
 * \file     randombot.c
 * \brief    Implémentation du randombot en JNI
 * \author   Pierre Pomeret-Coquot
 * \version  1.1
 * \date     10 avril 2017
 */

# include <stdlib.h>
# include <time.h>
# include "randombot.h"

/**
 * \defgroup c_pack_ia_randombot IA0 : randombot
 * \ingroup  c_pack_ia
 * \brief    IA jouant des coups valides aléatoires
 * \author   Pierre Pomeret-Coquot
 * \version  1.1
 * \date     13 avril 2017
 * @{
 */

/**
 * \brief Renvoie un couple (x,y) correspondant à un couple valide
 */
JNIEXPORT jintArray JNICALL Java_noyau_IA0_randombotXjouer
  (JNIEnv * jEnv, jobject jObject, jintArray plateau, jint largeur){
  
	jint x, y;
	jintArray retour;
	jint temp[2];
	jint * cases;
	
	cases = (*jEnv)->GetIntArrayElements(jEnv, plateau, 0);
	
	/* On trouve une case vide */
	do {
		x = rand() % largeur;
		y = rand() % largeur;
	}
    while (cases[x + largeur*y] != 0);
    
    
	(*jEnv)->ReleaseIntArrayElements(jEnv, plateau, cases, 0);
	
	/* On décompose en (x,y) */
	temp[0] = x;
	temp[1] = y;
	
	/* On insère les jentiers dans le jtableau */
	retour = (*jEnv)->NewIntArray(jEnv, 2);
	(*jEnv)->SetIntArrayRegion(jEnv, retour, 0, 2, temp);
	
	
	return retour;
	
}


/**
 * \brief Initialise le randombot
 *
 * Initialise la série aléatoire du randombot
 */
JNIEXPORT void JNICALL Java_noyau_IA0_randombotXinit
  (JNIEnv * jEnv, jobject jObject){
	srand(time(NULL)); 
}


/** @} */

