package ihm.rasta.apparences;

/**
 * \class     ihm.rasta.apparences.ApparenceRsasta
 * \brief     Apparence altérnative
 * \author    Pierre Pomeret-Coquot
 * \date      6 mai
 */

import noyau.Joueur;
import noyau.Utilisateur;
import java.awt.Color;

public class ApparenceRasta extends ExtensionClassic {


	private static final String FOND      = "rasta-1915004_1280.jpg";
	private static final String HUMAIN_J1 = "humain1.png";
	private static final String HUMAIN_J2 = "humain2.png";
	private static final String IA_J1     = "ia1.png";
	private static final String IA_J2     = "ia2.png";

	private static final String DOS_IMAGE = "../images/rasta/";
	
	private static final Color COULEUR_1  = new Color(240, 210, 150, 128);
	private static final Color COULEUR_2  = Color.black;
	private static final Color COULEUR_3  = Color.red; 
	private static final Color COULEUR_J0 = new Color(140,  40,  20, 128); 
	private static final Color COULEUR_J1 = new Color( 60, 150,  40);
	private static final Color COULEUR_J2 = new Color(240, 200,  20);
	
	
	public String url(Apparence.Image ref){
		String fichier = "";
		switch (ref){
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
			default:
				return super.url(ref);	
		}
		return DOS_IMAGE + fichier;
	}
	
	public Color couleur(Apparence.Couleur ref){
		switch (ref){
			case FOND:
				return COULEUR_1;
			case STRONG:
				return COULEUR_3;
			case J0:
				return COULEUR_J0;
			case J1:
				return COULEUR_J1;
			case J2:
				return COULEUR_J2;
			default:
				return super.couleur(ref);
		}
	}
	
	public String[] nomJoueursParDefaut(){
		String[] renvoi = {"Joueur vert", "Joueur jaune"};
		return renvoi;
	}
	
	
	
	public String aPropos(){
		return "Apparence <i>Rasta-pouet</i> proposé par Pierre Pomeret-Coquot.\n Fond : https://pixabay.com/p-1915004/";
	}
	
	
}
	
