
package ihm.rasta.composants;

import javax.swing.*;
import java.awt.*;


public class BlocVide extends JPanel {
	
	public BlocVide(int tailleX, int tailleY){
		super();
		this.setOpaque(false);
		this.setPreferredSize(new Dimension(tailleX, tailleY));
	}
}


