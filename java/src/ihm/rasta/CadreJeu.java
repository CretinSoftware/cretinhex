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
		init();
	}

	CadreJeu(Fenetre fenetre, String fichier){
		super(fenetre);
		this.partie = new Partie(fichier);
		init();
	}

	CadreJeu(Fenetre fenetre, int largeur, Joueur joueur){
		super(fenetre);
		this.partie = new Partie(largeur, joueur);
		init();
	}
	
	CadreJeu(CadreJeu cadre){
		super(cadre.getFenetre());
		this.partie = cadre.getPartie();
		init();
	}
	
	
	
	public void init(){
		this.boutons[0].setEnabled(false);
		this.boutons[1].setEnabled(false);
		initCadres();
		
	}
	
	public void initCadres(){		
		this.setLayout(new BorderLayout());
		
		this.add(new Texte("<h1>Jeu !</h1>", JLabel.CENTER), BorderLayout.NORTH);
		
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
		this.add(new BlocDamier(this, this.partie.obtenirDamier(), this.partie.largeurDamier(), 500, 300), BorderLayout.CENTER);
		this.add(new BlocInfoPartie(this.partie), BorderLayout.EAST);
	}
	
	private Partie getPartie(){
		return this.partie;
	}
	
	private Fenetre getFenetre(){
		return this.fenetre;
	}
	
	public void jouerEn(int x, int y){
		//System.out.println("Jouer en " + x + "x" + y);
		if (this.partie.obtenirCase(x, y) == Joueur.J0){
			this.partie.placerPion(x, y);
			this.fenetre.redessinerCadres();
		}
	}
	
	public JButton getDefaultButton(){
		if (this.partie.quiGagne() == Joueur.J0)
			return null;
		return this.blocBoutons.getBt(2);
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
}
