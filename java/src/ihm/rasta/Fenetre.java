
package ihm.rasta;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.io.File;
import java.util.Random;

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
	
	
	private static Cadre CADRE_ACCUEIL;
	private static Cadre CADRE_NOUVELLE_PARTIE;
	private static Cadre CADRE_JEU;
	private static String idCadreActif;
	
	public static Color couleurBG = Color.white;
	public static Apparence apparence;
	
	private CardLayout cl;
	private JPanel contenu;
	
	private JMenu menuPartie;
	private JMenuItem menuItemAccueil, menuItemSauvegarder;
	
	
	/** \brief Constructeur de Fenetre */
	public Fenetre(){
	
		super("CretinHex");
		
		/* Apparence */
		apparence = new ApparenceClassic();
		
		/* Cadres et layout */
		CADRE_ACCUEIL         = new CadreAccueil(this);
		CADRE_NOUVELLE_PARTIE = new CadreNouvellePartie(this);
		CADRE_JEU             = new CadreJeu(this);
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
		ImageIcon ico = new ImageIcon(apparence.url(RefImage.LOGO));
		this.setIconImage(ico.getImage());
		
		/* Dimension + fenêtre centrée */		
		this.setSize(800, 600);
		Dimension dim = Toolkit.getDefaultToolkit().getScreenSize();
		this.setLocation(dim.width/2 - this.getWidth()/2, dim.height/2 - this.getHeight()/2);
		
		this.afficherCadre("accueil");
		
		/* Bien sûr */
		this.setVisible(true);
	}
	
	
	
	
	
	
	
	/* \brief Initialise les cadres et le layout */
	public void initCadres(){
		
		
		/* CardLayout : affichage du bon cadre */
		this.cl = new CardLayout();
		this.contenu = new JPanel();
		this.setContentPane(this.contenu);
		
		this.contenu.setLayout(cl);
		this.contenu.add(this.CADRE_ACCUEIL, "accueil");
		this.contenu.add(this.CADRE_NOUVELLE_PARTIE, "nvPartie");
		this.contenu.add(this.CADRE_JEU, "jeu");
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
		
		item = new JMenuItem("Annuler le mouvement");
		this.menuPartie.add(item);
		
		this.menuPartie.addSeparator();
		
		menuBar.add(this.menuPartie);
		
		
		/* Menu aide */
		menu = new JMenu("Aide");
		menu.setMnemonic('A');
		
		item = new JMenuItem("Aide");
		item.setMnemonic('A');
		item.setAccelerator(KeyStroke.getKeyStroke(KeyEvent.VK_H, KeyEvent.CTRL_MASK));
		item.setEnabled(false);
		menu.add(item);
		
		menu.addSeparator();
		
		item = new JMenuItem("À propos");
		item.setEnabled(false);
		menu.add(item);
		
		item = new JMenuItem("Support");
		item.setEnabled(false);
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
		this.rafraichirCadres();
	}
	
	void afficherCadre(String mnemo){
		if (mnemo.equals("jeu")){
			this.menuPartie.setEnabled(true);
			this.menuItemSauvegarder.setEnabled(true);
		}
		else {
			this.menuPartie.setEnabled(false);
			this.menuItemSauvegarder.setEnabled(false);
		}
		if (mnemo.equals("accueil")){
			this.menuItemAccueil.setEnabled(false);
		}
		else {
			this.menuItemAccueil.setEnabled(true);
		}
		this.idCadreActif = mnemo;
		this.getRootPane().setDefaultButton(this.getCadreActif().getDefaultButton());
		this.cl.show(this.contenu, mnemo);
		
		SwingUtilities.invokeLater(new Runnable() {
			public void run() {
				if (idCadreActif.equals("jeu"))
						((CadreJeu) getCadreActif()).demanderJouer();

			}
		});
		
	}
	
	Cadre getCadreActif(){
		if (this.idCadreActif.equals("nvPartie"))
			return this.CADRE_NOUVELLE_PARTIE;
		if (this.idCadreActif.equals("jeu"))
			return this.CADRE_JEU;
		if (this.idCadreActif.equals("accueil"))
			return this.CADRE_ACCUEIL;
		return null;
	}
	
	
	
	
	
	
	
	
	public void nouvellePartie(){
		afficherCadre("nvPartie");
	}
	
	public void chargerPartie(){
		JFileChooser dialogue = new JFileChooser(new File("../sauvegardes"));
		File fichier;
		if (dialogue.showOpenDialog(this) == JFileChooser.APPROVE_OPTION){
			fichier = dialogue.getSelectedFile();
			this.CADRE_JEU = new CadreJeu(this, fichier.getPath());
			this.rafraichirCadres();
			this.afficherCadre("jeu");
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
				
			if (tab[2].equals("Humain"))
				Application.j2 = new Humain(tab[3], Joueur.J2);
			else if (tab[2].equals("RandomBot"))
				Application.j2 = new IA0(Joueur.J2);
			else if (tab[2].equals("BridgeBot"))
				Application.j2 = new BridgeBot(Joueur.J2);
				
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
				this.afficherCadre("accueil");
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
				this.rafraichirCadres();
				this.afficherCadre("jeu");
				
			}
				
			/* Préférences Joueurs */
			else if (cmd.equals(Action.OPT_JOUEURS)){
				this.prefsJoueurs();
			}
		
		
		
		
			/* Apparence 'Classique' */
			else if (cmd.equals(Action.MOD_CLASSIC)){
				apparence = new ApparenceClassic();
				this.couleurBG = Color.white;
				this.redessinerCadres();
			}
		
			/* Apparence 'Rasta pouet' */
			else if (cmd.equals(Action.MOD_RASTA)){
				apparence = new ApparenceRasta();
				this.couleurBG = Color.yellow;
				this.redessinerCadres();
			}
		
		
		
			/* Par défaut : rien */
			else {
				System.out.println("Action " + cmd + " non gérée par la fenêtre");
				System.out.println("Action : " + e);
			}
		}
	}	
}
