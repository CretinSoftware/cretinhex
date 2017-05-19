/** 
 * \file     randombot.c
 * \brief    Implémentation du randombot en JNI
 * \author   Pierre Pomeret-Coquot
 * \version  1.1
 * \date     10 avril 2017
 */

# include <stdlib.h>
# include <time.h>
# include <assert.h>
# include "randombot.h"

/**
 * \defgroup pack_ia_randombot IA0 : randombot
 * \ingroup  pack_ia
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
	
	int casesVides[largeur*largeur];
	int nbCasesVides = 0;
	int i;
	
	cases = (*jEnv)->GetIntArrayElements(jEnv, plateau, 0);
	for (i = 0; i < largeur*largeur; ++i)
		if (cases[i] == 0)
			casesVides[nbCasesVides++] = i;
	
	assert(nbCasesVides > 0);
	i = rand() % nbCasesVides;
	x = casesVides[i] % largeur;
	y = casesVides[i] / largeur;
	
    
	(*jEnv)->ReleaseIntArrayElements(jEnv, plateau, cases, 0);
	
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

