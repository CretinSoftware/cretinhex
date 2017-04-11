package ihm;
import ihm.console.*;

/**
 * \class     IHMConsole
 * \brief     Affiche des "pages" en ligne de commande
 * \author    François Mahé
 * \author    Pierre Pomeret-Coquot
 * \date      samedi 1er avril
 *
 * \par   Description
 *   - La méthode play() est une astucieuse boucle affichant, page après page, le contenu sur le terminal.
 *   - La méthode obtenirCoords utilise simplement le menu implémenté dans ihm.console.Menu
 */
public class IHMConsole implements IHM {

	// La liste des pages.
	
	
	
	public void play(){
		Page p = new PageAccueil();
		
		while (true)
		{
			p.afficher_page();
			p = p.executer_code();
		}
	}
	
	public int[] obtenirCoords(int taille){
		return new Menu("Que Jouer").obtenirCoords(taille);
	}

}
