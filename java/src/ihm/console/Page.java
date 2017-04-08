
package ihm.console;
import cretinplay.Application;
import java.io.IOException;

/**
 * \class     Page
 * \author    François Mahé
 * \date      samedi 1er avril
 *
 */
public abstract class Page implements InterfacePage{
	
	
	

	String titre; /**< \brief Le titre de la page */
	
	/**
	 * \brief    Construit une page
	 * \param    titre Le titre de la page
	 */
	public Page(String titre) 
	{
		this.titre = titre;
		if (this.titre.length()%2 == 1)
			this.titre += " ";
	}
	
	/**
	 * \brief    Donne le titre d'une page
	 */
	public String getTitre(){
		return this.titre;
	}
	
	/** \brief Longueur du titre */
	private int getTailleTitre()
	{
		return this.titre.length();
	}

	/** \todo   Ajouter une description */
	private void decaler()
	{
		for(int i = 0; i < ((Application.LARGEUR_ECRAN-this.getTailleTitre())/2)-1; i++)
			System.out.print(" ");
	}
	
	/** \todo   Ajouter une description */
	private void bordure()
	{
		for(int i = 0; i < Application.LARGEUR_ECRAN; i++ )
			System.out.print("*");
		System.out.println("");
	}
	
	public void afficher_titre() 
	{
		this.bordure();
		System.out.print("*");
		this.decaler();
		System.out.print(this.titre);
		this.decaler();
		System.out.println("*");
		this.bordure();
	}

	
	public void afficher_contenu()
	{
	}


	public void afficher_page() 
	{
		/* Efface la console :  */
		if (Application.SYSTEME.toUpperCase().equals("UNIX")){
		    System.out.print("\033[H\033[2J");  
		    System.out.flush();  
		}
		/* ne compile pas sous azteca. Version java ?
		else if (Application.SYSTEME.toUpperCase().equals("WINDOW")){
			 try {
				new ProcessBuilder("cmd", "/c", "cls").inheritIO().start().waitFor();
			} catch (InterruptedException | IOException e) {
				e.printStackTrace();
			}
		}
		*/
		else
			System.out.println("\n\n");
		
		
	    /* Affiche la page */
		this.afficher_titre();
		this.afficher_contenu();
	}

	
	public abstract Page executer_code();

}
