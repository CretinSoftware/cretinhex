/**
 * \class     ihm.rasta.apparences.ApparenceClassic
 * \brief     L'apparence par défaut
 * \author    Pierre Pomeret-Coquot
 * \date      6 mai
 */


package ihm.rasta.apparences;

import noyau.Joueur;
import noyau.Utilisateur;

public class ApparenceClassic implements Apparence {


	private static final String LOGO      = "logo.png";
	private static final String FOND      = "fond.png";
	
	private static final String HUMAIN_J1 = "humain_1.png";
	private static final String HUMAIN_J2 = "humain_2.png";
	private static final String IA_J1     = "ia_1.png";
	private static final String IA_J2     = "ia_2.png";
	
	private static final String DOS_IMAGE = "../images/classic/";
	
	public String url(RefImage ref){
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
	
	
}
	
