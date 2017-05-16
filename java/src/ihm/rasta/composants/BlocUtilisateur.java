/**
 * \class     ihm.rasta.composants.BlocUtilisateur
 * \brief     L'image et le nom de l'utilisateur
 * \author    Pierre Pomeret-Coquot
 * \date      3 mai
 */


package ihm.rasta.composants;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import noyau.*;
import ihm.rasta.*;
import ihm.rasta.apparences.*;
import cretinplay.Application;


public class BlocUtilisateur extends Bloc {
	
	private static final int DIM_X = 112;
	private static final int DIM_Y = 136;
	private static Texte texte;

	public BlocUtilisateur(Utilisateur u, int largeur, int hauteur){
		super(largeur, hauteur);
		
		int dx = largeur;
		int dy = DIM_Y * largeur / DIM_X;	
				
		int hBlocVide = (hauteur - dy - 30)/2;
		
		this.setLayout(new BoxLayout(this, BoxLayout.PAGE_AXIS));
		
		this.add(new Bloc(largeur, hBlocVide));
		this.add(new BlocImage(Fenetre.apparence.url(u), dx, dy));
		this.texte = new Texte("<b>"+u.getNom()+"</b>", JLabel.CENTER);
		this.texte.setPreferredSize(new Dimension(largeur, 30));
		this.add(this.texte);
		
		this.add(new Bloc(largeur, hBlocVide));
	}
	
	public void setApparence(Apparence apparence){
		this.texte.setApparence(apparence);
	}
}


