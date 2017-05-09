/**
 * \class     ihm.rasta.composants.Texte
 * \brief     Affiche du texte html facilement
 * \author    Pierre Pomeret-Coquot
 * \date      3 mai
 */


package ihm.rasta.composants;

import javax.swing.*;
import java.awt.*;
import java.util.regex.*;
import ihm.rasta.apparences.Apparence;


public class Texte extends JLabel {
	
	private boolean clicable;
	private String txt;
	private Apparence apparence;
	
	public Texte(String txt){
		super(txt);
		this.init(false);
	}
	
	public Texte(String txt, int alignement){
		super(txt, alignement);
		this.init(false);
	}
	
	public Texte(String txt, Apparence apparence){
		super(txt);
		this.init(false);
		this.setApparence(apparence);
	}
	
	public Texte(String txt, int alignement, Apparence apparence){
		super(txt, alignement);
		this.init(false);
		this.setApparence(apparence);
	}
	
	private void init(boolean clicable){
		this.setVerticalAlignment(JLabel.TOP);
		this.setOpaque(false);
		this.txt = this.getHtmlText();
		this.setHtmlText(this.txt);
		
	}
	
	protected String enBleu(String txt){
		return "<b><u style=\"color: blue;\">" + this.txt + "</u></b>";
	}
	
	protected String enRouge(String txt){
		return "<b><i><u style=\"color: red;\">" + this.txt + "</u></i></b>";
	}
	
	protected void setHtmlText(String txt){
		this.setText("<html>" + txt + "</html>");
	}
	
	public String getHtmlText(){
		Pattern pattern = Pattern.compile("</?html>");
		Matcher matcher = pattern.matcher(super.getText());
		return matcher.replaceAll("");
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
			super.paintComponent(g);
		}
	}
	
}


