
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
	private BlocBoutons blocBoutons;

	CadreAccueil(Fenetre fenetre){
		super(fenetre);
		this.imageFond = new ImageIcon(Fenetre.apparence.url(Apparence.Image.LOGO)).getImage();

		this.setLayout(new BorderLayout());
		
		this.add(new Titre("cretinhex", this.fenetre.apparence), BorderLayout.NORTH);
		
		this.blocBoutons = new BlocBoutons(this.boutons);
		this.add(this.blocBoutons, BorderLayout.SOUTH);
		
		Bloc bloc;
		bloc = new BlocUtilisateur(Application.j1, 100, 500);
		bloc.setApparence(this.fenetre.apparence);		
		this.add(bloc, BorderLayout.WEST);
		
		bloc = new BlocUtilisateur(Application.j2, 100, 500);
		bloc.setApparence(this.fenetre.apparence);		
		this.add(bloc, BorderLayout.EAST);
		
	}
	
	public JButton getDefaultButton(){
		return this.boutons[0];
	}

	
	public void paintComponent(Graphics g){
		super.paintComponent(g);
		int dx = 400;
		int dy = 185;
		g.drawImage(this.imageFond, (this.getWidth() - dx) / 2, (this.getHeight() - dy) / 2, dx, dy, null);
	}
	
	


}
