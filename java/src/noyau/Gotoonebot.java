/**
 * \class     noyau.Gotoonebot
 * \brief     IA utilisant la structure de donnée Minimax
 * \author    Francois Mahé
 */
package noyau;
import cretinplay.Application;

public class Gotoonebot implements Utilisateur
{

	private String nom;
	private Joueur j;
	
	static{System.loadLibrary("cretinhex_gotoonebot");}
	
	public Gotoonebot (Joueur J)
	{
		this.nom = "Rainbow Dash";
		this.j = J;
		gotoonebotXinit(this.j.toInt());
		System.out.println("Init faite");
	}
	
		public int[] jouer(Partie p){
			return gotoonebotXjouer(p.obtenirDamierInt(), p.largeurDamier());
		}
	
	
	/** \brief Appelle queJouer par JNI */
	private native int[] gotoonebotXjouer(int[] damier, int tailleDamier);
	private native void gotoonebotXinit(int joueur);
	
	
	
	
	
	
	
	/**
	 * \brief   Informe l'utilisateur du coup joué par l'adversaire
	 * \todo    Void si c'est vraiment nécessaire (on lui passe déjà la partie, et donc l'historique)
	 */
	public void actualiser(int x, int y){}
	
	/**
	 * \brief   Désallouer la mémoire (surtout pour les ia)
	 */
	public void quitter(){}
	
	public String getExistance(){
		return "gotoone";
		}
	/** \brief Obtenir le nom de l'utilisateur */
	public String getNom(){return this.nom;}
	
	/** \brief Définir le nom de l'utilisateur */
	public void setNom(String nom){}
	
	/** \brief Obtenir le joueur (J1 ou J2) */
	public Joueur getJoueur(){return this.j;}
	

	
}