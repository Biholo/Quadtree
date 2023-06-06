#include "../include/Graphique.h"
#include "../include/Global.h"
#include "../include/Option.h"

//Affiches toutes les cases contenant des points
void affiche_cases(QuadTree q, int indice, int k){
    MLV_Color colorRectangle = MLV_convert_rgba_to_color(251, 255, 255, 255);
    MLV_Color colorContour = MLV_convert_rgba_to_color(191, 219, 243, 255);
    if(q[indice].plist != -1 && q[indice].nbp <= k){
        MLV_draw_filled_rectangle(q[indice].positionFirst.x, q[indice].positionFirst.y, q[indice].positionSecond.x - q[indice].positionFirst.x, q[indice].positionSecond.y - q[indice].positionFirst.y, colorRectangle);
        MLV_draw_rectangle(q[indice].positionFirst.x, q[indice].positionFirst.y, q[indice].positionSecond.x - q[indice].positionFirst.x, q[indice].positionSecond.y - q[indice].positionFirst.y, colorContour);
    }
    
    if(indice * 4 + 1 <=  max_noeud(taille_width, taille_cell_min) && q[indice * 4 + 1].nbp != 0 ){
        affiche_cases(q, indice * 4 + 1, k);
    }
    if(indice * 4 + 2 <= max_noeud(taille_width, taille_cell_min) && q[indice * 4 + 2].nbp != 0){
        affiche_cases(q, indice * 4 + 2, k);
    }
    if(indice * 4 + 3 <= max_noeud(taille_width, taille_cell_min) && q[indice * 4 + 3].nbp != 0 ){
        affiche_cases(q, indice * 4 + 3, k);
    }
    if(indice * 4 + 4 <= max_noeud(taille_width, taille_cell_min) && q[indice * 4 + 4].nbp != 0){
        affiche_cases(q, indice * 4 + 4, k);
    } 
}

//Affiche un point de la bonne couleur
void affiche_point(Point p){
    if(p.color == 0)
        MLV_draw_filled_circle(p.pos.x, p.pos.y, 1, MLV_COLOR_AZURE);
    else if(p.color == 1)
        MLV_draw_filled_circle(p.pos.x, p.pos.y, 1, MLV_COLOR_RED);
    else if(p.color == 2)
        MLV_draw_filled_circle(p.pos.x, p.pos.y, 1, MLV_COLOR_PINK);
    else if(p.color == 3)
        MLV_draw_filled_circle(p.pos.x, p.pos.y, 1, MLV_COLOR_BLUE);
    else if(p.color == 4)
        MLV_draw_filled_circle(p.pos.x, p.pos.y, 1, MLV_COLOR_GREEN);
    else if(p.color == 5)
        MLV_draw_filled_circle(p.pos.x, p.pos.y, 1, MLV_COLOR_YELLOW);
    else if(p.color == 6)
        MLV_draw_filled_circle(p.pos.x, p.pos.y, 1, MLV_COLOR_ORANGE);
}

//Affiche tout les points
void affiche_points(Point * tab_pts){
    for(int i = 0; i < taille_tab; i++){
        affiche_point(tab_pts[i]);
    }
}

//Affiche supprime et affiche le quadtree (cases + points)
void afficher_quadtree(QuadTree q, int points){
    MLV_clear_window(MLV_COLOR_WHITE);
    affiche_cases(q, 0, k);
    if(points)
        affiche_points(tab_points);
    MLV_actualise_window();
}

//Si une touche est pressé et qu'elle correspond 
void interaction_keyboard(Option * opt, int * time_last_key){
    int time = MLV_get_time();

    if(time - *time_last_key > 100){
        if(MLV_get_keyboard_state(MLV_KEYBOARD_z) == MLV_PRESSED){
            opt->deplacement = !opt->deplacement;
        }
        if(MLV_get_keyboard_state(MLV_KEYBOARD_a) == MLV_PRESSED){
            opt->affiche_point = !opt->affiche_point;
        }
        if(MLV_get_keyboard_state(MLV_KEYBOARD_e) == MLV_PRESSED){
            opt->play = 0;
        }
        if(MLV_get_keyboard_state(MLV_KEYBOARD_s) == MLV_PRESSED){
            opt->type_deplacement = Spiral;
        }
        if(MLV_get_keyboard_state(MLV_KEYBOARD_q) == MLV_PRESSED){
            opt->type_deplacement = Aleatoire;
        }
        if(MLV_get_keyboard_state(MLV_KEYBOARD_d) == MLV_PRESSED){
            opt->type_deplacement = Aleatoire_Centrique;
        }
        if(MLV_get_keyboard_state(MLV_KEYBOARD_f) == MLV_PRESSED){
            opt->type_deplacement = Centre;
        }
        *time_last_key = time;
    }
}

//Intéraction avec la souris
void interaction_souris(QuadTree a, int * time_last_key){
    int time = MLV_get_time();
    Position p;
    int x, y;
    //Si un clic gauche est pressé.
    if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED &&
    time - *time_last_key > 100) {
        MLV_get_mouse_position(&x, &y);
        p.x = x;
        p.y = y;
        ajouter_point(tab_points, p);
        ajout_point_arbre(a, taille_tab - 1, 0);
    }
}

//Attente l'intéraction du clavier ou d'un clic de la souris
void attente_interaction(QuadTree a, int * time_last_key, Option * option){
    MLV_Event event_type = MLV_wait_keyboard_or_mouse(NULL, NULL, NULL, NULL, NULL);
    if(event_type == MLV_MOUSE_BUTTON){
        interaction_souris(a, time_last_key);
    }
    else{
        interaction_keyboard(option, time_last_key);
    }
}