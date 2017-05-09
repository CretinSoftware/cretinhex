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
import ihm.rasta.apparences.Apparence;

public class Dialogue extends JDialog {

	protected Fenetre parent;

	public Dialogue(Fenetre parent, String titre, boolean modal){
		super((JFrame) parent, titre, modal);
		this.setSize(500, 320);
		this.init(parent);
	}
	
	public Dialogue(Fenetre parent, String titre, boolean modal, int tailleX, int tailleY){
		super((JFrame) parent, titre, modal);
		this.setSize(tailleX, tailleY);
		this.init(parent);
	}
	
	private void init(Fenetre parent){
		this.parent = parent;
		this.centrer();
		
		JPanel tout = new Bloc(parent.apparence);
		tout.setLayout(new BorderLayout());
		this.setContentPane(tout);
	}
	
	protected void centrer(){
		this.setLocationRelativeTo(null);
		Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
		this.setLocation(dim.width/2 - this.getWidth()/2, dim.height/2 - this.getHeight()/2);
	}
	
	public String[] afficher(){	
		this.setVisible(true);
		return null;
	}
	
}
