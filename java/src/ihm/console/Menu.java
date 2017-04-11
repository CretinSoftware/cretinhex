package ihm.console;


import cretinplay.Application;
import java.util.Arrays;
import java.util.Scanner;

/**
 * Affiche un menu et récupère le choix de l'utilisateur
 * @author Pierre
 *
 */
public class Menu 
{
	private String question;                        /**< \brief La question qui est donc le titre du menu */
	private String[] reponses;                      /**< \brief La liste des solutions, au format texte */
	private Page[] redirections;                    /**< \brief La liste des redirections, pour une menu de page \todo Faut-il plutôt une classe fille ? */
	
	private Scanner scan = new Scanner(System.in);  /**< \brief L'outil pour lire les réponses de l'utilisateur */
	
	
	
	/**
	 * Constructeur de menu
	 * 
	 * La première phrase est la question posée.
	 * Les suivantes, si présentes, seront affichées comme des propositions précédées d'un nombre
	 * @{
	 */
	 
	/**
	 * \brief    Menu sans propositions
	 * \param    question La question qui sera posée
	 */
	public Menu (String question)
	{
		this.question = question;
		this.reponses = new String[0];
		this.redirections = new Page[0];
	}
	
	/**
	 * \brief    Menu avec propositions
	 * \param    question La question qui sera posée
	 * \param    reponses La liste des réponses possibles
	 */
	public Menu (String question, String... reponses)
	{
		this.question = question;
		this.reponses = Arrays.copyOf(reponses, reponses.length);
	}
	
	/**
	 * \brief    Menu de page avec propositions
	 * \param    question      La question qui sera posée
	 * \param    redirections  La liste des redirection (pages) possibles
	 */
	public Menu(String question, Page... redirections){
		this.question = question;
		this.redirections = Arrays.copyOf(redirections, redirections.length);
		this.reponses = new String[redirections.length];
		for (int i = 0; i < redirections.length; ++i)
			this.reponses[i] = this.redirections[i].getTitre();
	}
	
	
	
	/**
	 * Affiche le menu et les éventuelles propositions
	 */
	public void afficher()
	{
		if (this.reponses.length > 0)
		{
			System.out.println(this.question);
			for (int i = 1; i <= this.reponses.length; ++i)
				System.out.println(" " + i + " : " + this.reponses[i-1]);
			System.out.print("Votre choix : ");
		}
		else
			System.out.print(this.question + " : ");
	}

	
	/**
	 * Affiche le menu et récupère une chaîne de caractère
	 * @return La chaîne tapée par l'utilisateur
	 */
	public String obtenirString()
	{ 
		this.afficher();
		return scan.nextLine();
	}

	
	/**
	 * Affiche le menu et récupère un entier
	 * @return L'entier tapé par l'utilisateur
	 * 
	 * En cas de choix multiple, la valeur est contrainte à ces choix
	 */
	public int obtenirInt()
	{ 
		if (this.reponses.length > 0)
			return this.obtenirInt(1, this.reponses.length);
		
		int i = 0;
		boolean ok = false;
		while (!ok)
		{
			this.afficher();
			if (scan.hasNextInt())
			{
				i = scan.nextInt();
				ok = true;
			}
			else
				System.out.println("Merci d'entrer une valeur entière");
			scan.nextLine();
		}
		return i;
	}

	
	/**
	 * Affiche le menu et récupère un entier compris entre min et max
	 * @param min le minimum accepté (inclus)
	 * @param max le maximum accepté (inclus)
	 * @return L'entier tapé par l'utilisateur
	 */
	public int obtenirInt(int min, int max)
	{ 
		int i = 0;
		boolean ok = false;
		while (!ok){
			this.afficher();
			if (scan.hasNextInt())
			{
				i = scan.nextInt();
				ok = (i >= min && i <= max);
			}
			scan.nextLine();
			if (!ok)
				System.out.println("Merci d'entrer une valeur entière entre " + min + " et " + max);
		}
		return i;
	}
	
	/**
	 * Renvoie un couple (x,y) numéroté à partir de 0
	 * ex : renvoie (2,0) si l'utilisateur rentre A3 (3->2 et A->0)
	 * et renvoie (-1,-1) si l'utilisateur tape 0
	 * @param taille taille du damier
	 * @return (x,y) ou (-1,-1)
	 * @todo Faire le coup du -1... ou pas !
	 */
	public int[] obtenirCoords(int taille){
		int[] coords = new int[2];
		boolean ok = false;
		while (!ok){
			String str = this.obtenirString().toUpperCase();
			char c = str.charAt(0);
			
			if (str.equals("0")){
				coords[0] = -1;
				coords[1] = -1;
				ok = true;
			}
			else if (c >= 'A' && c <= 'Z'){
				coords[1] = (int) c - (int) 'A';
				coords[0] = Integer.parseInt(str.substring(1)) - 1;
				ok = (coords[0] >= 0 && coords[0] < taille && coords[1] >= 0 && coords[1] < taille);
			}
		}
		return coords;
	}
	
	/**
	 * Renvoie une page 
	 * @todo Fixer le bug si on demande à un menu initialisé avec le constructeur 'string' 
	 * @return
	 */
	public Page obtenirPage(){
		return this.redirections[this.obtenirInt() - 1];
	}
}
