/**
 * \class    ihm.console.PageSortie
 * \author   François Mahé
 * \date     samedi 1er avril 2017
 */
package ihm.console;

public class PageSortie extends Page {

	public PageSortie() {
		super("Page de sortie");
	}
	
	public Page executer_code()
	{
		System.out.println("Au revoir...");
		System.exit(0);
		return null;
	}
}
