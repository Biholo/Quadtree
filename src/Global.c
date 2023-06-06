#include "../include/Global.h"

/*Initialisation des variables global*/
Point * tab_points;
int * tab_peres;
int taille_tab;
int taille_max_tab = 10000;
int k;
int taille_cell_min;
int taille_width;

//Initialisation à partir des paramètre
void init(int max_point_cell, int size_window, int size_min_cell) {
    tab_peres = allocation_tab_pere(taille_max_tab);
    tab_points = allocation_tab(taille_max_tab);
    taille_cell_min = size_min_cell;
    taille_width = size_window;
    k = max_point_cell;
}   