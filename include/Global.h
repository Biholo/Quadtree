#ifndef __GLOBAL__
#define __GLOBAL__

#include "Point.h"
#include "Outil.h"

extern Point * tab_points;
extern int * tab_peres;
extern int taille_tab;
extern int taille_max_tab;
extern int k;
extern int taille_cell_min;
extern int taille_width;

/**
 * @brief Initilisation des variables global paramétrant le jeu.
 */
void init(int max_point_cell, int size_window, int size_min_cell);

#endif
