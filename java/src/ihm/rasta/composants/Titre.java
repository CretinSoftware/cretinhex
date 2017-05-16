/**
 * \class     ihm.rasta.composants.Titre
 * \brief     Affiche Un titre H1
 * \author    Pierre Pomeret-Coquot
 * \date      6 mai
 */


package ihm.rasta.composants;

import javax.swing.*;
import java.awt.*;
import ihm.rasta.apparences.Apparence;


public class Titre extends Texte {
	
	private String txt;
	private Apparence apparence;
	
	public Titre(String txt){
		super(txt, JLabel.CENTER);
		this.init(false);
	}
	
	public Titre(String txt, Apparence apparence){
		super(txt, JLabel.CENTER);
		this.init(false);
		this.setApparence(apparence);
	}
	
	private void init(boolean clicable){
		this.setVerticalAlignment(JLabel.TOP);
		this.setOpaque(false);
		this.txt = this.getHtmlText();
		super.setHtmlText("<h1>"+this.txt+"</h1>");
	}
	
	
	public void paintComponent(Graphics g){
		if (this.apparence == null)
			super.paintComponent(g);
		else {
			g.setColor(this.apparence.couleur(Apparence.Couleur.FOND));
			g.fillRect(0, 0, this.getWidth(), this.getHeight());
			super.paintComponent(g);
		}
	}
	
}


