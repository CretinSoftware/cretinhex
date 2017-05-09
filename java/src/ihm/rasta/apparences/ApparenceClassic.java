/**
 * \class     ihm.rasta.apparences.ApparenceClassic
 * \brief     L'apparence par défaut
 * \author    Pierre Pomeret-Coquot
 * \date      6 mai
 */


package ihm.rasta.apparences;

import noyau.Joueur;
import noyau.Utilisateur;
import java.awt.Color;

public class ApparenceClassic implements Apparence {

	public  static final String[] NOM_JOUEURS_PAR_DEFAUT = {"Joueur blanc", "Joueur noir"};

	private static final String LOGO      = "logo.png";
	private static final String FOND      = "gray-texture-background.jpg";
	
	private static final String HUMAIN_J1 = "humain_1.png";
	private static final String HUMAIN_J2 = "humain_2.png";
	private static final String IA_J1     = "ia_1.png";
	private static final String IA_J2     = "ia_2.png";
	
	private static final String DOS_IMAGE = "../images/classic/";
	
	
	private static final Color COULEUR_1  = new Color(  0,   0,   0,   0);
	private static final Color COULEUR_2  = Color.black;
	private static final Color COULEUR_3  = Color.red; 
	
	private static final Color COULEUR_J0 = new Color(127, 127, 127);
	private static final Color COULEUR_J1 = new Color(223, 223, 223);
	private static final Color COULEUR_J2 = new Color( 31,  31,  31);
	
	public String url(Apparence.Image ref){
		String fichier = "";
		switch (ref){
			case LOGO:
				fichier = LOGO;
				break;
			case FOND:
				fichier = FOND;
				break;
				
			case HUMAIN_J1:
				fichier = HUMAIN_J1;
				break;
			case HUMAIN_J2:
				fichier = HUMAIN_J2;
				break;
			case IA_J1:
				fichier = IA_J1;
				break;
			case IA_J2:
				fichier = IA_J2;
				break;	
		}
		return DOS_IMAGE + fichier;
	}
	
	
	public String url(Utilisateur u){
		String fichier;
		if (u.getExistance().equals("humain")){
			if (u.getJoueur() == Joueur.J1)
				fichier = HUMAIN_J1;
			else 
				fichier = HUMAIN_J2;
		}
		else {
			if (u.getJoueur() == Joueur.J1)
				fichier = IA_J1;
			else 
				fichier = IA_J2;
		}
		return DOS_IMAGE + fichier;
	}
	
	
	
	
	public Color couleur(Apparence.Couleur ref){
		switch (ref){
			case J0:
				return COULEUR_J0;
			case J1:
				return COULEUR_J1;
			case J2:
				return COULEUR_J2;
			case FOND:
			case BOUTON:
				return COULEUR_1;
			case STRONG:
				return COULEUR_3;
			default:
				return COULEUR_2;
		}
	}
	
	public String [] nomJoueursParDefaut(){
		return this.NOM_JOUEURS_PAR_DEFAUT;
	}
	
	
	public String aPropos(){
		return "Thème <i>classic</i> proposé par Pierre Pomeret-Coquot.<br />Fond : http://www.publicdomainpictures.net/pictures/40000/velka/gray-texture-background.jpg";
	}
	
	
}
	
