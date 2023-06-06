#ifndef __OUTIL__
#define __OUTIL__


/**
 * @brief Cette fonction permet de savoir le nombre maximal de noeuds que l'on peut 
 * avoir de la fenêtre en fonction des dimensions de la fenêtre.
 *
 * @param n (int)
 * @return (int)
 */
int max_noeud(int n, int dim);

/**
 * @brief Cette fonction permet d'allouer notre tableau des pères pour les points
 * 
 * @param nb_points (int)
 * @return (int)
 */
int * allocation_tab_pere(int nb_points);
#endif