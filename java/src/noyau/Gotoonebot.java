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
		this.Joueur = J;
		gotooneXinit(this.joueur);
	}

	
}