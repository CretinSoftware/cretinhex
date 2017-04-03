package ihm;
import ihm.console.*;

public class IHMConsole implements IHM {

	// La liste des pages.
	
	
	
	public void play(){
		Page p = new PageAccueil();
		
		while (true)
		{
			p.afficher_page();
			p = p.executer_code();
		}
	}
	
	public int[] obtenirCoords(int taille){
		return new Menu("Que Jouer").obtenirCoords(taille);
	}

}
