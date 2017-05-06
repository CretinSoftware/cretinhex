
package ihm.rasta;
import ihm.rasta.composants.*;
import ihm.rasta.apparences.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

import noyau.Utilisateur;
import cretinplay.Application;

/**
 * \class     CadreAccueil
 * \brief     Conteneur de la page d'accueil
 * \author    Pierre Pomeret-Coquot
 * \date      3 mai
 */
 
public class CadreAccueil extends Cadre {

	private Bouton boutons[] = {
		new Bouton(this, Action.NOUVEAU),
		new Bouton(this, Action.OUVRIR),
		new Bouton(this, Action.OPT_JOUEURS),
		new Bouton(this, Action.QUITTER)
	};
	
	private Image imageFond;

	CadreAccueil(Fenetre fenetre){
		super(fenetre);
		this.imageFond = new ImageIcon(Fenetre.apparence.url(RefImage.LOGO)).getImage();

		this.setLayout(new BorderLayout());
		
		this.add(new Texte("<h1>cretinhex</h1>", JLabel.CENTER), BorderLayout.NORTH);
		
		this.add(new BlocBoutons(boutons), BorderLayout.SOUTH);
		
		this.add(new BlocUtilisateur(Application.j1, 100, 500), BorderLayout.WEST);
		
		this.add(new BlocUtilisateur(Application.j2, 100, 500), BorderLayout.EAST);
		
	}

	
	public void paintComponent(Graphics g){
		super.paintComponent(g);
		int dx = 400;
		int dy = 185;
		g.drawImage(this.imageFond, (this.getWidth() - dx) / 2, (this.getHeight() - dy) / 2, dx, dy, null);
	}
	
	


}
