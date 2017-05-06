
package ihm.rasta;
import ihm.rasta.apparences.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

/**
 * \class     Cadre
 * \brief     Conteneur JPanel pour les différentes vues de l'application
 * \author    Pierre Pomeret-Coquot
 * \date      2 mai
 */
 
public abstract class Cadre extends JPanel implements ActionListener {

	protected Image imageFond;
	protected Fenetre fenetre;

	Cadre(Fenetre fenetre){
		super();
		this.fenetre = fenetre;
		this.imageFond = new ImageIcon(Fenetre.apparence.url(RefImage.FOND)).getImage();
	}
	
	public String[] getOptions(){
		return null;
	}
	
	public String getConfirmation(String action){
		return null;
	}
	
	public JButton getDefaultButton(){
		return null;
	}
	
	public void paintComponent(Graphics g){
		/* Image de fond */
		g.drawImage(this.imageFond, 0, 0, this.getWidth(), this.getHeight(), null);
	}

	public void actionPerformed(ActionEvent e) {
		this.fenetre.actionPerformed(e);
	}      
	

}
