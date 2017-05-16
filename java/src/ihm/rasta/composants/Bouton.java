/**
 * \class     ihm.rasta.composants.Bouton
 * \brief     Bouton simple
 * \author    Pierre Pomeret-Coquot
 * \date      3 mai
 */


package ihm.rasta.composants;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Bouton extends JButton implements MouseListener {

	private String txt;

	public Bouton(ActionListener actionListener, String txt){
		super(txt);
		this.txt = txt;
		this.addActionListener(actionListener);
		
		this.setPreferredSize(new Dimension(150, 27));
	}

	public Bouton(ActionListener actionListener, String txt, String actionCommand){
		super(txt);
		this.txt = txt;
		this.addActionListener(actionListener);
		this.setActionCommand(actionCommand);
		
		this.setPreferredSize(new Dimension(150, 27));
	}
	
	public String getTxt(){
		return this.txt;
	}


	//Méthode appelée lors du clic de souris
	public void mouseClicked(MouseEvent event) { }

	//Méthode appelée lors du survol de la souris
	public void mouseEntered(MouseEvent event) { }

	//Méthode appelée lorsque la souris sort de la zone du bouton
	public void mouseExited(MouseEvent event) { }

	//Méthode appelée lorsque l'on presse le bouton gauche de la souris
	public void mousePressed(MouseEvent event) { }

	//Méthode appelée lorsque l'on relâche le clic de souris
	public void mouseReleased(MouseEvent event) { }  
  
  
}


