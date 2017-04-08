/**
 * \class     noyau.Humain
 * \brief     L'humain qui est assis derrière l'écran...
 * \author    Pierre Pomeret-Coquot
 * \date      samedi 1er avril
 */
package noyau;
import cretinplay.Application;

public class Humain implements Utilisateur {


	private String nom;     /**< \brief Nom de l'humain */
	private Joueur j;       /**< \brief Joueur (i.e J1 ou J2) */


	/** \brief Constructeur d'après un nom et un joueur (J1 ou J2) */
	public Humain(String nom, Joueur j){
		this.nom = nom;
		this.j = j;
	}

	/**
	 * \note Appelle l'ihm pour obtenir de l'utilisateur la paire de coordonnées voulue)
	 */
	public int[] jouer(Partie p){
		return Application.ihm.obtenirCoords(p.largeurDamier());
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
