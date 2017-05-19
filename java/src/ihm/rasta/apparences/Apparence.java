/**
 * \interface ihm.rasta.apparences.Apparence
 * \brief     Palette d'images et de couleurs pour l'application
 * \author    Pierre Pomeret-Coquot
 * \date      6 mai
 */
 
package ihm.rasta.apparences;

import noyau.Joueur;
import noyau.Utilisateur;
import java.awt.Color;

public interface Apparence {

	public enum Couleur {
		FOND,
		POLICE,
		STRONG,
		BOUTON,
		
		J0,
		J1,
		J2;
		
		
		public static Couleur fromJoueur(Joueur j){
			switch (j){
				case J1:
					return J1;
				case J2:
					return J2;
				default:
					return J0;
			}
		}
		
		public static Couleur fromInt(int i){
			return fromJoueur(Joueur.fromInt(i));
		}
	}
	
	
	public enum Image {
		LOGO,
		FOND,
	
		HUMAIN_J1,
		HUMAIN_J2,
		IA_J1,
		IA_J2;
	}
	
	public static final String[] NOM_JOUEURS_PAR_DEFAUT = null;

	/** \brief Chemin d'accès à une image */
	public String url(Apparence.Image ref);
	
	/** \brief Chemin d'accès à l'image d'un utilisateur */
	public String url(Utilisateur u);
	
	public Color couleur(Apparence.Couleur ref);
	
	public String[] nomJoueursParDefaut();
	
	public String aPropos();
	
	
}
	
