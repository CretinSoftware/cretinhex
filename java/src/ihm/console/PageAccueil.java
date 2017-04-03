package ihm.console;

public class PageAccueil extends Page {

	private Menu menu;
	private String texte;
	
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
		return this.menu.obtenirPage();
	}

}
