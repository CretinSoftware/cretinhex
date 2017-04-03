/**
 * 
 */
package noyau;

/**
 * @author Pierre
 *
 */
public interface Utilisateur
{
	public String getNom();
	public void setNom(String nom);
	public int[] jouer(Partie p);
	public void actualiser(int x, int y);
}
