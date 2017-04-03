/**
 * 
 */
package ihm.console;

/**
 * @author François
 *
 */
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
