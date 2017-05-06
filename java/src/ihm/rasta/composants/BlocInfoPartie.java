/**
 * \class     ihm.rasta.composants.BlocInfoPartie
 * \brief     Bloc contenant le numero de tour, à qui de jouer, etc.
 * \author    Pierre Pomeret-Coquot
 * \date      3 mai
 */


package ihm.rasta.composants;

import javax.swing.*;
import java.awt.*;
import noyau.*;
import ihm.rasta.*;
import cretinplay.Application;


public class BlocInfoPartie extends Bloc {
	
	public BlocInfoPartie(Partie partie){
		super();
		
		Utilisateur u;
		
		this.setLayout(new BoxLayout(this, BoxLayout.PAGE_AXIS));
		
		if (partie.quiGagne() == Joueur.J0){
			
			u = Application.getUtilisateur(partie.aQuiDeJouer());
			
			this.add(new Texte("Partie en cours... <br />C'est actuellement le <i><b>tour " + partie.obtenirTour() + "</b></i>"));
			
			this.add(new JLabel(new ImageIcon(Fenetre.apparence.url(u))));
			this.add(new Texte("<b style=\"font-size: 2em; color; grey;\">C'est à <i>" + u.getNom() + "</i> !</b>"));
			
			if (u.getExistance().equals("humain"))
				this.add(new Texte("Cliquez sur la grille pour placer un pion !"));
			else
				this.add(new Texte("<i>Attendons que " + u.getNom() + " <br />prenne une décision :-)</i>"));
		
		}
		else {
		
			u = Application.getUtilisateur(partie.quiGagne());
			
			this.add(new Texte("Partie terminée... <br />Elle a duré <i><b>" + partie.obtenirTour() + " tours</b></i>"));
			
			this.add(new JLabel(new ImageIcon(Fenetre.apparence.url(u))));
			this.add(new Texte("<b style=\"font-size: 2em; color: red\">Gagnant : <i>" + u.getNom() + "</i> </b>"));
			
			this.add(new Texte("<i>Toutes nos félicitation à " + u.getNom() + "</i>"));
		}
	}
}


