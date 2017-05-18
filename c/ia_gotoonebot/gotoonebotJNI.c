
#include "gotoonebot.h"
#include "gotoonebotJNI.h"
#include <stdio.h>





gotoone TRUC = NULL;


JNIEXPORT void JNICALL Java_noyau_Gotoonebot_gotoonebotXinit
  (JNIEnv * jEnv, jobject jObj, jint joueur){
		TRUC = gotoone_init((Joueur) joueur);
	}


JNIEXPORT jintArray JNICALL Java_noyau_Gotoonebot_gotoonebotXjouer
  (JNIEnv * jEnv, jobject jObj, jintArray plateau, jint largeur){
		
		
		
	jintArray retour;
	jint temp[2];
	jint * cases;
	jint x, y;
	int i;
	
	/* Fabrication du damier de la partie */
	cases = (*jEnv)->GetIntArrayElements(jEnv, plateau, 0);
	Damier d = Damier_init(largeur);
	for (i = 0; i < largeur * largeur; ++i){
		switch (cases[i]){
			case 1: d = Damier_modifierCase(d, J1, i%largeur, i/largeur); break;
			case 2: d = Damier_modifierCase(d, J2, i%largeur, i/largeur); break;
		}
	}
	
	/* Calcul du coup à jouer */
	gotoone_jouer(TRUC, d, &x, &y);
	
	Damier_libererMemoire(&d);
	
	
	(*jEnv)->ReleaseIntArrayElements(jEnv, plateau, cases, 0);
	
	/* On décompose en (x,y) */
	temp[0] = x;
	temp[1] = y;
	
	/* On insère les jentiers dans le jtableau */
	retour = (*jEnv)->NewIntArray(jEnv, 2);
	(*jEnv)->SetIntArrayRegion(jEnv, retour, 0, 2, temp);
	
	return retour;
		
	}

