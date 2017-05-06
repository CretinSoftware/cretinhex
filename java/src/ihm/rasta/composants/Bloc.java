/**
 * \class     ihm.rasta.composants.Bloc
 * \brief     Un bloc simple, vide, transparent
 * \author    Pierre Pomeret-Coquot
 * \date      3 mai
 */


package ihm.rasta.composants;

import javax.swing.*;
import java.awt.*;


public class Bloc extends JPanel {
	
	public Bloc(){
		super();
		this.setOpaque(false);
	}
	
	public Bloc(int tailleX, int tailleY){
		super();
		this.setOpaque(false);
		this.setPreferredSize(new Dimension(tailleX, tailleY));
	}
}


