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
import ihm.rasta.apparences.Apparence;
import cretinplay.Application;


public class BlocInfoPartie extends Bloc {
	
	Bloc contenu;
	
	public BlocInfoPartie(Partie partie){
		super();
		this.init(partie);
	}
	public BlocInfoPartie(Partie partie, Apparence apparence){
		super();
		this.init(partie);
		this.setApparence(apparence);
	}
	
	private void init(Partie partie){
		Utilisateur u;
		
		this.setLayout(new BoxLayout(this, BoxLayout.PAGE_AXIS));
		
		Bloc tout;
		tout = new Bloc();
		tout.setLayout(new BoxLayout(tout, BoxLayout.PAGE_AXIS));
		tout.add(new Bloc(200, 150));
		
		this.contenu = new Bloc(200, 300);
		this.contenu.setLayout(new BoxLayout(this.contenu, BoxLayout.PAGE_AXIS));
		tout.add(this.contenu);
		tout.add(new Bloc(200, 150));
		
		
		
		
		if (partie.quiGagne() == Joueur.J0){
			
			u = Application.getUtilisateur(partie.aQuiDeJouer());
			
			this.contenu.add(new Texte("Partie en cours... <br />C'est actuellement le <i><b>tour " + partie.obtenirTour() + "</b></i>"));
			
			this.contenu.add(new JLabel(new ImageIcon(Fenetre.apparence.url(u))));
			this.contenu.add(new Texte("<b style=\"font-size: 2em; color; grey;\">C'est à <i>" + u.getNom() + "</i> !</b>"));
			
			if (u.getExistance().equals("humain"))
				this.contenu.add(new Texte("Cliquez sur la grille pour placer un pion !"));
			else
				this.contenu.add(new Texte("<i>Attendons que " + u.getNom() + " <br />prenne une décision :-)</i>"));
		
		}
		else {
		
			u = Application.getUtilisateur(partie.quiGagne());
			
			this.contenu.add(new Texte("Partie terminée... <br />Elle a duré <i><b>" + partie.obtenirTour() + " tours</b></i>"));
			
			this.contenu.add(new JLabel(new ImageIcon(Fenetre.apparence.url(u))));
			this.contenu.add(new Texte("<b style=\"font-size: 2em; color: red\">Gagnant : <i>" + u.getNom() + "</i> </b>"));
			
			this.contenu.add(new Texte("<i>Toutes nos félicitation à " + u.getNom() + "</i>"));
		}
		
		this.add(tout);
	}
	
	
	
	public void setApparence(Apparence apparence){
		this.contenu.setApparence(apparence);
	}
	
	
}


