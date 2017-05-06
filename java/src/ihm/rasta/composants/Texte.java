/**
 * \class     ihm.rasta.composants.Texte
 * \brief     Affiche du texte html facilement
 * \author    Pierre Pomeret-Coquot
 * \date      3 mai
 */


package ihm.rasta.composants;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;


public class Texte extends JLabel {
	
	private boolean clicable;
	private String txt;
	
	public Texte(String txt){
		super(txt);
		this.init(false);
	}
	
	public Texte(String txt, int alignement){
		super(txt, alignement);
		this.init(false);
	}
	
	private void init(boolean clicable){
		this.setVerticalAlignment(JLabel.TOP);
		this.setOpaque(false);
		this.txt = this.getText();
		this.setHtmlText(this.txt);
		
	}
	
	private String enBleu(String txt){
		return "<b><u style=\"color: blue;\">" + this.txt + "</u></b>";
	}
	
	private String enRouge(String txt){
		return "<b><i><u style=\"color: red;\">" + this.txt + "</u></i></b>";
	}
	
	private void setHtmlText(String txt){
		this.setText("<html>" + txt + "</html>");
	}
	
}


