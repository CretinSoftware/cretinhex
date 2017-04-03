package noyau;




/**
 * \brief Joueur désigne J1, J2, ou personne
 */

public enum Joueur {
	J0 (0, '-', "Personne"),
	J1 (1, 'O', "Joueur 1"),
	J2 (2, '#', "Joueur 2");

	
	private int intv;
	private char charv;
	private String stringv;
	
	
	/**
	 * \brief Constructeur privé affectant les valeurs intv, charv et strinv au champ local
	 */
	private Joueur(int intv, char charv, String stringv){
		this.intv = intv;
		this.charv = charv;
		this.stringv = stringv;
	}
	
	
	/** \brief Valeur entière associée à un joueur */
	public int toInt(){
		return this.intv;
	}
	
	/** \brief Renvoie le caractère associé à un joueur */
	public char toChar(){
		return this.charv;
	}
	
	/** \brief Chaîne de caractère associée à un joueur */
	public String toString(){
		return this.stringv;
	}
	
	
	
	
	
	/**
	 * \brief Joueur correspondant à un entier
	 * \param intv L'entier désignant le joueur
	 * \return Le joueur correspondant à l'entier désignant le joueur...
	 * \pre 0 &le; intv &le; 2
	 */
	public static Joueur fromInt(int intv){
		switch (intv){
			case 0: return J0;
			case 1: return J1;
			case 2: return J2;
			default: throw new IllegalArgumentException("Joueur " + intv + " inconnu ( j<0 ou j>2 ! )");
		}
	}
	

}


