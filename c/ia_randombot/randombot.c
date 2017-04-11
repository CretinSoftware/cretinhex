# include <stdlib.h>
# include <time.h>
# include "randombot.h"

/*
 * Class:     noyau_IA0
 * Method:    randombotXjouer
 * Signature: ([I)[I
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
		printf("IA0 : x=%d, y=%d\n", (int) x, (int) y);
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


/*
 * Class:     noyau_IA0
 * Method:    randombotXinit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_noyau_IA0_randombotXinit
  (JNIEnv * jEnv, jobject jObject){
	srand(time(NULL)); 
}


