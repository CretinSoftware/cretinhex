/**
 * \interface noyau.Utilisateur
 * \brief     Interface pour les humains et les IA
 * \author    Pierre Pomeret-Coquot
 * \date      samedi 1er avril
 *
 */
package noyau;

public interface Utilisateur
{
	/** \brief Obtenir le nom de l'utilisateur */
	public String getNom();
	
	/** \brief Définir le nom de l'utilisateur */
	public void setNom(String nom);
	
	/** 
	 * \brief   Faire jouer un coup à l'utilisateur
	 * \param   p L'état actuel de la partie
	 * \return  Une paire de coordonnées (x,y) valide
	 *
	 * \par     Description
	 * La méthode jouer() est implémentée pour chaque Utilsiateur (Humain, IA) et permet,
	 * par l'ihm ou les bibliothèques, de lui demander ce qu'il souhaite jouer.
	 *
	 * Le couple (x,y) renvoyé correspond à un placement valide.
	 */
	public int[] jouer(Partie p);
	
	/**
	 * \brief   Informe l'utilisateur du coup joué par l'adversaire
	 * \todo    Void si c'est vraiment nécessaire (on lui passe déjà la partie, et donc l'historique)
	 */
	public void actualiser(int x, int y);
}
