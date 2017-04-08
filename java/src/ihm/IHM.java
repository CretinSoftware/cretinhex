/**
 * \interface ihm.IHM
 * \brief     Interface pour interfaces-utilisateurs
 * \author    Pierre Pomeret-Coquot
 * \date      samedi 1er avril
 */
package ihm;

public interface IHM {


	/**
	 * \brief  Est appelée par la classe main au lancement du programme
	 *
	 * L'application laisse la main à l'ihm avec un appel à cette fonction, 
	 * cette dernière utilisera le noyau pour ce qui ressort du traitement de données.
	 */
	public void play();
	
	/**
	 * \brief  Est appelée par noyau.Humain pour demander les coordonnées au joueur
	 * \param  taille La taille du damier 
	 * \return Un tableau de deux entiers compris entre 0 et taille-1
	 */
	public int[] obtenirCoords(int taille);
	
}
