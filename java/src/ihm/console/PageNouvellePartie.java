/**
 * 
 */
package ihm.console;

import noyau.Joueur;
import cretinplay.Application;

/**
 * @author François
 *
 */
public class PageNouvellePartie extends Page{

	public PageNouvellePartie() {
		super("Nouvelle partie");
	}
	
	public Page executer_code()
	{
		int largeur = new Menu("Largeur du damier").obtenirInt(0, 20);
		
		Joueur premier = Joueur.fromInt(new Menu("Qui commence ?", Application.j1.getNom(), Application.j2.getNom()).obtenirInt());
		
		return new PageJeu(largeur, premier);
	}
}
