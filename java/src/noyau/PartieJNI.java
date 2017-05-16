package noyau;

/**
 * \class noyau.PartieJNI
 * \ingroup java_pack_JNI
 * \brief Communication avec la bibliothèque cretinhex
 *
 * \version 1.2
 * \author Pierre Pomeret-Coquot
 * \date 12 mars 2017
 * 
 * La partie gérée en natif : l'interface JNI dialogue avec la bibliothèque cretinhex
 */
public class PartieJNI {


	
	
	/** \brief Bibliothèque native */
	static {
		//System.out.println("Java.library.path = " + System.getProperty("java.library.path"));
		System.loadLibrary("cretinhex");
	}



	/* Attributs */
	protected int tour;        /**< \brief Tour de jeu en cours. Utile ? */
	protected int largeur;     /**< \brief Largeur du damier. Utile ? */
	protected Joueur j;        /**< \brief aQuiDeJouer : utile ? */
	
	
	
	
	
	/**
	 * \brief Constructeur d'après fichier de sauvegarde
	 */
	PartieJNI(String nomFichier){
		this.cretinhexXcharger(nomFichier);
		
		this.largeur = this.cretinhexXlargeurDamier();
		this.j = Joueur.fromInt(this.cretinhexXaQuiDeJouer());
		this.tour = 1;
	}
	
	/**
	 * \brief Constructeur de nouvelle partie.
	 */
	PartieJNI(int l, Joueur j){
		this.cretinhexXinit(l, j.toInt());
		
		this.largeur = this.cretinhexXlargeurDamier();
		this.j = Joueur.fromInt(this.cretinhexXaQuiDeJouer());
		this.tour = 1;
	}
	
	
	
	

	/**
	 * \fn native void cretinhexXinit(int l, Joueur j)
	 * \param l La largeur du damier
	 * \param j Le premier joueur
	 * \brief Initialise la partie de Hex
	 *
	 * \attention La partie est gérée par une variable globale et doit donc ABSOLUMENT être unique
	 */ 
	protected native void cretinhexXinit(int l, int j);


	/**
	 * \fn native int cretinhexXlargeurDamier()
	 * \brief Donne la largeur du damier
	 */ 
	protected native int cretinhexXlargeurDamier();
	

	/**
	 * \fn native int cretinhexXaQuiDeJouer()
	 * \return Le joueur dont c'est le tour
	 * \brief A qui est-ce de jouer ?
	 */ 
	protected native int cretinhexXaQuiDeJouer();
	

	/**
	 * \fn native int cretinhexXobtenirTour()
	 * \return Le numéro du tour
	 * \brief A quel tour sommes-nous ?
	 */ 
	protected native int cretinhexXobtenirTour();
	

	/**
	 * \fn native void cretinhexXplacerPion(int x, int y)
	 * \param x Première coordonnée
	 * \param y Seconde coordonnée
	 * \brief Placer un pion sur le damier
	 *
	 * Place un pion (du joueur this.aQuiDeJouer()) sur la case (x, y)
	 * Pour rappel :
	 *  - x : colonne
	 *  - y : ligne
	 */ 
	protected native void cretinhexXplacerPion(int x, int y);
	

	/**
	 * \brief Donne l'occupant d'une case sur le damier
	 * \fn native int cretinhexXobtenirCase(int x, int y)
	 * \param x Première coordonnée
	 * \param y Seconde coordonnée
	 * \return Le joueur occupant la case (x, y)
	 */ 
	protected native int cretinhexXobtenirCase(int x, int y);
	

	/**
	 * \return Le damier sous forme d'un tableau linéaire 
	 * \brief Récupérer tout le damier
	 *
	 * Le renvoi est un tableau linéaire de largeur*largeur cases
	 * correspondant aux cases du damier
	 * \note
	 * La case (x,y) est à l'indice (x + y*largeur)
	 */ 
	protected native int[] cretinhexXobtenirDamier();
	

	/**
	 * \brief L'état du damier au tour n
	 * \param n Le numéro de tour auquel on veut accéder
	 * \return Le damier sous forme d'un tableau linéaire 
	 *
	 * Le renvoi est un tableau linéaire de largeur*largeur cases
	 * correspondant aux cases du damier au tour n
	 * \note
	 * La case (x,y) est à l'indice (x + y*largeur)
	 */ 
	protected native int[] cretinhexXobtenirDamierHisto(int n);
	

	/**
	 * \fn native int cretinhexXquiGagne()
	 * \return Le joueur gagnant, J0 si la partie est en cours
	 * \brief A-t'on un gagnant ?
	 *
	 * \attention La fonctionnalité n'est pas codé en C, la fonction renvoie toujours J0
	 */ 
	protected native int cretinhexXquiGagne();
	

	/**
	 * \fn native int cretinhexXsauvegarder(String nomFichier)
	 * \param nomFichier Le fichier de sauvegarde
	 * \brief Enregistre une partie dans un fichier
	 *
	 */ 
	protected native int cretinhexXsauvegarder(String nomFichier);
	

	/**
	 * \fn native void cretinhexXcharger(String nomFichier)
	 * \param nomFichier Le fichier de sauvegarde
	 * \brief Charge la partie depuis un fichier
	 */ 
	protected native void cretinhexXcharger(String nomFichier);
	

	/**
	 * \fn native void cretinhexXcharger(String nomFichier)
	 * \param nomFichier Le fichier de sauvegarde
	 * \brief Charge la partie depuis un fichier
	 */ 
	protected native void cretinhexXannuler(int nombreDeTours);
	

	/**
	 * \fn native int cretinhexXlibererMemoire()
	 * \brief Libère la mémoire allouée à une partie.
	 */ 
	protected native void cretinhexXlibererMemoire();
	
	
	
	
	
}

/** @} */
