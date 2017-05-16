package ihm;
import ihm.rasta.Fenetre;
import ihm.rasta.Contenu;
import ihm.rasta.apparences.*;

/**
 * \class     IHMRasta
 * \brief     Premier essai d'interface graphique
 * \author    Pierre Pomeret-Coquot
 * \date      1er mai
 *
 */
 
 
public class IHMRasta implements IHM {

	Apparence apparence;

	public static Fenetre fenetre;
	
	public IHMRasta(){
		super();
		this.apparence = new ApparenceClassic();
	}
	
	public IHMRasta(String str){
		super();
		this.apparence = Contenu.Mod.fromString(str).toApparence();
	}
	
	public void play(){
		IHMRasta.fenetre = new Fenetre(this.apparence);		
	}
	
	public int[] obtenirCoords(int taille){
		return null;
	}

}
