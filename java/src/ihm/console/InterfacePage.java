/**
 * 
 */
package ihm.console;

/**
 * \author    François Mahé
 * \date      15 mars
 *
 */
public interface InterfacePage
{
	
	/**
	 * \brief   Affiche le titre de la page
	 */
	public void afficher_titre();/*affiche le titre*/
	
	/**
	 * \brief   Affiche le contenu de la page
	 */
	public void afficher_contenu();/* affiche le contenu de la page*/
	
	/**
	 * \brief   Affiche la page (i.e. titre + contenu
	 */
	public void afficher_page();/* affiche une page */
	
	/**
	 * \brief   Execute un peu de code propre à la page.
	 */
	public Page executer_code();/* execute le code associ� a une page */
	
}
