/**
 * \class    ihm.console.PageAccueil
 * \author   François Mahé
 * \author   Pierre Pomeret-Coquot
 * \date     samedi 1er avril 2017
 */

package ihm.console;

public class PageAccueil extends Page {

	private Menu menu;       /**< \brief Menu de la page (i.e. redirections vers d'autres pages) */
	private String texte;    /**< \brief Contenu de la page */
	
	public PageAccueil(){
		super("HEX : cretinplay");
		this.texte = "Bien le bonjour !";
		this.menu = new Menu(
			"Que faire ?",
			new PageNouvellePartie(),
			new PageChargement(),
			new PageOptions(),
			new PageSortie()
		);
	}
	
	
	public void afficher_contenu(){
		System.out.println(this.texte + "\n");
	}
	
	public Page executer_code(){
		/* On se contente de renvoyer le choix de l'utilisateur */
		return this.menu.obtenirPage();
	}

}
