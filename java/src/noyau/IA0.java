/**
 * \class     noyau.Humain
 * \brief     L'humain qui est assis derrière l'écran...
 * \author    Pierre Pomeret-Coquot
 * \date      dimanche 2 avril 2017
 */
package noyau;
import cretinplay.Application;

public class IA0 implements Utilisateur {


	private String nom;     /**< \brief Nom de l'IA*/
	private Joueur j;       /**< \brief Joueur (i.e J1 ou J2) */
	
	
	static { System.loadLibrary("cretinhex_randombot"); }

	private native int[] randombotXjouer(int[] damier);

	/** \brief Constructeur d'après un nom et un joueur (J1 ou J2) */
	public IA0(String nom, Joueur j){
		this.nom = nom;
		this.j = j;
	}

	public int[] jouer(Partie p){
		int[] i = {-1, -1};
		return i;
	}
	
	public void actualiser(int x, int y){
	}


	public String getNom(){
		return this.nom;
	}
	
	public void setNom(String nom){
		this.nom = nom;
	}
	
}
