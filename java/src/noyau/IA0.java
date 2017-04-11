/**
 * \class     noyau.IA0
 * \brief     IA qui joue au hasard.
 * \author    Pierre Pomeret-Coquot
 * \date      dimanche 2 avril 2017
 */
package noyau;
import cretinplay.Application;

public class IA0 implements Utilisateur {


	private String nom;     /**< \brief Nom de l'IA*/	
	
	static { System.loadLibrary("cretinhex_randombot"); }

	private native int[] randombotXjouer(int[] damier, int tailleDamier);
	private native void randombotXinit();

	/** \brief Constructeur d'après un nom et un joueur (J1 ou J2) */
	public IA0(){
		this.nom = "RandomBot";
		randombotXinit();
	}

	public int[] jouer(Partie p){
		int[] i = {-1, -1};
		return i;
	}
	
	public void actualiser(int x, int y){
	}
	
	public void quitter(){
	}


	public String getNom(){
		return this.nom;
	}
	
	public void setNom(String nom){
		this.nom = nom;
	}
	
}
