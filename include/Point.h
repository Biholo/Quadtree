#ifndef __POINT__
#define __POINT__

#include "Option.h"

typedef struct Position {
    int x; 
    int y;
} Position;

typedef struct  {
    Position pos;
    int color;
} Point;

typedef enum  {
    NORD, OUEST, EST, SUD, NORD_EST, NORD_OUEST, SUD_EST, SUD_OUEST
}Direction;


Position milieu_positions(Position pos1, Position pos2);

/**
 * @brief Allocation d'un tableau de points en fonction de taille_max.
 * 
 * @param taille_max (int)
 * @return (Point*)
 */
Point * allocation_tab(int taille_max);

/**
 * @brief initialisation du tableau de points.
 * 
 * @param points (Point*)
 * @param taille (int)
 */
void init_tableau(Point * points, int taille);

/**
 * @brief Ajout d'un point dans un tableau de point
 * a la position donnée en paramètre avec une couleur aléatoire.
 * 
 * @param tab (Point*)
 * @param p (Position)
 * @param tab_pos (Position*)
 */
void ajouter_point(Point * tab, Position p);

/**
 * @brief Verifie si un point n'est pas superposé avec les autres
 * points du QuadTree
 * 
 * @param tab_points (Point*)
 * @param n (int)
 * @param point (Position)
 * @return (int)
 */
int verif_superposition(Point * tab_points, int n, Position point);

/**
 * @brief Modifie les coordonnées des points de manière aléatoire.
 * 
 * @param tab_points (Point*)
 */
void deplacement_aleatoire_centrique(Point * tab_point);

/**
 * @brief Modifie les coordonnées des points progressivement jusqu'au
 * centre de la fenêtre.
 * 
 * @param tab_points (Point*)
 */
void deplacement_centre(Point * tab_point);

/**
 * @brief Modifie les coordonnées des points progressivement jusqu'aux 
 * coordonnées de la position p.
 * 
 * @param tab_points (Point*)
 */
void deplacement_spiral(Position p, Point * tab_point);

/**
 * @brief Modification d'une position p de manière circulaire. (La suite 
 * des modifications forment un cercle.)
 * 
 * @param tab_points (Point*)
 * @param angle (double*)
 */
void deplacement_point_ref(Position * p, double * angle);

/**
 * @brief Modifie les coordonnées des points de tab_point progressivement 
 * vers une position de tab_pos d'indice similaire. Lorsque la position et le point 
 * possède les même coordonnées, ont redéfini les coordonnées pour un nouveau point.
 * 
 * @param tab_pos (Position*)
 * @param tab_point (Point*)
 */
void deplacement_aleatoire(Position * tab_pos, Point * tab_point);

/**
 * @brief Génère les positions dans le tableau de position pos.
 * 
 * @param pos (Position*)
 */
void init_positions_deplacement(Position * pos);
#endif