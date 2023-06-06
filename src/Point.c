#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../include/Point.h"
#include "../include/Global.h"
#include "../include/Option.h"

#define RADIUS 200
#define ANGLE_STEP 0.03
#define M_PI 3.141593

//Allocation des points 
Point * allocation_tab(int taille_max){
    Point * tab = (Point*)malloc(sizeof(Point) * taille_max);
    if(tab == NULL){
        fprintf(stderr, "Erreur lors de l'allocation du tableau de points.\n");
        exit(-1);
    }
    return tab;
}

//Verifi si deux points sont supperposé
int verif_superposition(Point * tab_points, int n, Position point){
    for(int i = 0; i < n; i++){
        if(tab_points[i].pos.x == point.x && tab_points[i].pos.y == point.y)
            return 1;
    }
    return 0;
}

//Remplissage du talbeau de point
void init_tableau(Point * points, int taille){
    Point point;
    Position p;
    if(points == NULL){
        fprintf(stderr, "Echec d'initialisation du tableau\n");
        exit(-1);
    }
    for(int i = 0; i < taille; i++){
        do {
            p.x = rand() % taille_width;
            p.y = rand() % taille_width;
        } while(verif_superposition(points, i, p));   
        taille_tab++;
        point.pos = p;
        point.color = rand() % 7;
        points[i] = point;
    }
}

//Génère une position aléatoire
Position position_aleatoire(){
    Position p;
    p.x = rand() % taille_width;
    p.y = rand() % taille_width;
    return p;
}

//Remplissage du tableau de position avec des positions aléatoire
void init_positions_deplacement(Position * pos){
    for(int i = 0; i < taille_max_tab; i++){
        pos[i] = position_aleatoire();
    }
}

//Déplacement des points de manière aléaoitre en fonction de 8 directions possibles
void deplacement_aleatoire_centrique(Point * tab_point){
    for(int i = 0; i < taille_tab; i++){
        switch (rand() % 8){
        case NORD:
            tab_point[i].pos.y--;
            break;
        case SUD:
            tab_point[i].pos.y++;
            break;
        case EST:
            tab_point[i].pos.x++;
            break;
        case OUEST:
            tab_point[i].pos.x--;
            break;
        case NORD_EST:
            tab_point[i].pos.y++;
            tab_point[i].pos.x--;
            break;
        case NORD_OUEST:
            tab_point[i].pos.y--;
            tab_point[i].pos.x--;
            break;
        case SUD_EST:
            tab_point[i].pos.x++;
            tab_point[i].pos.y--;
            break;
        case SUD_OUEST:
            tab_point[i].pos.x++;
            tab_point[i].pos.y++;
            break;
        
        default:
            break;
        }
    }
}

//Déplace les points en fonction de l'element du tableau de position avec
//la même occurence
void deplacement_aleatoire(Position * tab_pos, Point * tab_point){
    for(int i = 0; i < taille_tab; i++){
        if(tab_pos[i].x < tab_point[i].pos.x)
            tab_point[i].pos.x--;
        else if(tab_pos[i].x > tab_point[i].pos.x)
            tab_point[i].pos.x++;

        if(tab_pos[i].y < tab_point[i].pos.y)
            tab_point[i].pos.y--;
        else if(tab_pos[i].y > tab_point[i].pos.y)
            tab_point[i].pos.y++;

        if(tab_pos[i].x == tab_point[i].pos.x && tab_pos[i].y == tab_point[i].pos.y){
            tab_pos[i] = position_aleatoire();
        }

    }
}

//Déplace tout les points vers le centre de la fênetre
void deplacement_centre(Point * tab_point){
    for(int i = 0; i < taille_tab; i++){
        if(tab_point[i].pos.x > taille_width/2)
            tab_point[i].pos.x--;
        else
            tab_point[i].pos.x++;

        if(tab_point[i].pos.y > taille_width/2)
            tab_point[i].pos.y--;
        else
            tab_point[i].pos.y++;
    }
}

//Déplace les points en fonction de la position p qui est un point de référence
void deplacement_spiral(Position p, Point * tab_point){
    for(int i = 0; i < taille_tab; i++){
        if(p.x < tab_point[i].pos.x)
            tab_point[i].pos.x--;
        else
            tab_point[i].pos.x++;

        if(p.y < tab_point[i].pos.y)
            tab_point[i].pos.y--;
        else
            tab_point[i].pos.y++;
    }
}

//Déplace le point de référence pour le déplacement spiral
void deplacement_point_ref(Position * p, double * angle){
    (*p).x = taille_width/2 + RADIUS * cos(*angle);
    (*p).y = taille_width/2 - RADIUS * sin(*angle);
    *angle += ANGLE_STEP;
    if (*angle >= 2 * M_PI) {
        *angle -= 2 * M_PI;
    }
}

//Ajoute un point à l'emplacement de position p et augmente la taille général du tableau de point
void ajouter_point(Point * tab, Position p){
    Point point;
    point.pos = p;
    point.color = rand() % 7;
    tab[taille_tab] = point;
    taille_tab++;
}

//Récupère le milieu de deux positions
Position milieu_positions(Position pos1, Position pos2){
    Position milieu;
    milieu.x = pos1.x + ((pos2.x - pos1.x) / 2);
    milieu.y = pos1.y +((pos2.y - pos1.y) / 2);   
    return milieu;
}

