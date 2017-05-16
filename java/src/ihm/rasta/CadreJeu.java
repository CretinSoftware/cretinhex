/**
 * \class     ihm.rasta.CadreJeu
 * \brief     Le cadre pour jouer
 * \author    Pierre Pomeret-Coquot
 * \date      6 mai
 */



package ihm.rasta;
import ihm.rasta.composants.*;
import cretinplay.Application;
import noyau.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.File;

public class CadreJeu extends Cadre {

	private Partie partie;
	private BlocBoutons blocBoutons;
	
	private Bouton boutons[] = {
		new Bouton(this, Action.HISTORIQUE),
		new Bouton(this, Action.SAUVEGARDER),
		new Bouton(this, "Abandonner", Action.ACCUEIL)
	};
	
	private String actionsAConfirmer[] = {
		Action.ACCUEIL,
		Action.QUITTER,
		Action.NOUVEAU,
		Action.OUVRIR
	};

	CadreJeu(Fenetre fenetre){
		super(fenetre);
		this.partie = null;
	}

	CadreJeu(Fenetre fenetre, String fichier){
		super(fenetre);
		this.partie = new Partie(fichier);
		this.init();
	}

	CadreJeu(Fenetre fenetre, int largeur, Joueur joueur){
		super(fenetre);
		this.partie = new Partie(largeur, joueur);
		this.init();
	}
	
	CadreJeu(Fenetre f, Partie p){
		super(f);
		this.partie = p;
		this.init();
	}
	
	CadreJeu(CadreJeu cadre){
		super(cadre.getFenetre());
		this.partie = cadre.getPartie();
		if (this.partie != null)
			this.init();
	}
	
	
	
	public void init(){
		if (this.partie.obtenirTour() <= 1){
			this.boutons[0].setEnabled(false);
			this.boutons[1].setEnabled(false);
		}
		initCadres();
	}
	
	public void initCadres(){		
		this.setLayout(new BorderLayout());
		
		this.add(new Titre("Jeu !", this.fenetre.apparence), BorderLayout.NORTH);
		
		this.blocBoutons = new BlocBoutons(this.boutons);
		this.add(this.blocBoutons, BorderLayout.SOUTH);
		
		if (this.partie == null)
			this.add(new Texte("Pas de partie<br /><em>Vous n'auriez pas dû arriver là !</em>"), BorderLayout.CENTER);
		else {
			this.initDamier();
			if (this.partie.quiGagne() != Joueur.J0){
				Bouton btAccueil = this.blocBoutons.getBt(2);
				btAccueil.setText("Terminer");
			}
		}
	}
	
	public void initDamier(){
		this.add(new BlocDamier(this, this.partie.obtenirDamier(), this.partie.largeurDamier(), 500, 300, this.fenetre.apparence), BorderLayout.CENTER);
		this.add(new BlocInfoPartie(this.partie, this.fenetre.apparence), BorderLayout.EAST);
	}
	
	
	
	
	
	
	
	
	public int getTour(){
		return this.partie.obtenirTour();
	}
	
	public boolean partieTerminee(){
		return (this.partie.quiGagne() != Joueur.J0);
	}
		
	private Partie getPartie(){
		return this.partie;
	}
	
	private Fenetre getFenetre(){
		return this.fenetre;
	}
	
	public String [] actionsAConfirmer(){
		return this.actionsAConfirmer;
	}
	
	public void jouerEn(int x, int y){
		//System.out.println("Jouer en " + x + "x" + y);
		if (x >= 0 && x < this.partie.largeurDamier() && y >=0 && y < this.partie.largeurDamier())
			if (this.partie.quiGagne() == Joueur.J0)
				if (this.partie.obtenirCase(x, y) == Joueur.J0){
					this.partie.placerPion(x, y);
					this.fenetre.redessinerCadres();
				}
	}
	
	public void annulerMouvements(int nbTours){
		this.partie.annuler(nbTours);
		this.fenetre.redessinerCadres();
	}
	
	public JButton getDefaultButton(){
		if (this.partie.quiGagne() == Joueur.J0)
			return null;
		return this.boutons[2];
	}
	
	public void demanderJouer(){
	 	if (this.partie != null && this.partie.quiGagne() == Joueur.J0){
			int coords[] = Application.getUtilisateur(this.partie.aQuiDeJouer()).jouer(this.partie);
			if (coords != null)
				this.jouerEn(coords[0], coords[1]);
		}
	}
	
	
	public String getConfirmation(String action){
		if (this.partie.quiGagne() == Joueur.J0){
			boolean intercepter = false;
			for (int i = 0; !intercepter && i < this.actionsAConfirmer.length; ++i)
				if (this.actionsAConfirmer[i] == action)
					intercepter = true;
		
			if (intercepter)
				return "Toute partie non sauvegardée sera perdue.";
			else
				return null;
		}
		else
			return null;
	}
	
	
	
	
	
	
	
	public void actionPerformed(ActionEvent e){
		String cmd = e.getActionCommand();
		String reponse;
		int nbTours;
		
		
		/* Annuler */
		if (cmd.equals(Action.ANNULER)) {
			int max = this.getPartie().obtenirTour();
			JOptionPane jop = new JOptionPane(); 
		
			reponse = (String) jop.showInputDialog(
				null, 
				"Combien de mouvements annuler (max: " + (max-1) + ") ?", 
				"Annuler des mouvements", 
				JOptionPane.QUESTION_MESSAGE,
				null,
				null, 
				2
			);
			
			try {
				nbTours = Integer.parseInt(reponse);
			} 
			catch (Exception except) {
				nbTours = -1; 
			}
		
			if (nbTours <= 0 || nbTours >= max)
				new JOptionPane().showMessageDialog(
					null, 
					"Impossible d'annuler " + nbTours + " mouvement(s). Veuillez réessayer...", 
					"Annulation impossible", 
					JOptionPane.INFORMATION_MESSAGE
				);
			else
				this.annulerMouvements(nbTours);
		}
		
		
		/* Sauvegarder */
		else if (cmd.equals(Action.SAUVEGARDER)){
			System.out.println("sauv2");
			JFileChooser dialogue = new JFileChooser(new File("../sauvegardes"));
			File fichier;
			if (dialogue.showOpenDialog(this) == JFileChooser.APPROVE_OPTION){
				fichier = dialogue.getSelectedFile();
				this.partie.sauvegarder(fichier.getPath());
				new JOptionPane().showMessageDialog(
					null, 
					"La sauvegarde vers " + fichier.getName() + " s'est bien déoulée.", 
					"Sauvegarde OK", 
					JOptionPane.INFORMATION_MESSAGE
				);
			}
		}
		
		
		/* Historique */
		else if (cmd.equals(Action.HISTORIQUE)){
			this.fenetre.setCadre(new CadreHisto(this.fenetre, this.partie), Fenetre.MNEMO_HST);
			this.fenetre.afficherCadre(Fenetre.MNEMO_HST);
		}
		
		/* Par défaut */
		else
			super.actionPerformed(e);
	}
	
	
	
	
	
}
