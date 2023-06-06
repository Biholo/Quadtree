#ifndef __NOEUD__
#define __NOEUD__

#include "Point.h"
#include "Outil.h"

typedef struct Noeud {
    int fa;
    int fb;
    int fc;
    int fd;
    Position positionFirst;
    Position positionSecond;
    int plist;
    int nbp;
}Noeud, * QuadTree;

/**
 * @brief Allocation du Quadtree.
 * 
 * @param taille (int)
 * @return (Noeud*)
 */
Noeud * Allocation_arbre(int taille);

/**
 * @brief Cette fonction permet de creer notre QuadTree.
 * 
 * @param a (QuadTree)
 * @param debut (Position)
 * @param fin (Position)
 * @param indice (int)
 * @return (int)
 */
int creer_arbre(QuadTree a, Position debut, Position fin, int indice);

/**
 * @brief Ajout un point d'incide_point dans le Quadtree.
 * 
 * @param a (QuadTree)
 * @param indice_point (int)
 * @param indice (int)
 */
void ajout_point_arbre(QuadTree a, int indice_point,  int indice);

/**
 * @brief Retire tous les points ajouté dans le quadtree.
 * 
 * @param a (QuadTree)
 * @param indice (int)
 */
void vider_quadtree(QuadTree a, int indice);

/**
 * @brief Ajoute tous les points dans le QuadTree
 * 
 * @param a (QuadTree)
 */
void ajout_tab_dans_quadtree(QuadTree a);

/**
 * @brief Prend en compte les options pour attribué le type de déplacement adéquat.
 * 
 * @param opt (Option)
 * @param p (Position)
 * @param a (QuadTree)
 * @param points (Position*)
 */
void deplacement(Option opt, Position p, QuadTree a, Position * points);

#endif