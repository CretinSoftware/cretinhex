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
import noyau.*;


public class PageOptions extends Page{

	public PageOptions() {
		super("Options");
	}
	
	public Page executer_code()
	{
		String str;
		
		switch(new Menu("Quel existance pour le joueur 1 ?", "Humain", "Randombot", "GotooneBot", "Bridgebot").obtenirInt()){
			case 1:
				str = new Menu("Nom du joueur 1").obtenirString();
				Application.j1 = new Humain(str, Joueur.J1);
				break;
			case 2:
				Application.j1 = new IA0(Joueur.J1);
				break;
			case 3:
				Application.j1 = new Gotoonebot(Joueur.J1);
				break;
			case 4:
				Application.j1 = new BridgeBot(Joueur.J1);
				break;
			default:
				System.err.println("Un soucis dans le choix de l'IA...");
		}
		
		switch(new Menu("Quel existance pour le joueur 2 ?", "Humain", "Randombot", "GotooneBot", "Bridgebot").obtenirInt()){
			case 1:
				str = new Menu("Nom du joueur 1").obtenirString();
				Application.j2 = new Humain(str, Joueur.J2);
				break;
			case 2:
				Application.j2 = new IA0(Joueur.J2);
				break;
			case 3:
				Application.j2 = new Gotoonebot(Joueur.J2);
				break;
			case 4:
				Application.j2 = new BridgeBot(Joueur.J2);
				break;
			default:
				System.err.println("Un soucis dans le choix de l'IA...");
		}
		
		
		return new PageAccueil();
	}
}
