/**
 * \class    ihm.console.PageJeu
 * \author   Pierre Pomeret-Coquot
 * \author   François Mahé
 * \date     samedi 1er avril 2017
 *
 * \todo     Faire / terminer la PageJeu
 */
package ihm.console;
import cretinplay.Application;
import noyau.Partie;
import noyau.Joueur;
import noyau.Utilisateur;



public class PageJeu extends Page{


	Partie partie;     /**< \brief La partie utilisée dans cette PageJeu */
	Menu menu;         /**< \brief Menu de sortie */

	
	/**
	 * \brief   Constructeur de PageJeu
	 * \param   f Le fichier de sauvegarde contenant la partie à charger
	 */
	public PageJeu(String f) {
		super("Jeu");
		this.partie = new Partie(f);
		this.menu = new Menu("Quitter la partie ?", new PageAccueil());
	}
	
	/**
	 * \param   largeur La largeur du damier
	 * \param   premier Le premier joueur
	 */   
	public PageJeu(int largeur, Joueur premier) {
		super("Jeu");
		this.partie = new Partie(largeur, premier);
		this.menu = new Menu("Quitter la partie ?", new PageAccueil());
	}
	
	
	/**
	 * Renvoie Application.j1 ou Application.j2
	 */
	private Utilisateur user(Joueur j){
		if (j == Joueur.J1)
			return Application.j1;
		else
			return Application.j2;
	}
	
	
	
	public Page executer_code()
	{
		Utilisateur aLuiDeJouer;
		boolean onJoue;
		int coords[];
		
		onJoue = true;
		while (onJoue){
			aLuiDeJouer = user(this.partie.aQuiDeJouer());
			
			System.out.println("C'est à " + aLuiDeJouer.getNom() + " de jouer.");
			this.partie.afficher();
		
			coords = aLuiDeJouer.jouer(this.partie);
			if (coords[0] == -1)
				onJoue = false;
			else
				this.partie.placerPion(coords[0], coords[1]);		
		}
		
		
		this.partie.libererMemoire();
		return this.menu.obtenirPage();
	}
}
