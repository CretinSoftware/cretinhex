package ihm;
import ihm.rasta.Fenetre;
import ihm.rasta.Contenu;
import ihm.rasta.apparences.*;

/**
 * \class     IHMRasta
 * \brief     Interface graphique
 * \author    Pierre Pomeret-Coquot
 * \date      1er mai
 *
 */
 
 
public class IHMRasta implements IHM {

	/** \brief Palette d'image et de couleur pour l'affichage des éléments de la fenêtre */
	Apparence apparence;

	/** \brief Fenetre de l'application */
	public static Fenetre fenetre;
	
	/**
	 * \brief Instancie l'ihm par défaut (apparence Classic)
	 */
	public IHMRasta(){
		super();
		this.apparence = new ApparenceClassic();
	}
	
	
	/**
	 * \brief Instancie l'ihm avec une apparence donnée
	 * \param str Mnémonique indiquant l'apparence (palette d'image et de couleur)
	 */
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
