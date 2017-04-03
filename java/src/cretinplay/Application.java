package cretinplay;
import ihm.*;
import noyau.*;

/**
 * @author François
 * @author Pierre
 *
 */
public class Application {


	public static IHM ihm = new IHMConsole();
	
	public static String SYSTEME = "Non spécifié";
	public static int LARGEUR_ECRAN = 80;
	
	public static Utilisateur j1;
	public static Utilisateur j2;


	
	
	/**
	 * Affiche l'usage des commandes et termine l'exécution du programme
	 */
	private static void erreurUsage(){
		System.err.println("Options autorisées : ");
		System.err.println("\t-l x (largeur de l'écran) ");
		System.err.println("\t-sys UNIX|Windows (quelques fioritures)");
		System.exit(1);
	}


	/**
	 * @param args Arguments (-l -sys)
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
		j1 = new Humain("Joueur 1", Joueur.J1);
		j2 = new Humain("Joueur 2", Joueur.J2);
		
		
		// Démarrage
		ihm.play();
		
		
		
	}

}
