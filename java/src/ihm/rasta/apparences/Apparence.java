/**
 * \interface ihm.rasta.apparences.Apparence
 * \brief     Ce que fait une Apparence : donner des urls
 * \author    Pierre Pomeret-Coquot
 * \date      6 mai
 */
 
package ihm.rasta.apparences;

import noyau.Joueur;
import noyau.Utilisateur;

public interface Apparence {


	public String url(RefImage ref);
	public String url(Utilisateur u);
	
	
}
	
