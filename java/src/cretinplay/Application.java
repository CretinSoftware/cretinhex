/**
 * \class   cretinplay.Application
 * \brief   Main + lecture de la commande passée
 * \author  Pierre Pomeret-Coquot
 * \date    samedi 1er avril 2017
 * 
 * \par     Description
 * Application eest la première classe appelée. Elle contient le main,
 * gère les paramètres passés en ligne de commande, et appelle la fonction
 * ihm.play() qui lance l'interface (ligne de commande, graphique, etc.)
 *
 */

package cretinplay;
import ihm.*;
import noyau.*;


public class Application {


	public static IHM ihm = new IHMConsole();       /**< \brief Interface utilisateur utilisée */
	public static Utilisateur j1;                   /**< \brief Caractériqtiques du joueur 1 */
	public static Utilisateur j2;                   /**< \brief Caractéristiques du joueur 2 */
	
	public static String SYSTEME = "Non spécifié";  /**< \brief Sysème d'exploitation sur lesuel tourne l'application */
	public static int LARGEUR_ECRAN = 80;           /**< \brief Largeur de l'écran en nombre de caractères */
	


	
	
	/**
	 * \brief Affiche l'usage des commandes et termine l'exécution du programme
	 */
	private static void erreurUsage(){
		System.err.println("Options autorisées : ");
		System.err.println("\t-ihm console|rasta ");
		System.err.println("\t-l x (largeur de l'écran) ");
		System.err.println("\t-sys UNIX|Windows (quelques fioritures)");
		System.exit(1);
	}


	/**
	 * \param args Arguments 
	 *         - -l x : largeur de x caractères pour l'ihm console
	 *         - -sys x : définit le système comme étant x (x=unix permet une fioriture pour l'affichage ihm console)
	 */
	
	public static void main(String[] args) 
	{
	
		int i = 0;
		
		/* Arguments ligne de commande */
		while (i < args.length)
		{
		
		
		
			// -sys unix ou -sys windows : quelques fioritures
			if(args[i].equals("-sys")){
				++i;
				if (args.length > i)
					Application.SYSTEME = args[i];
				else
					erreurUsage();
			}
		
			// -ihm console (par défaut) ou rasta ou encore d'autres...
			else if(args[i].equals("-ihm")){
				++i;
				if (args.length > i){
					if (args[i].toUpperCase().equals("RASTA"))
						Application.ihm = new IHMRasta();
					else if (args[i].toUpperCase().equals("CONSOLE"))
						Application.ihm = new IHMConsole();
					else
						erreurUsage();
				}
				else
					erreurUsage();
			}
			
						
			// -l 150 : la largeur de l'écran
			else if (args[i].equals("-l")){
				++i;
				if (args.length > i)
					Application.LARGEUR_ECRAN = Integer.parseInt(args[i]);
				else
					erreurUsage();
			}
			
			
			else {
				erreurUsage();
			}
			++i;
		}
		
		
		
		
		
		// Utilisateurs par défaut : deux humains
		j1 = new Humain("Joueur blanc", Joueur.J1);
		j2 = new Humain("Joueur noir",  Joueur.J2);
		
		
		// Démarrage
		ihm.play();
		
		
		
	}
	
	
	
	
	public static Utilisateur getUtilisateur(Joueur j){
		if (j == Joueur.J1)
			return j1;
		else
			return j2;
	}
	
	

}
