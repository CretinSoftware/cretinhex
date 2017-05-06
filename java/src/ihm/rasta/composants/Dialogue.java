/**
 * \class     ihm.rasta.composants.Dialogue
 * \brief     Dialogue vide, de base
 * \author    Pierre Pomeret-Coquot
 * \date      3 mai
 */


package ihm.rasta.composants;

import javax.swing.*;
import java.awt.*;
import ihm.rasta.Fenetre;

public class Dialogue extends JDialog {

	protected Fenetre parent;

	public Dialogue(Fenetre parent, String titre, boolean modal){
	
		super((JFrame) parent, titre, modal);
		
		this.parent = parent;
		
		this.setSize(500, 320);
		/*this.setResizable(false);*/
		
		this.setBackground(Fenetre.couleurBG);
		
		this.centrer();
		
	}
	
	protected void centrer(){
		this.setLocationRelativeTo(null);
		Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
		this.setLocation(dim.width/2 - this.getWidth()/2, dim.height/2 - this.getHeight()/2);
	}
	/*
	public String afficher(){	
		this.setVisible(true);
		return null;
	}
	*/
}
