#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>
#include <time.h>
#include <unistd.h>
#include <math.h>

#include "../include/Graphique.h"
#include "../include/Global.h"
#include "../include/Option.h"

#define SIZE_WINDOW 512
#define NBP 15
#define MIN_SIZE_CELL 1
#define POINTS 1000

int main(int argc, char *argv[]){
    srand(time(NULL));
    Option option;
    int elapsed_time;
    double angle = 0.0;

    /*Initialisation des variables et allocations des tableaux*/
    init(NBP, SIZE_WINDOW, MIN_SIZE_CELL);
    option = init_option();
    QuadTree b = Allocation_arbre(taille_width);
    Position debut = {0, 0};
    Position fin = {taille_width, taille_width};
    Position points_deplacement[taille_max_tab];

    Position pos = {taille_width/2 + 200, taille_width/2}; // Initial position
   
    /*Création des tableaux et ajout*/
    creer_arbre(b, debut, fin, 0);
    init_tableau(tab_points, POINTS);
    init_positions_deplacement(points_deplacement);
    ajout_tab_dans_quadtree(b);

    MLV_create_window( "Quadtree", "Quadtree", taille_width, taille_width);
    elapsed_time =  MLV_get_time();
    afficher_quadtree(b, option.affiche_point);
    while(option.play){
        //Affichage et vérification si une touche ou clic est pressé.
        if(option.deplacement){
            interaction_souris(b, &elapsed_time);
            interaction_keyboard(&option, &elapsed_time);
            deplacement_point_ref(&pos, &angle);
            deplacement(option, pos, b, points_deplacement);

        }
        //Si les déplacement sont désactivé alors ont attent une intéraction de l'utilisateur
        else {
            attente_interaction(b, &elapsed_time, &option);
        }
        afficher_quadtree(b, option.affiche_point);
        MLV_wait_milliseconds(20);
    }
    
    MLV_actualise_window();
    MLV_free_window();
    free(tab_peres);
    free(tab_points);
    free(b);

    return 0;
}