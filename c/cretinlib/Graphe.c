/**
 * \file Graphe.c
 * \brief Implémentation du type Graphe.
 * \author Pierre POMERET-COQUOT
 * \version 1.0
 * \date 3 avril 2017
 *
 */
 
# include "Graphe.h"
# include <stdio.h>
# include <stdlib.h>
# include <assert.h>



/*
 * \defgroup pack_cretinlib_Graphe Graphe
 * \ingroup pack_cretinlib
 * \author Pierre POMERET-COQUOT
 * \version 1.0
 * \date 3 avril 2017
 *
 * \par Description
 * \todo Rapide description
 *
 *
 * \par Type abstrait de données
 *
 * <pre style="line-height:1.1em;">
 * SORTE :            Graphe
 * 
 * UTILISE :          GrapheElement, LDC, int
 *
 * CONSTRUCTEURS :    Graphe_init                                     _____ -> LDC
 *                    LDC_insererElement            LDC, LDCElement, int -> LDC   
 *
 * OPERATEURS :       LDC_obtenirElement                        LDC, int -> LDCElement
 *                    LDC_enleverElement                        LDC, int -> LDC
 *                    LDC_taille                                     LDC -> int
 *                    LDC_libererMemoire                      LDCElement -> _____
 *
 * </pre>
 * \todo Finir le TAD     
 *
 * @{               
 */


typedef struct Graphe {
	LDC pointsEntree;
	int nbNoeuds;
} GrapheInterne;














/*
 * \defgroup pack_cretinlib_GrapheNoeud GrapheNoeud
 * 
 * \par Description
 * Type manipulé par les Graphes, dans lesquels vous pouvez stocker vos &laquo; trucs &raquo;
 *
 * \par Type abstrait de données
 * <pre style="line-height: 1em;">
 *
 * Sorte :           GrapheNoeud
 *
 * Utilise :         GrapheElement (void *)
 *                   GrapheElementFree (fonction supprimant l'élément)
 *
 * Constructeur :    init :                GrapheElement, GrapheElementFree → GrapheNoeud
 *
 * Opérateurs :      obtenirElement :                           GrapheNoeud → GrapheElement
 *                   obtenirVoisins :                           GrapheNoeud → LDC (GrapheNoeud[])
 *                   fusionner :                  GrapheNoeud x GrapheNoeud → GrapheNoeud
 *                   libererMemoire :                           GrapheNoeud → __
 *
 * </pre>
 * 
 * @{               
 */

typedef struct GrapheNoeud {
	GrapheElement element;
	GrapheElementFree free;
	LDC voisins;
} GrapheNoeudInterne;




/*
 * \brief   Initialise un GrapheNoeud
 * \param   e L'élément contenu dans ce noeud
 * \param   free Fonction pour effacer l'élément, ou NULL
 * \return  Le noeud initialisé
 */
GrapheNoeud GrapheNoeud_init(GrapheElement e, GrapheElementFree free){
	GrapheNoeud noeud;
	
	noeud = (GrapheNoeud) malloc(sizeof(GrapheNoeudInterne));
	assert(noeud != NULL);
	
	noeud->element = e;
	noeud->free = free;
	noeud->voisins = LDC_init();
	
	return noeud;
}


/*
 * \brief   Récupère l'élément contenu dans un noeud
 */
GrapheElement GrapheNoeud_obtenirElement(GrapheNoeud noeud){
	return noeud->element;
}


/*
 * \brief   Donne la liste des noeuds voisins
 */
LDC GrapheNoeud_obtenirVoisins(GrapheNoeud noeud){
	return noeud->voisins;
}



/*
 * \brief Égalité de noeuds : même adresse
 */
int GrapheNoeud_estEgal(GrapheNoeud n1, GrapheNoeud n2){
	return (n1 == n2);
}

/*
 * \brief   Fusionne deux noeuds dans le premier
 * \param   n1 Le premier noeud
 * \param   n2 Le noeud à fusionner dans le premier
 * \return  Le premier noeud fusionné avec le second
 */
GrapheNoeud GrapheNoeud_fusionner(GrapheNoeud n1, GrapheNoeud n2){
	GrapheNoeud voisin;	
	
	while (LDC_taille(n2->voisins) > 0){
		voisin = (GrapheNoeud) LDC_obtenirElement(n2->voisins, 0);
		
		/* Le voisin n'est pas un voisin de n1 : on l'ajoute */
		if (LDC_obtenirPosition(n1->voisins, voisin, (LDCElementEgal) GrapheNoeud_estEgal) < 0)
			n1->voisins = LDC_insererElement(n1->voisins, -1, (LDCElement) voisin, NULL);
			voisin->voisins = LDC_insererElement(voisin->voisins, -1, (LDCElement) n1, NULL);

		/* Suppression du voisin dans n2 et de n2 dans voisin */
		n2->voisins = LDC_enleverElement(n2->voisins, 0);
		voisin->voisins = LDC_enleverElement(n2->voisins, LDC_obtenirPosition(voisin->voisins, (LDCElement) n2, (LDCElementEgal) GrapheNoeud_estEgal));
	}
	
	/* Libération du noeud n2 */
	GrapheNoeud_libererMemoire(&n2);
	
	return n1;
}


/*
 * \brief   Libère la mémoire allouée à un noeud
 * \note    Libère aussi la mémoire allouée à l'élément avec la fonction GrapheElementFree fournit à l'initialisation, si différente de NULL
 */
void GrapheNoeud_libererMemoire(GrapheNoeud * noeud){
	if ((*noeud)->free != NULL)
		(*noeud)->free(&((*noeud)->element));
	free(*noeud);
}


 
/** @} */











/* Graphe */

/*
 * \brief   Initialise un graphe
 * \param   pointsEntree Une LDC contenant les noeuds qui sont des points d'entrées
 * \return  Un graphe initialisé
 */
Graphe Graphe_init(LDC pointsEntree){
	Graphe g;

	g = (Graphe) malloc(sizeof(GrapheInterne));
	assert(g != NULL);

	g->pointsEntree = pointsEntree;
	g->nbNoeuds = 0;
	
	return g;
}

/*
 * \brief   Insertion d'un noeud
 * \param   noeud Le noeud à insérer, correctement initialisé
 * \param   voisins Une LDC contenant les noeuds voisins
 * \return  Le graphe mis à jour
 * \todo    Faire la fonction Graphe_insererNoeud()
 */
Graphe Graphe_insererNoeud(Graphe g, GrapheNoeud noeud, LDC voisins){
	return g;
}

/*
 * \brief   Libère la mémoire allouée à un Graphe
 * \todo    Faire la fonction Graphe_libererMemoire()
 *          et trouver l'heuristique permettant de nettoyer tous les noeuds
 */
void Graphe_libererMemoire(Graphe * g){
}




/** @} */
