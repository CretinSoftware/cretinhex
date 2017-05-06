package ihm;
import ihm.rasta.*;

/**
 * \class     IHMRasta
 * \brief     Premier essai d'interface graphique
 * \author    Pierre Pomeret-Coquot
 * \date      1er mai
 *
 */
 
 
public class IHMRasta implements IHM {


	public static Fenetre fenetre;
	
	
	public void play(){
		IHMRasta.fenetre = new Fenetre();		
	}
	
	public int[] obtenirCoords(int taille){
		int xy[] = new int[2];
		xy[0] = -1;
		xy[1] = -1;
		return xy;
	}

}
