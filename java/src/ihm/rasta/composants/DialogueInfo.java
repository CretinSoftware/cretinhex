/**
 * \class     ihm.rasta.composants.DialogueInfo
 * \brief     Dialogue contenant un message d'information et un bouton pour sortir.
 * \author    Pierre Pomeret-Coquot
 * \date      7 mai
 */


package ihm.rasta.composants;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import ihm.rasta.Fenetre;

public class DialogueInfo extends Dialogue {

	public DialogueInfo(Fenetre parent, String titre, boolean modal, Texte... textes){
		super(parent, titre, modal);
		this.init(textes);
	}
	
	public DialogueInfo(Fenetre parent, String titre, boolean modal, int tailleX, int tailleY, Texte... textes){
		super(parent, titre, modal, tailleX, tailleY);
		this.init(textes);
	}
	
	private void init(Texte... textes){		
		JPanel contenu ;
		
		contenu = new JPanel();
		contenu.setOpaque(false);
		contenu.setLayout(new BoxLayout(contenu, BoxLayout.PAGE_AXIS));
		
		for (int i = 0; i < textes.length; ++i)
			contenu.add(textes[i]);
		
		this.getContentPane().add(contenu, BorderLayout.CENTER);
		
		Bouton btOK = new Bouton(null, "OK");
		btOK.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e){
				setVisible(false);
			}
		});
		this.getRootPane().setDefaultButton(btOK);
		this.getContentPane().add(new BlocBoutons(btOK), BorderLayout.SOUTH);
		
	}
}
