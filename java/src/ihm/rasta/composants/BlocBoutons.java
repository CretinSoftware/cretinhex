/**
 * \class     ihm.rasta.composants.BlocBoutons
 * \brief     Un bloc contenant des boutons en ligne
 * \author    Pierre Pomeret-Coquot
 * \date      3 mai
 */


package ihm.rasta.composants;

import java.util.Arrays;
import javax.swing.*;
import java.awt.*;

public class BlocBoutons extends Bloc {

	private Bouton boutons[];

	public BlocBoutons(Bouton... boutons){
		super();
		this.boutons = Arrays.copyOf(boutons, boutons.length);
		
		for (int i = 0; i < boutons.length; ++i)
			this.add(boutons[i]);
		
	}
	
	
	public Bouton getBt(int i){
		if (i < this.boutons.length)
			return this.boutons[i];
		
		System.err.println("Demande le bouton " + i + " là où il n'y en a que " + this.boutons.length);
		return null;
	}
}


