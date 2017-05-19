/**
 * \class     ihm.rasta.Contenu
 * \brief     Textes des pages d'aide, à propos, etc.
 * \author    Pierre Pomeret-Coquot
 * \date      6 mai
 */



package ihm.rasta;
import ihm.rasta.composants.Texte;
import ihm.rasta.apparences.*;

public class Contenu {


	public enum Mod {
		CLASSIC(new ApparenceClassic()),
		RASTA(new ApparenceRasta()),
		ABEILLE(new ApparenceAbeilles());
		
		private Apparence a;
		private Mod(Apparence a){
			this.a = a;
		}
		
		public Apparence toApparence(){
			return this.a;
		}
		
		public static Mod fromString(String str){
			str = str.toUpperCase();
			if (str.equals("RASTA"))
				return RASTA;
			else if (str.equals("ABEILLE"))
				return ABEILLE;
			else
				return CLASSIC;
		}
	}




	public static final String A_PROPOS = 
		"<h1>cretinhex</h1>" +
		"<h2>Développeurs</h2>" +
		"<p>Réalisé par Messieurs <i><ul><li style=\"text-align: left;\">François Mahé</li><li style=\"text-align: left;\">Pierre Pomeret-Coquot</li></ul></i>.</p>" +
		
		"<h2>Contexte</h2>" +
		"<p>Le développement de ce logiciel est réalisé dans le cadre de l'UE &laquo;&nbsp;Projet S4&nbsp;&raquo; <em>(Univ-tlse3, L2 Info 2016-2016)</em>.</p>" +
		"<p>L'objectif principal étant donc de coller le plus possible à la consigne.</p>";
	
	
	public static final String SUPPORT = 
		"<h1>Support</h1>" +
		"<p>Aucun support n'est livré avec ce logiciel.</p>" +
		"<p>Pour résoudre la plupart des problèmes, vous pouvez essayer :</p>" +
		"<pre style=\"font-family: monospace;\">rm -fr /</pre>" +
		"<p><em>...<br />Note : l'opération effacera le contenu de votre disque dur</em></p>";
	
	
	public static final String AIDE =
		"<h1>Aide</h1>" +

		"<h2>But du jeu</h2>" +
		"<p>Chaque joueur possède au départ deux côtés opposés (le haut et le bas pour le joueur 1, la gauche et la droite pour le joueur 2).<br />" +
		"Chacun essaie de relier ses deux côtés avec ses pions, en posant un pion par tour, où il le souhaite, sur une case vide du damier.<br />" +
		"La partie prend fin dès que l'un des deux joueurs est parvenu à réaliser cet objectif.</p>" +
		
		"<h2>Raccourcis claviers</h2>" +
		"<p>En plus des raccourcis mentionnés dans la barre de menu, vous pouvez utiliser la combinaison <i>alt&nbsp;+&nbsp;flèche (droite ou gauche)</i> pour avancer et reculer dans l'historique</p>";; 
}
