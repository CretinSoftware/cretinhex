/**
 * \class    ihm.console.PageChargement
 * \author   François Mahé
 * \date     samedi 1er avril 2017
 *
 * \todo     Cette page ne fonctionne pas !
 */
package ihm.console;

public class PageChargement extends Page{

	public PageChargement() {
		super("Chargement");
	}
	
	public Page executer_code()
	{
		String fichier;
		
		fichier = new Menu("Entrez le chemin du fichier de sauvegarde").obtenirString();
		return new PageJeu(fichier);
	}
}
