package ihm.rasta.apparences;

/**
 * \class     ihm.rasta.apparences.ExtensionClassic
 * \brief     Apparence altérnative basée sur ApparenceClassic
 * \author    Pierre Pomeret-Coquot
 * \date      8 mai
 */

import noyau.Joueur;
import noyau.Utilisateur;
import java.awt.Color;

abstract class ExtensionClassic implements Apparence {
	
	private Apparence defaut;
	
	public ExtensionClassic(){
		this.defaut = new ApparenceClassic();
	}
	
	public String url(Apparence.Image ref){
		return this.defaut.url(ref);
	}
	
	public String url(Utilisateur u){
		String fichier;
		if (u.getExistance().equals("humain")){
			if (u.getJoueur() == Joueur.J1)
				return this.url(Apparence.Image.HUMAIN_J1);
			else 
				return this.url(Apparence.Image.HUMAIN_J2);
		}
		else {
			if (u.getJoueur() == Joueur.J1)
				return this.url(Apparence.Image.IA_J1);
			else 
				return this.url(Apparence.Image.IA_J2);
		}
	}
	
	public Color couleur(Apparence.Couleur ref){
		return this.defaut.couleur(ref);
	}
	
	public String aPropos(){
		return "";
	}
	
	public String [] nomJoueursParDefaut(){
		String renvoi[] = {"Joueur 1", "Joueur 2"};
		return renvoi;
	}
	
}
	
