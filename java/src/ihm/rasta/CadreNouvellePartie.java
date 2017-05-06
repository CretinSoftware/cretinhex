/**
 * \class     ihm.rasta.CadreNouvellePartie
 * \brief     Menu de création de partie
 * \author    Pierre Pomeret-Coquot
 * \date      4 mai
 */



package ihm.rasta;
import ihm.rasta.composants.*;
import cretinplay.Application;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class CadreNouvellePartie extends Cadre {


	private JComboBox comboBox;
	private JTextField textField;
	private BlocBoutons blocBoutons;


	private Bouton boutons[] = {
		new Bouton(this, "Jouer", Action.JEU_NOUVEAU),
		new Bouton(this, "Retour", Action.ACCUEIL)
	};
	

	CadreNouvellePartie(Fenetre fenetre){
		super(fenetre);
		
		
		
		this.setLayout(new BorderLayout());
		
		this.add(new Texte("<h1>Nouvelle partie</h1>", JLabel.CENTER), BorderLayout.NORTH);
		
		this.blocBoutons = new BlocBoutons(this.boutons);
		this.add(this.blocBoutons, BorderLayout.SOUTH);
		/*this.fenetre.getRootPane().setDefaultButton(this.blocBoutons.getBt(1));*/
		
		JPanel tout, pan;
		Texte texte;

		tout = new Bloc();
		tout.setLayout(new BoxLayout(tout, BoxLayout.PAGE_AXIS));
		
		pan = new Bloc(500, 75);
		pan.add(new BlocImage(Fenetre.apparence.url(Application.j1), 56, 67));
		pan.add(new Texte(" <i>" + Application.j1.getNom() + "</i> VS <i>" + Application.j2.getNom() + "</i> "));
		pan.add(new BlocImage(Fenetre.apparence.url(Application.j2), 56, 67));
		
		tout.add(pan);
		
		/*tout.add(new BlocBoutons(new Bouton(this, "Modifier...", Action.OPT_JOUEURS)));*/
		
		pan = new Bloc(500, 50);
		texte = new Texte("Qui commence ? ", JLabel.RIGHT);
		texte.setPreferredSize(new Dimension(150, 25));
		texte.setVerticalAlignment(JLabel.CENTER);
		pan.add(texte);
		this.comboBox = new JComboBox();
		this.comboBox.addItem("Aléatoire");
		this.comboBox.addItem("Joueur blanc");
		this.comboBox.addItem("Joueur noir");
		this.comboBox.setPreferredSize(new Dimension(150, 25));
		pan.add(this.comboBox);
		
		tout.add(pan);
		
		pan = new Bloc(500, 50);
		texte = new Texte("Largeur du damier : ", JLabel.RIGHT);
		texte.setPreferredSize(new Dimension(150, 25));
		texte.setVerticalAlignment(JLabel.CENTER);
		pan.add(texte);
		this.textField = new JTextField("11");
		this.textField.setPreferredSize(new Dimension(150, 25));
		pan.add(this.textField);
		tout.add(pan);
		 
		
		pan = new Bloc(500, 350);
		tout.add(pan);
		
		
		
		this.add(tout, BorderLayout.CENTER);
		
	}
	
	public JButton getDefaultButton(){
		return this.blocBoutons.getBt(0);
	}
	
	public String[] getOptions(){
		String retour[] = new String[2];
		retour[0] = (String) this.comboBox.getSelectedItem();
		retour[1] = (String) this.textField.getText();
		return retour;
	}

}
