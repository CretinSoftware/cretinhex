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

public class ApparenceAbeilles extends ExtensionClassic {


	private static final String FOND      = "005.jpg";
	private static final String HUMAIN_J1 = "humain1.png";
	private static final String HUMAIN_J2 = "humain2.png";
	private static final String IA_J1     = "ia1.png";
	private static final String IA_J2     = "ia2.png";
	
	private static final String DOS_IMAGE = "../images/abeilles/";
	
	private static final Color C_BG       = new Color(255, 255,   0, 127);
	private static final Color C_J0       = new Color(255, 191,   0, 200);
	private static final Color C_J1       = new Color(255, 240,  20);
	private static final Color C_J2       = new Color(255,  63,  10);
	
	
	
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
				return C_BG;
			case J0:
				return C_J0;
			case J1:
				return C_J1;
			case J2:
				return C_J2;
			default:
				return super.couleur(ref);
		}
	}
	
	
	
	public String aPropos(){
		return "Jeu d'images proposé par Pierre Pomeret-Coquot." + 
		"<br />Fond d'écran : https://thegardendiaries.files.wordpress.com/2014/04/005.jpg" +
		"Icone des joueurs : https://pixabay.com/p-24633/";
	}
}
	
