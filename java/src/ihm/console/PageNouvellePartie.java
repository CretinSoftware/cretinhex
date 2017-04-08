/**
 * \class    ihm.console.PageNouvellePartie
 * \author   François Mahé
 * \date     samedi 1er avril 2017
 */
package ihm.console;

import noyau.Joueur;
import cretinplay.Application;


public class PageNouvellePartie extends Page{

	public PageNouvellePartie() {
		super("Nouvelle partie");
	}
	
	public Page executer_code()
	{
		/* Largeur du damier */
		int largeur = new Menu("Largeur du damier").obtenirInt(0, 20);
		
		/* Premier joueur */
		Joueur premier = Joueur.fromInt(new Menu("Qui commence ?", Application.j1.getNom(), Application.j2.getNom()).obtenirInt());
		
		/* On renvoie la PageJeu */
		return new PageJeu(largeur, premier);
	}
}
