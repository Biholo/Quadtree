#ifndef __GRAPHIQUE__
#define __GRAPHIQUE__

#include <MLV/MLV_all.h>

#include "Quadtree.h"
#include "Option.h"

/**
 * @brief Cette fonction permet d'afficher graphiquement les cases avec des points de notre QuadTree.
 * 
 * @param q (QuadTree)
 * @param indice (int)
 * @param k (int)
 */
void affiche_cases(QuadTree q, int indice, int k);

/**
 * @brief Cette fonction permet d'afficher graphiquement les points de notre tableau de points
 * 
 * @param tab_pts (Point*)
 */
void affiche_points(Point * tab_pts);

/**
 * @brief Cette fonction permet d'afficher graphiquement tout le QuadTree (points et noeuds)
 * 
 * @param q (QuadTree)
 * @param point (int)
 */
void afficher_quadtree(QuadTree q, int point);

/**
 * @brief Détecte la pression d'une touche et modifie les options.
 * 
 * @param opt (Option*) Option modifiable au cours du jeu (deplacement, affichage, etc...)
 * @param time_last_key (int*) Indication du temps lors du denière événement clavier détecté
 */
void interaction_keyboard(Option * opt, int * time_last_key);

void interaction_souris(QuadTree a, int * time_last_key);

void attente_interaction(QuadTree a, int * time_last_key, Option * option);

void affiche_prefixe(QuadTree q, int indice);
#endif