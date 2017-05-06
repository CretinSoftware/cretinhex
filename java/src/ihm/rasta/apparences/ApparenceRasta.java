package ihm.rasta.apparences;

/**
 * \class     ihm.rasta.apparences.ApparenceRsasta
 * \brief     Apparence altérnative
 * \author    Pierre Pomeret-Coquot
 * \date      6 mai
 */

import noyau.Joueur;
import noyau.Utilisateur;

public class ApparenceRasta implements Apparence {


	private static final String FOND      = "fond.png";
	/*
	private static final String HUMAIN_J1 = "humain_1.png";
	private static final String HUMAIN_J2 = "humain_2.png";
	private static final String IA_J1     = "ia_1.png";
	private static final String IA_J2     = "ia_2.png";
	*/
	private static final String DOS_IMAGE = "../images/rasta/";
	
	private Apparence defaut;
	
	public ApparenceRasta(){
		this.defaut = new ApparenceClassic();
	}
	
	public String url(RefImage ref){
		String fichier = "";
		switch (ref){
			case FOND:
				fichier = FOND;
				break;
			/*
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
				break;	*/
			default:
				return this.defaut.url(ref);	
		}
		return DOS_IMAGE + fichier;
	}
	
	public String url(Utilisateur u){
		return this.defaut.url(u);
	}
	
	
}
	
