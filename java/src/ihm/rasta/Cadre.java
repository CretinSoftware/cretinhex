
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
		
		String url = Fenetre.apparence.url(Apparence.Image.FOND);
		if (url != null)
			this.imageFond = new ImageIcon(url).getImage();
		
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
	
	public Component getFocused(){
		return null;
	}
	
	public void paintComponent(Graphics g){
	
		/* Couleur de fond */
		g.setColor(this.fenetre.apparence.couleur(Apparence.Couleur.FOND));
		g.fillRect(0, 0, this.getWidth(), this.getHeight());
	
		/* Image de fond */
		if (this.imageFond != null)
			g.drawImage(this.imageFond, 0, 0, this.getWidth(), this.getHeight(), null);
	}

	public void actionPerformed(ActionEvent e) {
		this.fenetre.actionPerformed(e);
	}      
	

}
