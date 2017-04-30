/** 
 * \file    bridgebotJNI.h
 * \author  Pierre Pomeret-Coquot
 * \date    14 avril 2017
 * \brief   Implémentation de l'interface JNI pour Bridgebot
 */
 
# include "bridgebot.h"
# include "bridgebotJNI.h"




/**
 * \brief   Appelle de BridgeBot pour savoir quoi jouer
 *
 * \par     Description
 * Le BridgeBot trouve les meilleurs chemins les plus courts menant à la victoire, 
 * pour un Damier donné et pour les deux joueurs.
 * Il y detecte les ponts et essaie d'avancer son chemin en empèchant son adversaire 
 * de faire la même chose 
 */
JNIEXPORT jintArray JNICALL Java_noyau_BridgeBot_bridgebotXjouer
  (JNIEnv * jEnv, jobject jObject, jintArray plateau, jint largeurDamier, jint joueur){
  
	jintArray retour;
	jint temp[2];
	jint * cases;
	jint x, y;
	int i;
	
	/* Fabrication du damier de la partie */
	cases = (*jEnv)->GetIntArrayElements(jEnv, plateau, 0);
	Damier d = Damier_init(largeurDamier);
	for (i = 0; i < largeurDamier * largeurDamier; ++i){
		switch (cases[i]){
			case 1: d = Damier_modifierCase(d, J1, i%largeurDamier, i/largeurDamier); break;
			case 2: d = Damier_modifierCase(d, J2, i%largeurDamier, i/largeurDamier); break;
		}
	}
	
	/* Calcul du coup à jouer */
	BridgeBot_jouer(d, joueur, &x, &y, BRIDGEBOT_PONTS);
	
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


/**
 * \brief   Initialise le BridgeBot (alloue de la mémoire, dit qui il est (J1 ou J2))
 */
JNIEXPORT void JNICALL Java_noyau_BridgeBot_bridgebotXinit
  (JNIEnv * jEnv, jobject jObject){
	BridgeBot_init();
}


/**
 * \brief   Tue un BridgeBot
 *
 * \par     Description
 * Libère la mémoire allouée au bridgebot
 */
JNIEXPORT void JNICALL Java_noyau_BridgeBot_bridgebotXlibererMemoire
  (JNIEnv * jEnv, jobject jObject){
}


