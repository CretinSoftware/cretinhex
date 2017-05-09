package noyau;

	
/**
 * \class noyau.Partie
 * \brief Manipulation de partie
 *
 * Le calcul provient de la classe PartieJNI (et donc de la bibliothèque externe cretinhex)
 *
 */
public class Partie extends PartieJNI {


	public static final int TAILLE_PAR_DEFAUT = 11;   /**< Taille par défaut du damier */

	
	/** \brief Constructeur pour une nouvelle partie par défaut */
	public Partie(){
		super(TAILLE_PAR_DEFAUT, Joueur.J1);
	}
	
	/** \brief Constructeur pour une nouvelle partie de taille l */
	public Partie(int l){
		super(l, Joueur.J1);
	}
	
	/** \brief Constructeur pour une nouvelle partie de taille l où j commence */
	public Partie(int l, Joueur j){
		super(l, j);
	}
	
	/** \brief Constructeur pour une partie par défaut où j commence */
	public Partie(Joueur j){
		super(TAILLE_PAR_DEFAUT, j);
	}	
	
	/** \brief Constructeur pour une partie d'après le fichier de sauvegarde nomFichier */
	public Partie(String nomFichier){
		super(nomFichier);
	}
	
	
	
	
	
	
	/* Méthodes */
	 

	/**
	 * \fn int largeurDamier()
	 * \brief Donne la largeur du damier
	 */ 
	public int largeurDamier(){
		return this.largeur;
	}
	

	/**
	 * \fn int aQuiDeJouer()
	 * \return Le joueur dont c'est le tour
	 * \brief A qui est-ce de jouer ?
	 */ 
	public Joueur aQuiDeJouer(){
		return this.j;
	}
	

	/**
	 * \fn int obtenirTour()
	 * \return Le numéro du tour
	 * \brief A quel tour sommes-nous ?
	 */ 
	public int obtenirTour(){
		return super.cretinhexXobtenirTour();
	}

	/**
	 * \fn void placerPion(int x, int y)
	 * \param x Première coordonnée
	 * \param y Seconde coordonnée
	 * \brief Placer un pion sur le damier
	 *
	 * Place un pion (du joueur this.aQuiDeJouer()) sur la case (x, y)
	 * Pour rappel :
	 *  - x : colonne
	 *  - y : ligne
	 */ 
	public void placerPion(int x, int y){
		super.cretinhexXplacerPion(x, y);
		this.j = Joueur.fromInt(super.cretinhexXaQuiDeJouer());
	}
	

	/**
	 * \fn Joueur obtenirCase(int x, int y)
	 * \param x Première coordonnée
	 * \param y Seconde coordonnée
	 * \return Le joueur occupant la case (x, y)
	 * \brief Donne l'occupant d'une case sur le damier
	 */ 
	public Joueur obtenirCase(int x, int y){
		return Joueur.fromInt(super.cretinhexXobtenirCase(x, y));
	}
	

	/**
	 * \return Le damier sous forme d'un tableau linéaire 
	 * \brief Récupérer tout le damier
	 *
	 * Le renvoi est un tableau linéaire de largeur*largeur cases
	 * correspondant aux cases du damier
	 * \note
	 * La case (x,y) est à l'indice (x + y*largeur)
	 */ 
	public Joueur[] obtenirDamier(){
		int[] damierI = super.cretinhexXobtenirDamier();
		Joueur[] damierJ = new Joueur[this.largeur * this.largeur];
		
		for (int i = 0; i < this.largeur * this.largeur; ++i)
			damierJ[i] = Joueur.fromInt(damierI[i]);
			
		return damierJ;
	}
	
	/**
	 * \brief  Renvoie le damier sous forme d'entier
	 */
	public int[] obtenirDamierInt(){
		return super.cretinhexXobtenirDamier();
	}
		
	

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
	public Joueur[] obtenirDamierHisto(int n){
		int[] damierI = super.cretinhexXobtenirDamierHisto(n);
		Joueur[] damierJ = new Joueur[this.largeur * this.largeur];
		
		for (int i = 0; i < this.largeur * this.largeur; ++i)
			damierJ[i] = Joueur.fromInt(damierI[i]);
			
		return damierJ;
	}
	

	/**
	 * \fn Joueur quiGagne()
	 * \return Le joueur gagnant, J0 si la partie est en cours
	 * \brief A-t'on un gagnant ?
	 *
	 * \attention La fonctionnalité n'est pas codé en C, la fonction renvoie toujours J0
	 */ 
	public Joueur quiGagne(){
		return Joueur.fromInt(super.cretinhexXquiGagne());
	}
	

	/**
	 * \fn void sauvegarder(String nomFichier)
	 * \param nomFichier Le fichier de sauvegarde
	 * \brief Enregistre une partie dans un fichier
	 *
	 */ 
	public void sauvegarder(String nomFichier) throws RuntimeException { 
			if (super.cretinhexXsauvegarder(nomFichier) == -1)
				throw new RuntimeException("Impossible d'enregistrer dans " + nomFichier);
	}
	

	/**
	 * \fn void charger(String nomFichier)
	 * \param nomFichier Le fichier de sauvegarde
	 * \brief Charge la partie depuis un fichier
	 */ 
	public void charger(String nomFichier){
		super.cretinhexXcharger(nomFichier);
		this.largeur = this.cretinhexXlargeurDamier();
		this.j = this.aQuiDeJouer();
	}
	

	/**
	 * \fn void annuler(int nbTours)
	 * \param nbTours le nombre de mouvements à annuler
	 * \brief Annule nbTours coups
	 */ 
	public void annuler(int nbTours){
		super.cretinhexXannuler(nbTours);
		this.j = Joueur.fromInt(super.cretinhexXaQuiDeJouer());
	}
	

	/**
	 * \fn int libererMemoire()
	 * \brief Libère la mémoire allouée à une partie. 
	 */ 
	public void libererMemoire(){
		super.cretinhexXlibererMemoire();
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	/**
	 * Affiche un damier, quel qu'il soir
	 */
	public void afficherDamier(Joueur damier[]){
		for (int i = 0; i < this.largeur; ++i){
			for (int j = 0; j < i; ++j)
				System.out.print(" ");
			for (int j = 0; j < this.largeur; ++j){
				System.out.print(damier[i * this.largeur + j].toChar() + " ");
			}
			System.out.print("\n");
		}
	}
	
	
	
	/**
	 * Affichage du damier actuel
	 */
	public void afficher(){
		System.out.println("\nTour " + this.obtenirTour() + ", c'est à " + this.j.toString());
		Joueur damier[] = this.obtenirDamier();
		this.afficherDamier(damier);
	}
	
	/**
	 * \brief Affichage d'un damier de l'historique
	 */
	public void afficherHisto(int n){
		System.out.println("\nHistorique : tour " + n);
		Joueur damier[] = this.obtenirDamierHisto(n);
		this.afficherDamier(damier);
	}
		
	
	
	
	
	
	
	
	
	
	
	
	/** 
	 * Joue un tour en x,y et affiche un peu de texte
	 */
	public void afficherTourComplet(int x, int y){
		System.out.print("Tour " + this.obtenirTour() + " : " + this.j.toString() + " joue en " + x + "x" + y + "... ");
		this.placerPion(x, y);
		System.out.println("C'est à " + this.j.toString() + " de jouer");
	}
	
	
	
	
}
