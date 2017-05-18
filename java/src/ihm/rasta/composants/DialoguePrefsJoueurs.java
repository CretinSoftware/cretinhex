/**
 * \class     ihm.rasta.composants.DialoguePrefsJoueurs
 * \brief     Popup demandant l'existance et le nom des joueurs
 * \author    Pierre Pomeret-Coquot
 * \date      3 mai
 * \todo      Préselection du joueur actuel
 */


package ihm.rasta.composants;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import ihm.rasta.Fenetre;
import cretinplay.Application;
import noyau.*;

public class DialoguePrefsJoueurs extends Dialogue {


	private JComboBox existanceJ1, existanceJ2;
	private JTextField nomJ1, nomJ2;
	
	private String resultat[];

	public DialoguePrefsJoueurs(Fenetre parent){
		super(parent, "Préférences des joueurs", true);
		this.resultat = null;
		this.init();
	}
	
	private void init(){
		
		this.setSize(750, 200);
		this.centrer();
		
		
		
		
		JPanel tout, contenu, boutons, cadre, cadre2;
		JLabel label;
		
		tout = new JPanel();
		tout.setOpaque(false);
		tout.setPreferredSize(new Dimension(750, 200));
		tout.setLayout(new BoxLayout(tout, BoxLayout.PAGE_AXIS));
		
		contenu = new JPanel();
		contenu.setOpaque(false);
		contenu.setPreferredSize(new Dimension(750, 150));
		contenu.setLayout(new BoxLayout(contenu, BoxLayout.LINE_AXIS));
		
		

		
		/* Formulaire J1 */
		
		cadre = new JPanel();
		cadre.setPreferredSize(new Dimension(375, this.getHeight()));
		cadre.setOpaque(false);
		cadre.setBorder(BorderFactory.createTitledBorder("Joueur 1"));
		
		cadre2 = new Bloc(275, 30);
		cadre2.setLayout(new BoxLayout(cadre2, BoxLayout.LINE_AXIS));
		
		label = new JLabel("Type de joueur :");
		label.setPreferredSize(new Dimension(150, 50));
		cadre2.add(label);
		
		this.existanceJ1 = new JComboBox();
		this.existanceJ1.addItem("Humain");
		this.existanceJ1.addItem("RandomBot");
		this.existanceJ1.addItem("GotooneBot");
		this.existanceJ1.addItem("BridgeBot");
		this.existanceJ1.setPreferredSize(new Dimension(00, 50));
		if (Application.j1.getExistance().equals("ia0"))
			this.existanceJ1.setSelectedItem("RandomBot");
		else if (Application.j1.getExistance().equals("gotoone"))
			this.existanceJ1.setSelectedItem("GotooneBot");
		else if (Application.j1.getExistance().equals("bridgebot"))
			this.existanceJ1.setSelectedItem("BridgeBot");
		else
			this.existanceJ1.setSelectedItem("Humain");
		this.existanceJ1.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				if (existanceJ1.getSelectedItem().equals("Humain"))
					nomJ1.setEnabled(true);
				else
					nomJ1.setEnabled(false);
			}
		});
		cadre2.add(this.existanceJ1);
		
		cadre.add(cadre2);
		
		cadre2 = new Bloc(275, 30);
		cadre2.setLayout(new BoxLayout(cadre2, BoxLayout.LINE_AXIS));
		
		label = new JLabel("Nom du joueur :");
		label.setPreferredSize(new Dimension(150, 50));
		cadre2.add(label);
		
		this.nomJ1 = new JTextField(Application.j1.getNom());
		this.nomJ1.setPreferredSize(new Dimension(100, 50));
		cadre2.add(this.nomJ1);
		if (this.existanceJ1.getSelectedItem().equals("Humain"))
			this.nomJ1.setEnabled(true);
		else
			this.nomJ1.setEnabled(false);
		cadre.add(cadre2);
		
		contenu.add(cadre);
		
		

		/* Séparateur */

		contenu.add(new Bloc(50, this.getHeight()));
		
			
		
		/* Formulaire J2 */
		
		cadre = new JPanel();
		cadre.setPreferredSize(new Dimension(375, this.getHeight()));
		cadre.setOpaque(false);
		cadre.setBorder(BorderFactory.createTitledBorder("Joueur 2"));
		
		cadre2 = new Bloc(275, 30);
		cadre2.setLayout(new BoxLayout(cadre2, BoxLayout.LINE_AXIS));
		
		label = new JLabel("Type de joueur :");
		label.setPreferredSize(new Dimension(150, 50));
		cadre2.add(label);
		
		this.existanceJ2 = new JComboBox();
		this.existanceJ2.addItem("Humain");
		this.existanceJ2.addItem("RandomBot");
		this.existanceJ2.addItem("BridgeBot");
		this.existanceJ2.addItem("GotooneBot");
		this.existanceJ2.setPreferredSize(new Dimension(100, 50));
		if (Application.j2.getExistance().equals("ia0"))
			this.existanceJ2.setSelectedItem("RandomBot");
		else if (Application.j2.getExistance().equals("gotoone"))
			this.existanceJ2.setSelectedItem("GotooneBot");
		else if (Application.j2.getExistance().equals("bridgebot"))
			this.existanceJ2.setSelectedItem("BridgeBot");
		else
			this.existanceJ2.setSelectedItem("Humain");
		this.existanceJ2.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				if (existanceJ2.getSelectedItem().equals("Humain"))
					nomJ2.setEnabled(true);
				else
					nomJ2.setEnabled(false);
			}
		});
		cadre2.add(this.existanceJ2);
		
		cadre.add(cadre2);
		
		cadre2 = new Bloc(275, 30);
		cadre2.setLayout(new BoxLayout(cadre2, BoxLayout.LINE_AXIS));
		
		label = new JLabel("Nom du joueur :");
		label.setPreferredSize(new Dimension(150, 50));
		cadre2.add(label);
		
		this.nomJ2 = new JTextField(Application.j2.getNom());
		this.nomJ2.setPreferredSize(new Dimension(100, 50));
		if (this.existanceJ2.getSelectedItem().equals("Humain"))
			this.nomJ2.setEnabled(true);
		else
			this.nomJ2.setEnabled(false);
		cadre2.add(this.nomJ2);
		cadre.add(cadre2);
		
		contenu.add(cadre);
		
		tout.add(contenu);
		
		
		
		/* Boutons Annuler et OK */
		
		boutons = new JPanel();
		boutons.setPreferredSize(new Dimension(750, 50));
		
		Bouton btOK = new Bouton(null, "OK");
		this.getRootPane().setDefaultButton(btOK);
		btOK.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent arg0){
				resultat = new String[4];
				resultat[0] = (String) existanceJ1.getSelectedItem();
				resultat[1] = (String) nomJ1.getText();
				resultat[2] = (String) existanceJ2.getSelectedItem();
				resultat[3] = (String) nomJ2.getText();		
				setVisible(false);		
			}
		});
		boutons.add(btOK);
		
		Bouton btAnnuler = new Bouton(null, "Annuler");
		btAnnuler.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent arg0){
				resultat = null;
				setVisible(false);
			}
		});
		
		boutons.add(btAnnuler);
		tout.add(boutons);
		
		this.getContentPane().add(tout);
	}
	
	
	
	public String[] afficher(){	
		this.setVisible(true);
		parent.initCadres();
		return this.resultat;
	}	
}
