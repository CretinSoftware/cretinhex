/**
 * \class     ihm.rasta.composants.BlocDamier
 * \brief     Bloc dans lequel on dessine le damier
 * \author    Pierre Pomeret-Coquot
 * \date      6 mai
 */


package ihm.rasta.composants;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import noyau.*;
import ihm.rasta.*;
import cretinplay.Application;


public class BlocDamier extends Bloc {

	public static double racine3 = 1.732;
	
	private static Color couleurs[] = {
		new Color(128, 128, 128),
		new Color(192, 192, 192),
		new Color(64, 64, 64)
	};
	
	private int largeurDamier;
	private Joueur damier[];
	
    private Point mouse = new Point();

	public BlocDamier(Joueur damier[], int largeurDamier, int tailleX, int tailleY){
		super(tailleX, tailleY);
		
		this.largeurDamier = largeurDamier;
		this.damier = new Joueur[damier.length];
		for (int i = 0; i < damier.length; ++i)
			this.damier[i] = damier[i];
		
		this.addMouseMotionListener(new MouseMotionAdapter() {
            public void mouseMoved(MouseEvent e) {
                mouse = e.getPoint();
                e.getComponent().repaint();
            }
        });
	}
	
	public void paintComponent(Graphics g){
		double tailleX = (double) this.getWidth();
		double tailleY = (double) this.getHeight();		
		double diam;
		double decalageX, decalageY;
		int indice;
		Polygon polygone;
		
		
		double nbCasesMiniX = (double) (this.largeurDamier) * 1.5;
		double nbCasesMiniY = (double) (this.largeurDamier + 1) * 3.0 / 4.0;
		
		diam = tailleX * 2.0 / ( racine3 * nbCasesMiniX );
		decalageX = 0.0;
		decalageY = (tailleY - diam * nbCasesMiniY) / 2;
		
		if (diam > tailleY / nbCasesMiniY){
			diam = tailleY / nbCasesMiniY;
			decalageX = (tailleX - diam * nbCasesMiniX * racine3 / 2.0) / 2.0;
			decalageY = 0.0;
		}
			
		double x, y;
		int xs[] = new int[6];
		int ys[] = new int[6];
		
		for (int i = 0; i < largeurDamier; ++i){
			y = ((double) i * 3.0 / 4.0 + 0.5) * diam + decalageY;
			
			ys[0] = (int) (y - (diam / 2));
			ys[1] = (int) (y - (diam / 4));
			ys[2] = (int) (y + (diam / 4));
			ys[3] = (int) (y + (diam / 2));
			ys[4] = ys[2];
			ys[5] = ys[1];
			
			for (int j = 0; j < largeurDamier; ++j){
				x = ((double) i * 0.5 + (double) j + 0.5) * diam * racine3 / 2.0 + decalageX;
				indice = i * this.largeurDamier + j;
				
				xs[0] = (int) x;
				xs[1] = (int) (x + (diam * racine3 / 4));
				xs[2] = xs[1];
				xs[3] = xs[0];
				xs[4] = (int) (x - (diam * racine3 / 4));
				xs[5] = xs[4];
				
				polygone = new Polygon(xs, ys, 6);
				
				
				if (this.damier[indice] == Joueur.J0 && polygone.contains(mouse))
					g.setColor(new Color(200, 10, 10));
				else
					g.setColor(this.couleurs[this.damier[indice].toInt()]);
				g.fillPolygon(polygone);
				g.setColor(Color.black);
				g.drawPolygon(polygone);
			}
		}
	}
}


