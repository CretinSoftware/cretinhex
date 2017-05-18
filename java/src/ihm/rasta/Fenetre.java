
package ihm.rasta;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.File;
import java.util.Random;
import java.util.concurrent.TimeUnit;

import cretinplay.Application;
import noyau.*;
import ihm.rasta.composants.*;
import ihm.rasta.apparences.*;


/**
 * \class     Fenetre
 * \brief     JFrame affichant l'application
 * \author    Pierre Pomeret-Coquot
 * \date      3 mai
 */
 
 
public class Fenetre extends JFrame implements ActionListener {


	
	public static class ThreadHisto extends Thread {
		private Fenetre fen;
		public ThreadHisto(String name, Fenetre fen){
			super(name);
			this.fen = fen;
		}
		public void run(){
			try {
				Thread.sleep(750);
				this.fen.redessinerCadres();
			}
			catch (Exception exception){
			}
		}
	}
	
	public static String MNEMO_ACC = "accueil";
	public static String MNEMO_NV  = "nvPartie";
	public static String MNEMO_JEU = "jeu";
	public static String MNEMO_HST = "histo";
	
	
	private static Cadre CADRE_ACCUEIL;
	private static Cadre CADRE_NOUVELLE_PARTIE;
	private static Cadre CADRE_JEU;
	private static Cadre CADRE_HISTO;
	private static String idCadreActif;
	
	public static Apparence apparence;
	
	private CardLayout cl;
	private JPanel contenu;
	
	private JMenu menuPartie;
	private JMenuItem menuItemAccueil, menuItemSauvegarder, menuItemHisto, menuItemAnnuler;
	
	
	/** \brief Constructeur de Fenetre */
	public Fenetre(){
		super("CretinHex");
		/* Apparence */
		this.apparence = new ApparenceRasta();
		this.init();
	}
	
	/** \brief Constructeur de Fenetre */
	public Fenetre(Apparence a){
		super("CretinHex");
		/* Apparence */
		this.apparence = a;
		this.init();
	}
	
	
	private void init(){
		
		
		/* Joueurs par défaut */
		String nomJoueurs[] = this.apparence.nomJoueursParDefaut();
		if (nomJoueurs != null){
			Application.j1.setNom(nomJoueurs[0]);
			Application.j2.setNom(nomJoueurs[1]);
		}
		
		/* Cadres et layout */
		CADRE_ACCUEIL         = new CadreAccueil(this);
		CADRE_NOUVELLE_PARTIE = new CadreNouvellePartie(this);
		CADRE_JEU             = new CadreJeu(this);
		CADRE_HISTO           = new CadreHisto(this);
		this.idCadreActif = "accueil";
		this.initCadres();
		
		/* Barre de menu */
		this.initMenuBar();
				
		/* Fermeture de la fenêtre */
		WindowListener l = new WindowAdapter() {
			public void windowClosing(WindowEvent e){
				System.exit(0);
			}
		};
		this.addWindowListener(l);
		this.setDefaultCloseOperation(WindowConstants.DISPOSE_ON_CLOSE);
			
		/* Icône de la barre de titre */
		ImageIcon ico = new ImageIcon(apparence.url(Apparence.Image.LOGO));
		this.setIconImage(ico.getImage());
		
		/* Dimension + fenêtre centrée */		
		this.setSize(800, 600);
		Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
		this.setLocation(dim.width/2 - this.getWidth()/2, dim.height/2 - this.getHeight()/2);
		
		this.afficherCadre("accueil");
		
		/* Bien sûr */
		this.setVisible(true);
		
		Component focused = this.getCadreActif().getFocused();
		if (focused != null)
			focused.requestFocusInWindow();
	}
	
	
	
	
	
	
	
	/* \brief Initialise les cadres et le layout */
	public void initCadres(){
		
		
		/* CardLayout : affichage du bon cadre */
		this.cl = new CardLayout();
		this.contenu = new JPanel();
		this.setContentPane(this.contenu);
		
		this.contenu.setLayout(cl);
		this.contenu.add(this.CADRE_ACCUEIL, MNEMO_ACC);
		this.contenu.add(this.CADRE_NOUVELLE_PARTIE, MNEMO_NV);
		this.contenu.add(this.CADRE_JEU, MNEMO_JEU);
		this.contenu.add(this.CADRE_HISTO, MNEMO_HST);
	}
	
	
	/* \brief Initialise la barre de menu */
	public void initMenuBar(){
	
		/* MenuBar */
		JMenuBar menuBar = new JMenuBar();
		JMenu menu, menu2, menu3;
		JMenuItem item;
		
		/* Menu application */
		menu = new JMenu("Cretinhex");
		menu.setMnemonic('C');

		item = new JMenuItem(Action.NOUVEAU);
		item.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_N, KeyEvent.CTRL_MASK)); 
		item.setMnemonic('N');
		item.addActionListener(this);
		menu.add(item);
		
		item = new JMenuItem("Ouvrir...");
		item.setActionCommand(Action.OUVRIR);
		item.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_O, KeyEvent.CTRL_MASK)); 
		item.setMnemonic('O');
		item.addActionListener(this);
		menu.add(item);
		
		menu.addSeparator();
		
		this.menuItemSauvegarder = new JMenuItem("Sauvegarder");
		this.menuItemSauvegarder.setEnabled(false);
		this.menuItemSauvegarder.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_S, KeyEvent.CTRL_MASK)); 
		this.menuItemSauvegarder.setMnemonic('S');
		this.menuItemSauvegarder.addActionListener(this);
		menu.add(this.menuItemSauvegarder);
		
		menu.addSeparator();
		
		menu2 = new JMenu("Préférences");
		menu2.setMnemonic('P');
		item = new JMenuItem(Action.OPT_JOUEURS);
		item.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_J, KeyEvent.CTRL_MASK));
		item.setMnemonic('J');
		item.addActionListener(this);
		menu2.add(item);
		menu3 = new JMenu("Apparence");
		menu3.setMnemonic('A');
		item = new JMenuItem(Action.MOD_CLASSIC);
		item.addActionListener(this);
		menu3.add(item);
		item = new JMenuItem(Action.MOD_RASTA);
		item.addActionListener(this);
		menu3.add(item);
		item = new JMenuItem(Action.MOD_ABEILLE);
		item.addActionListener(this);
		menu3.add(item);
		item = new JMenuItem(Action.MOD_LICORNE);
		item.setEnabled(false);
		item.addActionListener(this);
		menu3.add(item);
		menu2.add(menu3);
		menu.add(menu2);
		
		menu.addSeparator();
		
		this.menuItemAccueil = new JMenuItem(Action.ACCUEIL);
		this.menuItemAccueil.addActionListener(this);
		menu.add(this.menuItemAccueil);
		
		item = new JMenuItem(Action.QUITTER);
		item.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_Q, KeyEvent.CTRL_MASK));
		item.setMnemonic('Q'); 
		item.addActionListener(this);
		menu.add(item);
		
		menuBar.add(menu);
		
		
		/* Menu Partie */
		this.menuPartie = new JMenu("Partie");
		this.menuPartie.setMnemonic('P');
		this.menuPartie.setEnabled(false);
		
		this.menuItemAnnuler = new JMenuItem("Annuler un / plusieurs mouvement(s)");
		this.menuItemAnnuler.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_Z, KeyEvent.CTRL_MASK));
		this.menuItemAnnuler.setMnemonic('A');
		this.menuItemAnnuler.setActionCommand(Action.ANNULER);
		this.menuItemAnnuler.addActionListener(this);
		this.menuPartie.add(this.menuItemAnnuler);
		
		this.menuPartie.addSeparator();
		
		this.menuItemHisto = new JMenuItem("Historique");
		this.menuItemHisto.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_H, KeyEvent.CTRL_MASK));
		this.menuItemHisto.setMnemonic('H');
		this.menuItemHisto.addActionListener(this);
		this.menuPartie.add(this.menuItemHisto);
		
		menuBar.add(this.menuPartie);
		
		
		/* Menu aide */
		menu = new JMenu("Aide");
		menu.setMnemonic('A');
		
		item = new JMenuItem(Action.AIDE);
		item.addActionListener(this);
		item.setMnemonic('A');
		item.setAccelerator(KeyStroke.getKeyStroke("F1"));
		menu.add(item);
		
		menu.addSeparator();
		
		item = new JMenuItem(Action.A_PROPOS);
		item.addActionListener(this);
		menu.add(item);
		
		item = new JMenuItem(Action.SUPPORT);
		item.addActionListener(this);
		menu.add(item);
		
		menuBar.add(menu);
		
		this.setJMenuBar(menuBar);
		
	}
	
	
	
	
	
	
	void rafraichirCadres(){
		this.initCadres();
		this.afficherCadre(this.idCadreActif);
	}
	
	void redessinerCadres(){
		this.CADRE_NOUVELLE_PARTIE = new CadreNouvellePartie(this);
		this.CADRE_ACCUEIL = new CadreAccueil(this);
		this.CADRE_JEU = new CadreJeu((CadreJeu) this.CADRE_JEU);
		this.CADRE_HISTO = new CadreHisto((CadreHisto) this.CADRE_HISTO);
		this.rafraichirCadres();
	}
	
	void afficherCadre(String mnemo){
		
		if (mnemo.equals("jeu")){
			this.menuPartie.setEnabled(true);
			this.menuItemSauvegarder.setEnabled(true);
			if (((CadreJeu) this.CADRE_JEU).getTour() > 1){
				this.menuItemHisto.setEnabled(true);
				this.menuItemAnnuler.setEnabled(true);
			}
			else {
				this.menuItemHisto.setEnabled(false);
				this.menuItemAnnuler.setEnabled(false);
			}
			if (((CadreJeu) this.CADRE_JEU).partieTerminee())
				this.menuItemAnnuler.setEnabled(false);
		}
		else {
			this.menuPartie.setEnabled(false);
			this.menuItemSauvegarder.setEnabled(false);
		}
		
		if (mnemo.equals("accueil"))
			this.menuItemAccueil.setEnabled(false);
		else
			this.menuItemAccueil.setEnabled(true);
		
		this.idCadreActif = mnemo;
		this.getRootPane().setDefaultButton(this.getCadreActif().getDefaultButton());
		this.cl.show(this.contenu, mnemo);
		
		Component focused = this.getCadreActif().getFocused();
		if (focused != null)
			focused.requestFocusInWindow();
		
		SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				if (idCadreActif.equals(MNEMO_JEU))
						((CadreJeu) getCadreActif()).demanderJouer();

			}
		});
		
	}
	
	Cadre getCadre(String mnemo){
		if (mnemo.equals(MNEMO_NV))
			return this.CADRE_NOUVELLE_PARTIE;
		else if (mnemo.equals(MNEMO_JEU))
			return this.CADRE_JEU;
		else if (mnemo.equals(MNEMO_ACC))
			return this.CADRE_ACCUEIL;
		else if (mnemo.equals(MNEMO_HST))
			return this.CADRE_HISTO;
		else
			System.err.println("Pas de cadre dont le mnemo est '" + mnemo + "'");
		return null;
	}
	
	Cadre getCadreActif(){
		if (this.idCadreActif.equals(MNEMO_NV))
			return this.CADRE_NOUVELLE_PARTIE;
		else if (this.idCadreActif.equals(MNEMO_JEU))
			return this.CADRE_JEU;
		else if (this.idCadreActif.equals(MNEMO_ACC))
			return this.CADRE_ACCUEIL;
		else if (this.idCadreActif.equals(MNEMO_HST))
			return this.CADRE_HISTO;
		return null;
	}
	
	void setCadre(Cadre cadre, String mnemo){
		if (mnemo.equals(MNEMO_NV))
			this.CADRE_NOUVELLE_PARTIE = cadre;
		else if (mnemo.equals(MNEMO_JEU))
			this.CADRE_JEU = cadre;
		else if (mnemo.equals(MNEMO_ACC))
			this.CADRE_ACCUEIL = cadre;
		else if (mnemo.equals(MNEMO_HST))
			this.CADRE_HISTO = cadre;
		else
			System.err.println("Pas de cadre dont le mnemo est '" + mnemo + "'");
		this.redessinerCadres();
	}
	
	
	
	
	
	
	
	
	public void nouvellePartie(){
		afficherCadre(MNEMO_NV);
	}
	
	public void chargerPartie(){
		JFileChooser dialogue = new JFileChooser(new File("../sauvegardes"));
		File fichier;
		if (dialogue.showOpenDialog(this) == JFileChooser.APPROVE_OPTION){
			fichier = dialogue.getSelectedFile();
			this.CADRE_JEU = new CadreJeu(this, fichier.getPath());
			this.CADRE_HISTO = new CadreHisto(this);
			this.rafraichirCadres();
			this.afficherCadre(MNEMO_JEU);
		}
	}
	
	public void quitter(){
		JOptionPane jop = new JOptionPane();
		int option = jop.showConfirmDialog(null, "Voulez-vous réellement quitter ?", "Confirmation...", JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE);
		if (option == 0){
			option = jop.showConfirmDialog(null, "Avez-vous réellement voulu cliquer sur \"Oui\" ?", "Sur-confirmation...", JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE);
			if (option == 0){
				System.exit(0);
			}
		}
	}
	
	public void prefsJoueurs(){
	
		DialoguePrefsJoueurs dialogue = new DialoguePrefsJoueurs(this);
		
		String tab[] = dialogue.afficher();
		
		if (tab == null)
			System.out.println("Annulé");
		else {
			if (tab[0].equals("Humain"))
				Application.j1 = new Humain(tab[1], Joueur.J1);
			else if (tab[0].equals("RandomBot"))
				Application.j1 = new IA0(Joueur.J1);
			else if (tab[0].equals("BridgeBot"))
				Application.j1 = new BridgeBot(Joueur.J1);
			else if (tab[0].equals("GotooneBot"))
				Application.j1 = new Gotoonebot(Joueur.J1);
				
			if (tab[2].equals("Humain"))
				Application.j2 = new Humain(tab[3], Joueur.J2);
			else if (tab[2].equals("RandomBot"))
				Application.j2 = new IA0(Joueur.J2);
			else if (tab[2].equals("BridgeBot"))
				Application.j2 = new BridgeBot(Joueur.J2);
			else if (tab[2].equals("GotooneBot"))
				Application.j2 = new Gotoonebot(Joueur.J2);
				
			this.CADRE_ACCUEIL = new CadreAccueil(this);
			this.CADRE_NOUVELLE_PARTIE = new CadreNouvellePartie(this);
		}
		this.redessinerCadres();
	}
	
	
	
	
	
	
	
	
	
	public void actionPerformed(ActionEvent e) {
		String cmd = e.getActionCommand();
		Random rand = new Random();
		boolean executer;
		JOptionPane jop;
		
		String confirmation = this.getCadreActif().getConfirmation(cmd);
		
		if (confirmation == null){
			executer = true;
		}
		else {
			executer = false;
			jop = new JOptionPane();
			int option = jop.showConfirmDialog(null, "Voulez-vous vraiment réaliser l'action \"" + cmd + "\" ? \n" + confirmation, cmd, JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE);
			if (option == 0)
				executer = true;
		}
		
		
		if (executer){
		
			/* Quitter */
			if (cmd.equals(Action.QUITTER)){
				this.quitter();
			}
		
			/* Page principale */
			else if (cmd.equals(Action.ACCUEIL)){
				this.afficherCadre(MNEMO_ACC);
			}
		
			/* Charger */
			else if (cmd.equals(Action.OUVRIR)){
				this.chargerPartie();
			}
		
			/* Nouvelle partie : menu */
			else if (cmd.equals(Action.NOUVEAU)){
				this.nouvellePartie();
			}
		
			/* Nouvelle partie : démarrer */
			else if (cmd.equals(Action.JEU_NOUVEAU)){
				String options[] =  CADRE_NOUVELLE_PARTIE.getOptions();
				Joueur j;
				int largeur;
			
				if (options[0].equals("Joueur blanc"))
					j = Joueur.J1;
				else if (options[0].equals("Joueur noir"))
					j = Joueur.J2;
				else
					if (rand.nextInt() % 2 == 0)
						j = Joueur.J1;
					else
						j = Joueur.J2;
			
				largeur = Integer.parseInt(options[1]);
			
				this.CADRE_JEU = new CadreJeu(this, largeur, j);
				this.CADRE_HISTO = new CadreHisto(this);
				this.rafraichirCadres();
				this.afficherCadre(MNEMO_JEU);
				
			}
				
			/* Préférences Joueurs */
			else if (cmd.equals(Action.OPT_JOUEURS)){
				this.prefsJoueurs();
			}
			
			
			
			/* Annuler */
			else if (cmd.equals(Action.ANNULER)){
				this.CADRE_JEU.actionPerformed(e);
			}
			
			/* Sauvegarder */
			else if (cmd.equals(Action.SAUVEGARDER)){
				this.CADRE_JEU.actionPerformed(e);
			}
			
			/* Historique */
			else if (cmd.equals(Action.HISTORIQUE)){
				this.CADRE_JEU.actionPerformed(e);
			}
		
		
		
			/* Apparence 'Classique' */
			else if (cmd.equals(Action.MOD_CLASSIC)){
				apparence = new ApparenceClassic();
				this.redessinerCadres();
			}
		
			/* Apparence 'Rasta pouet' */
			else if (cmd.equals(Action.MOD_RASTA)){
				apparence = new ApparenceRasta();
				this.redessinerCadres();
			}
		
			/* Apparence 'Abeilles' */
			else if (cmd.equals(Action.MOD_ABEILLE)){
				apparence = new ApparenceAbeilles();
				this.redessinerCadres();
			}
		
			/* Apparence 'Licorne' */
			else if (cmd.equals(Action.MOD_LICORNE)){
				apparence = new ApparenceLicorne();
				this.redessinerCadres();
			}
			
			
			
			/* A propos */
			else if (cmd.equals(Action.A_PROPOS)){	
				DialogueInfo dialogue = new DialogueInfo(
					this, 
					"À propos", 
					true, 
					500, 
					400,
					new Texte(Contenu.A_PROPOS), 
					new Texte("<h2>Apparence</h2><p>" + this.apparence.aPropos() + "</p><br /><br />")
				);
				dialogue.afficher();
			}
			
			/* Support */
			else if (cmd.equals(Action.SUPPORT)){	
				DialogueInfo dialogue = new DialogueInfo(
					this, 
					"Support", 
					false, 
					500, 
					300,
					new Texte(Contenu.SUPPORT)
				);
				dialogue.afficher();
			}
			
			/* AIDE */
			else if (cmd.equals(Action.AIDE)){	
				DialogueInfo dialogue = new DialogueInfo(
					this, 
					"Aide", 
					false, 
					600, 
					450,
					new Texte(Contenu.AIDE)
				);
				dialogue.afficher();
			}
		
		
		
			/* Par défaut : rien */
			else {
				System.out.println("Action " + cmd + " non gérée par la fenêtre");
			}
		}
	}
	
}
