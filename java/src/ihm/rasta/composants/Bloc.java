/**
 * \class     ihm.rasta.composants.Bloc
 * \brief     Un bloc simple, vide, transparent
 * \author    Pierre Pomeret-Coquot
 * \date      3 mai
 */


package ihm.rasta.composants;

import javax.swing.*;
import java.awt.*;
import ihm.rasta.apparences.Apparence;


public class Bloc extends JPanel {
	
	protected Apparence apparence;
	
	public Bloc(){
		super();
		this.setOpaque(false);
	}
	
	public Bloc(Apparence apparence){
		super();
		this.setOpaque(false);
		this.setApparence(apparence);
	}
	
	public Bloc(int tailleX, int tailleY){
		super();
		this.setOpaque(false);
		this.setPreferredSize(new Dimension(tailleX, tailleY));
	}
	
	public Bloc(int tailleX, int tailleY, Apparence apparence){
		super();
		this.setOpaque(false);
		this.setPreferredSize(new Dimension(tailleX, tailleY));
		this.setApparence(apparence);
	}
	
	public void setApparence(Apparence apparence){
		this.apparence = apparence;
	}
	
	public void paintComponent(Graphics g){
		if (this.apparence == null)
			super.paintComponent(g);
		else {
			g.setColor(this.apparence.couleur(Apparence.Couleur.FOND));
			g.fillRect(0, 0, this.getWidth(), this.getHeight());
		}
	}
}


