/**
 * \class     ihm.rasta.composants.BlocImage
 * \brief     Une image dans un bloc
 * \author    Pierre Pomeret-Coquot
 * \date      3 mai
 */


package ihm.rasta.composants;

import javax.swing.*;
import java.awt.*;
import noyau.*;
import ihm.rasta.*;
import cretinplay.Application;


public class BlocImage extends Bloc {
	
	private Image image;
	private int tailleX, tailleY;
	
	public BlocImage(String fichier, int tailleX, int tailleY){
		super(tailleX, tailleY);
		this.image = new ImageIcon(fichier).getImage();
		this.tailleX = tailleX;
		this.tailleY = tailleY;
	}

	
	public void paintComponent(Graphics g){
		super.paintComponent(g);
		
		Utilisateur u;
		String img;
		
		g.drawImage(this.image, 0, 0, tailleX, tailleY, null);
	}
	
}


