/**
 * \class    ihm.console.PageJeu
 * \author   François Mahé
 * \date     samedi 1er avril 2017
 *
 * \todo     Faire / terminer la PageJeu
 */
package ihm.console;
import noyau.Partie;
import noyau.Joueur;



public class PageJeu extends Page{


	Partie partie;     /**< \brief La partie utilisée dans cette PageJeu */

	
	/**
	 * \brief   Constructeur de PageJeu
	 * \param   f Le fichier de sauvegarde contenant la partie à charger
	 */
	public PageJeu(String f) {
		super("Jeu");
		this.partie = new Partie(f);
	}
	
	/**
	 * \param   largeur La largeur du damier
	 * \param   premier Le premier joueur
	 */   
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
