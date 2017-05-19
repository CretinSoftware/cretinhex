/**
 * \class     ihm.rasta.CadreHisto
 * \brief     Le cadre pour afficher l'historique
 * \author    Pierre Pomeret-Coquot
 * \date      7 mai
 */



package ihm.rasta;
import ihm.rasta.composants.*;
import cretinplay.Application;
import noyau.*;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.File;

public class CadreHisto extends Cadre {

	private Partie partie;
	private BlocDamier blocDamier;
	private BlocBoutons blocBoutons;
	private int tour;
	private boolean play;
	private Thread thread;
	
	private Bouton boutons[] = {
		new Bouton(this, Action.HISTO_DEB),
		new Bouton(this, Action.HISTO_PREC),
		new Bouton(this, Action.HISTO_PLAY),
		new Bouton(this, "Retour au jeu", Action.JEU_PARTIE),
		new Bouton(this, Action.HISTO_SUIV),
		new Bouton(this, Action.HISTO_FIN)
	};
	
	private String actionsAConfirmer[] = {
		Action.ACCUEIL,
		Action.QUITTER,
		Action.NOUVEAU,
		Action.OUVRIR
	};
	
	/** \brief Constructeur : cadre *vide* */
	public CadreHisto(Fenetre f){
		super(f);
		this.play = false;
	}

	/** \brief Constructeur : cadre d'après une partie ouverte */
	public CadreHisto (Fenetre f, Partie p){
		super(f);
		this.play = false;
		this.partie = p;
		this.tour = this.partie.obtenirTour();
		this.init();
	}

	/** \brief Constructeur : d'après lui-même */
	public CadreHisto (CadreHisto c){
		super(c.getFenetre());
		this.play = c.getPlay();
		if (c.getPartie() != null){
			this.tour = c.getTour();
			this.partie = c.getPartie();
			this.init();
		}
	}
	
	
	public void init(){
		this.setLayout(new BorderLayout());
		this.add(new Titre("Historique", this.fenetre.apparence), BorderLayout.NORTH);
		
		this.initBoutons();
		this.initCadres();
		
		if (this.play && this.tour < this.partie.obtenirTour())
			this.actionPerformed(new ActionEvent(this, 0, Action.HISTO_PLAY));	
	}
	
	public JButton getDefaultButton(){
		return this.boutons[3];
	}
	
	public void initBoutons(){
		
		this.boutons[0].setPreferredSize(new Dimension(60, 27));
		this.boutons[1].setPreferredSize(new Dimension(60, 27));
		this.boutons[4].setPreferredSize(new Dimension(60, 27));
		this.boutons[5].setPreferredSize(new Dimension(60, 27));
		
		this.boutons[1].setMnemonic(KeyEvent.VK_LEFT);
		this.boutons[4].setMnemonic(KeyEvent.VK_RIGHT);
		
		this.blocBoutons = new BlocBoutons(this.boutons);
		Bloc bloc = new Bloc();
		bloc.setLayout(new GridLayout(2,1));
		bloc.add(new Titre("Tour n°" + this.tour, this.fenetre.apparence));
		bloc.add(this.blocBoutons);
		this.add(bloc, BorderLayout.SOUTH);
	}
	
	public void initCadres(){		
		if (this.partie == null)
			this.add(new Texte("Pas de partie<br /><em>Vous n'auriez pas dû arriver là !</em>"), BorderLayout.CENTER);
		else {
		
			if (this.tour == 1){
				this.boutons[0].setEnabled(false);
				this.boutons[1].setEnabled(false);
			}
			else if (this.tour == this.partie.obtenirTour()){
				this.boutons[2].setEnabled(false);
				this.boutons[4].setEnabled(false);
				this.boutons[5].setEnabled(false);
			}
		
		
			this.initDamier();
		}
	}
	
	public void initDamier(){
		this.blocDamier = new BlocDamier(null, this.partie.obtenirDamierHisto(this.tour), this.partie.largeurDamier(), 500, 300, this.fenetre.apparence);
		
		this.add(this.blocDamier, BorderLayout.CENTER);
		this.add(new BlocInfoPartie(this.partie, this.fenetre.apparence), BorderLayout.EAST);
	}
	
	
	
	
	
	
	
	
	private int getTour(){
		return this.tour;
	}
	
	private Fenetre getFenetre(){
		return this.fenetre;
	}
	
	private Partie getPartie(){
		return this.partie;
	}
	
	private boolean getPlay(){
		return this.play;
	}
	
	
	
	
	
	public String getConfirmation(String action){
		return this.fenetre.getCadre(Fenetre.MNEMO_JEU).getConfirmation(action);
	}
	
	
	
	
	
	public void actionPerformed(ActionEvent e){
		String cmd = e.getActionCommand();
		String reponse;
		int nbTours;
		
		
		/* Retour jeu */
		if (cmd.equals(Action.JEU_PARTIE))
			this.fenetre.afficherCadre(Fenetre.MNEMO_JEU);
			
		/* Play */
		else if (cmd.equals(Action.HISTO_PLAY)){
			this.play = true;
			++ this.tour;
			this.thread = new Fenetre.ThreadHisto("Historique", this.fenetre);
			this.thread.start();
		}
			
		/* Début */
		else if (cmd.equals(Action.HISTO_DEB)){
			this.tour = 1;
			this.fenetre.redessinerCadres();
		}
			
		/* Précédent */
		else if (cmd.equals(Action.HISTO_PREC)){
			-- this.tour;
			this.fenetre.redessinerCadres();
		}
			
		/* Suivant */
		else if (cmd.equals(Action.HISTO_SUIV)){
			++ this.tour;
			this.fenetre.redessinerCadres();
		}
			
		/* Fin */
		else if (cmd.equals(Action.HISTO_FIN)){
			this.tour = this.partie.obtenirTour();
			this.fenetre.redessinerCadres();
		}
		
		/* Par défaut */
		else
			super.actionPerformed(e);
	}
	
	
	
	
	
}
