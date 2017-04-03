/**
 * 
 */
package ihm.console;

/**
 * @author Fran�ois
 *
 */
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
	
	//TODO : finir Page_sortie

}
