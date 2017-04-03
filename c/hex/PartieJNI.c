/**
 * \file PartieJNI.c
 * \brief Type Partie pour utilisation avec JNI
 * \author Pierre POMERET-COQUOT
 * \version 1.0
 * \date 2 mars 2017
 *
 * \see Partie.c
 * \attention La partie est une variable globale : une seule partie à la fois !
 *
 * Traduction de Partie.c pour l'interface JNI
 *
 *     
 */
# include "PartieJNI.h"
# include "Partie.h"
# include <stdio.h>
# include <stdlib.h>
# include <assert.h>


/** 
 * La variable globale PARTIE_GLOBALE stocke la partie en cours
 * \todo Trouver comment stocker la partie en mémoire / la transmettre à java
 */
Partie PARTIE_GLOBALE;



/*
 * Class:     cretinhex_PartieJNI
 * Method:    init
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_noyau_PartieJNI_cretinhexXinit
  (JNIEnv * jEnv, jobject jObject, jint l, jint j){
	Joueur joueur;
	switch (j){
		case 1:  joueur = J1; break;
		case 2:  joueur = J2; break;
		default: joueur = J0; break;
	}
	PARTIE_GLOBALE = Partie_init((int) l, joueur);
}

/*
 * Class:     cretinhex_PartieJNI
 * Method:    largeurDamier
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_noyau_PartieJNI_cretinhexXlargeurDamier
  (JNIEnv * jEnv, jobject jObject){
	return (jint) Partie_largeurDamier(PARTIE_GLOBALE);
}

/*
 * Class:     cretinhex_PartieJNI
 * Method:    aQuiDeJouer
 * Signature: ()V
 */
JNIEXPORT jint JNICALL Java_noyau_PartieJNI_cretinhexXaQuiDeJouer
  (JNIEnv * jEnv, jobject jObject){
	return (jint) Partie_aQuiDeJouer(PARTIE_GLOBALE);
}

/*
 * Class:     cretinhex_PartieJNI
 * Method:    obtenirTour
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_noyau_PartieJNI_cretinhexXobtenirTour
  (JNIEnv * jEnv, jobject jObject){
	return (jint) Partie_obtenirTour(PARTIE_GLOBALE);
}


/*
 * Class:     cretinhex_PartieJNI
 * Method:    placerPion
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_noyau_PartieJNI_cretinhexXplacerPion
  (JNIEnv * jEnv, jobject jObject, jint x, jint y){
	PARTIE_GLOBALE = Partie_placerPion(PARTIE_GLOBALE, x, y);
}

/*
 * Class:     cretinhex_PartieJNI
 * Method:    obtenirCase
 * Signature: (II)I
 */
 
JNIEXPORT jint JNICALL Java_noyau_PartieJNI_cretinhexXobtenirCase
  (JNIEnv * jEnv, jobject jObject, jint x, jint y){
	return (jint) Partie_obtenirCase(PARTIE_GLOBALE, x, y);
}

/*
 * Class:     cretinhex_PartieJNI
 * Method:    obtenirDamier
 * Signature: ()[I
 */
JNIEXPORT jintArray JNICALL Java_noyau_PartieJNI_cretinhexXobtenirDamier
  (JNIEnv * jEnv, jobject jObject){
  
  	/* Création d'un tableau java dans jEnv */
  	int l = Partie_largeurDamier(PARTIE_GLOBALE);
	jintArray retour = (*jEnv)->NewIntArray(jEnv, l*l);
	assert(retour != NULL);
	
	/* Création d'entiers java dans temp */
	jint temp[l*l];
	int i;
	Joueur * damier = Partie_obtenirDamier(PARTIE_GLOBALE);
	for (i = 0; i < l*l; ++i)
		temp[i] = (jint) damier[i];
	free(damier);
	
	/* Insertion des entiers dans le tableau */
	(*jEnv)->SetIntArrayRegion(jEnv, retour, 0, l*l, temp);
	
	return retour;
}

/*
 * Class:     cretinhex_PartieJNI
 * Method:    obtenirDamierHisto
 * Signature: (I)[I
 */
JNIEXPORT jintArray JNICALL Java_noyau_PartieJNI_cretinhexXobtenirDamierHisto
  (JNIEnv * jEnv, jobject jObject, jint n){
  
  	/* Création d'un tableau java dans jEnv */
  	int l = Partie_largeurDamier(PARTIE_GLOBALE);
	jintArray retour = (*jEnv)->NewIntArray(jEnv, l*l);
	assert(retour != NULL);
	
	/* Création d'entiers java dans temp */
	jint temp[l*l];
	int i;
	Joueur * damier = Partie_obtenirDamierHisto(PARTIE_GLOBALE, n);
	for (i = 0; i < l*l; ++i)
		temp[i] = (jint) damier[i];
	free(damier);
	
	/* Insertion des entiers dans le tableau */
	(*jEnv)->SetIntArrayRegion(jEnv, retour, 0, l*l, temp);
	
	return retour;
}

/*
 * Class:     cretinhex_PartieJNI
 * Method:    quiGagne
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_noyau_PartieJNI_cretinhexXquiGagne
  (JNIEnv * jEnv, jobject jObject){
	return Partie_quiGagne(PARTIE_GLOBALE);
}

/*
 * Class:     cretinhex_PartieJNI
 * Method:    sauvegarder
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT jint JNICALL Java_noyau_PartieJNI_cretinhexXsauvegarder
  (JNIEnv * jEnv, jobject jObject, jstring jString){
	const char *nomFichier = (*jEnv)->GetStringUTFChars(jEnv, jString, 0);
	printf("Sauvegarde : %s\n", nomFichier);
	return Partie_sauvegarder(PARTIE_GLOBALE, nomFichier);
}

/*
 * Class:     cretinhex_PartieJNI
 * Method:    charger
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_noyau_PartieJNI_cretinhexXcharger
  (JNIEnv * jEnv, jobject jObject, jstring jString){
	const char *nomFichier = (*jEnv)->GetStringUTFChars(jEnv, jString, 0);
	printf("Charger depuis : %s\n", nomFichier);
	PARTIE_GLOBALE = Partie_charger(nomFichier);
}
/*
 * Class:     cretinhex_PartieJNI
 * Method:    libererMemoire
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_noyau_PartieJNI_cretinhexXlibererMemoire
  (JNIEnv * jEnv, jobject jObject){
	Partie_libererMemoire(&PARTIE_GLOBALE);
}



