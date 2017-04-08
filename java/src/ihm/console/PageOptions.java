/**
 * \class    ihm.console.PageOptions
 * \author   Pierre Pomeret-Coquot
 * \date     samedi 1er avril 2017
 *
 * Permet de modifier le nom des joueurs
 * \todo     Permettre de choisir les joueurs Humains / IA
 */
package ihm.console;
import cretinplay.Application;
import noyau.Utilisateur;


public class PageOptions extends Page{

	public PageOptions() {
		super("Options");
	}
	
	public Page executer_code()
	{
		String str;
		
		str = new Menu("Nom du joueur 1").obtenirString();
		Application.j1.setNom(str);
		
		str = new Menu("Nom du joueur 2").obtenirString();
		Application.j2.setNom(str);
		
		
		return new PageAccueil();
	}
}
