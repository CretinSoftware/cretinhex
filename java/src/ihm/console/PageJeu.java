/**
 * 
 */
package ihm.console;
import noyau.Partie;
import noyau.Joueur;

/**
 * @author François
 *
 */
public class PageJeu extends Page{


	Partie partie;

	public PageJeu(String f) {
		super("Jeu");
		this.partie = new Partie(f);
	}

	public PageJeu(int largeur, Joueur premier) {
		super("Jeu");
		this.partie = new Partie(largeur, premier);
	}
	
	public Page executer_code()
	{
		System.out.println("C'est à " + this.partie.aQuiDeJouer() + " de jouer.");
		this.partie.afficher();
		
		
		this.partie.libererMemoire();
		
		return new PageAccueil();
	}
}
