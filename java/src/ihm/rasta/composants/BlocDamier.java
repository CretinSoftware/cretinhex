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
import ihm.rasta.apparences.Apparence;
import cretinplay.Application;


public class BlocDamier extends Bloc {

	public static double racine3 = 1.732;
	
	private static Color couleurs[];
	
	private CadreJeu parent;
	
	private Polygon hexagones[];
	
	private int largeurDamier;
	private Joueur damier[];
	
    private Point mouse = new Point();

	public BlocDamier(CadreJeu parent, Joueur damier[], int largeurDamier, int tailleX, int tailleY, Apparence apparence){
		super(tailleX, tailleY);
		
		
		/* Couleurs */
		this.couleurs = new Color[3];
		for (int i = 0; i < 3; ++i)
			this.couleurs[i] = apparence.couleur(Apparence.Couleur.fromInt(i));
		
		/* Hexagones */
		this.hexagones = new Polygon[(largeurDamier + 2) * (largeurDamier + 2)];
		this.parent = parent;
		
		this.largeurDamier = largeurDamier;
		this.damier = new Joueur[damier.length];
		for (int i = 0; i < damier.length; ++i)
			this.damier[i] = damier[i];
		
		if (this.parent != null){
			this.addMouseMotionListener(new MouseMotionAdapter() {
				public void mouseMoved(MouseEvent e) {
					mouse = e.getPoint();
					e.getComponent().repaint();
				}
			});
			this.addMouseListener(new MouseAdapter() {
				public void mousePressed(MouseEvent e) {
					mouse = e.getPoint();
					validerClic();
				}	
			});
		}
	}
	
	public void initHexagones(Graphics g){
		
		double tailleX = (double) this.getWidth();
		double tailleY = (double) this.getHeight();		
		double diam;
		double decalageX, decalageY;
		int indice;
		
		double nbCasesMiniX = (double) (this.largeurDamier + 2) * 1.5;
		double nbCasesMiniY = (double) (this.largeurDamier + 3) * 3.0 / 4.0;
		
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
		
		for (int i = 0; i < largeurDamier + 2; ++i){
			y = ((double) i * 3.0 / 4.0 + 0.5) * diam + decalageY;
			
			ys[0] = (int) (y - (diam / 2));
			ys[1] = (int) (y - (diam / 4));
			ys[2] = (int) (y + (diam / 4));
			ys[3] = (int) (y + (diam / 2));
			ys[4] = ys[2];
			ys[5] = ys[1];
			
			for (int j = 0; j < largeurDamier + 2; ++j){
				x = ((double) i * 0.5 + (double) j + 0.5) * diam * racine3 / 2.0 + decalageX;
				indice = i * (this.largeurDamier + 2) + j;
				
				xs[0] = (int) x;
				xs[1] = (int) (x + (diam * racine3 / 4));
				xs[2] = xs[1];
				xs[3] = xs[0];
				xs[4] = (int) (x - (diam * racine3 / 4));
				xs[5] = xs[4];
				
				this.hexagones[indice] = new Polygon(xs, ys, 6);
			}
		}
	}
		
		
	
	
	
	public void validerClic(){
		boolean trouve = false;
		for (int indice = 0; ! trouve && indice < this.hexagones.length; ++indice){
			if (this.hexagones[indice].contains(mouse)){
				trouve = true;
				this.parent.jouerEn(indice % (this.largeurDamier+2) - 1, indice / (this.largeurDamier+2) - 1);
			}
		}
	}
	
	
	
	
	public void paintComponent(Graphics g){
		int indiceDamier = 0;
		boolean bordGD, bordHB;
		this.initHexagones(g);
		
		Polygon polygone;
		
		for (int indice = 0; indice < this.hexagones.length; ++indice){
		
			polygone = this.hexagones[indice];
			
			bordHB = (indice / (this.largeurDamier + 2) == 0 || indice / (this.largeurDamier + 2) == this.largeurDamier + 1);
			bordGD = (indice % (this.largeurDamier + 2) == 0 || indice % (this.largeurDamier + 2) == this.largeurDamier + 1);
			
			if (bordHB && !bordGD)
				g.setColor(this.couleurs[1]);
			else if (bordGD && !bordHB)
				g.setColor(this.couleurs[2]);
			else if (!(bordGD || bordHB)){
				if (this.damier[indiceDamier] == Joueur.J0 && polygone.contains(mouse))
					g.setColor(new Color(200, 10, 10));
				else 
					g.setColor(this.couleurs[this.damier[indiceDamier].toInt()]);
				++indiceDamier;
			}
			
			if (!(bordGD && bordHB)){
				g.fillPolygon(polygone);
				if (!(bordGD || bordHB)){
					g.setColor(Color.black);
					g.drawPolygon(polygone);
				}
			}
		}
	}
}


