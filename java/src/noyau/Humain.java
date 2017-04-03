package noyau;
import cretinplay.Application;

public class Humain implements Utilisateur {


	private String nom;
	private Joueur j;

	public Humain(String nom, Joueur j){
		this.nom = nom;
		this.j = j;
	}


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
