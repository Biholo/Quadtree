#include <stdio.h>
#include <stdlib.h>

#include "../include/Quadtree.h"
#include "../include/Global.h"
#include "../include/Outil.h"


//Alloue la mémoire nécessaire pour un arbre
Noeud * Allocation_arbre(int taille){
    int taille_max = max_noeud(taille, taille_cell_min);
    Noeud * tab = (Noeud*)malloc(sizeof(Noeud) * taille_max);
    if(tab == NULL){
        fprintf(stderr, "Erreur lors de l'allocation du tableau de noeuds.\n");
        exit(-1);
    }
    return tab;
}

//Crée l'arbre
int creer_arbre(QuadTree a, Position debut, Position fin, int indice){
    Position milieu, tmp_first, tmp_second;
    
    if(indice>= max_noeud(taille_width, taille_cell_min)){
        return 0;
    }
    //
    a[indice].positionFirst = debut;
    a[indice].positionSecond = fin;
    a[indice].plist = -1;
    a[indice].fa = 4 * indice + 1;
    a[indice].fb = 4 * indice + 2;
    a[indice].fc = 4 * indice + 3;
    a[indice].fd = 4 * indice + 4;  
    a[indice].nbp = 0;
    milieu = milieu_positions(a[indice].positionFirst, a[indice].positionSecond);

    //fa
    creer_arbre(a, a[indice].positionFirst, milieu, 4 * indice + 1);
    //fb
    tmp_first.x = milieu.x;
    tmp_first.y = a[indice].positionFirst.y;
    tmp_second.x = a[indice].positionSecond.x;
    tmp_second.y = milieu.y;
    creer_arbre(a, tmp_first, tmp_second, 4 * indice + 2);

    //fc
    tmp_first.x = a[indice].positionFirst.x;
    tmp_first.y = milieu.y;
    tmp_second.x = milieu.x;
    tmp_second.y = a[indice].positionSecond.y;
    creer_arbre(a, tmp_first, tmp_second, 4 * indice + 3);
    //fd
    creer_arbre(a, milieu, a[indice].positionSecond, 4 * indice + 4);
    return 1;
}

//Ajoute un point dans l'arbre
void ajout_point_arbre(QuadTree a, int indice_point,  int indice){
    a[indice].nbp++;
    //Noeud vide sans aucun point
    if(a[indice].nbp == 1 && a[indice].plist == -1){
        a[indice].plist = indice_point;
        tab_peres[indice_point] = indice_point;
    }
    //Si plist n'est pas vide ->
    else if(a[indice].plist != -1){
        int temp_i = a[indice].plist;
        //Ne dépasse pas la taille maximun d'un noeud ou noeud externe
        if(a[indice].nbp <= k || indice * 4 + 1 > max_noeud(taille_width, taille_cell_min)){
            while(tab_peres[temp_i] != temp_i){
                temp_i = tab_peres[temp_i];
            }
            tab_peres[temp_i] = indice_point;
            tab_peres[indice_point] = indice_point;   
        }
        //Dépasse la taille maximun d'un noeud et qui n'est pas un noeud externe
        else{
            a[indice].plist = -1;
            int temp_i_second;
            while(tab_peres[temp_i] != temp_i){ //Redistribution des points dans les noeuds fils.
                temp_i_second = tab_peres[temp_i];
                ajout_point_arbre(a, temp_i, indice);
                temp_i = temp_i_second;
            }
            ajout_point_arbre(a, temp_i, indice);
            ajout_point_arbre(a, indice_point, indice); //Ajout du nouveau point
            a[indice].nbp = a[indice].nbp - k - 1;
        }
    }
    //Appel récursif sur les fils
    else{
        Position milieu = milieu_positions(a[indice].positionFirst, a[indice].positionSecond);
        if(tab_points[indice_point].pos.x >= milieu.x){
            if(tab_points[indice_point].pos.y >= milieu.y){
                ajout_point_arbre(a, indice_point, indice * 4 + 4);
            }else {
                ajout_point_arbre(a, indice_point, indice * 4 + 2);
            }
        }else{
            if(tab_points[indice_point].pos.y >= milieu.y){
                ajout_point_arbre(a, indice_point, indice * 4 + 3);
            }else {
                ajout_point_arbre(a, indice_point, indice * 4 + 1);
            }
        }
    }
}
//Permet de retirer les éléments présent dans le tableau de noeud (Quadtree)
void vider_quadtree(QuadTree a, int indice){
    a[indice].nbp = 0;
    a[indice].plist = -1;
    if(indice * 4 + 1 < max_noeud(taille_width, taille_cell_min)){
        if(a[indice * 4 + 1].nbp != 0)
            vider_quadtree(a, indice * 4 + 1);
        if(a[indice * 4 + 2].nbp != 0)
            vider_quadtree(a, indice * 4 + 2);
        if(a[indice * 4 + 3].nbp != 0)
            vider_quadtree(a, indice * 4 + 3);
        if(a[indice * 4 + 4].nbp != 0)
            vider_quadtree(a, indice * 4 + 4);
    }
}

//Ajoute tout les points dans le quadtree
void ajout_tab_dans_quadtree(QuadTree a){
    for(int i = 0; i < taille_tab; i++){
        ajout_point_arbre(a, i, 0);
    }
}

//Déplacement les points en fonction du type de déplacement
void deplacement(Option opt, Position p, QuadTree a, Position * pos){
    if(opt.deplacement){
        vider_quadtree(a, 0);
        if(opt.type_deplacement == Aleatoire)
            deplacement_aleatoire(pos, tab_points);
        else if(opt.type_deplacement == Centre)
            deplacement_centre(tab_points);
        else if(opt.type_deplacement == Spiral)
            deplacement_spiral(p, tab_points);
        else if(opt.type_deplacement == Aleatoire_Centrique)
            deplacement_aleatoire_centrique(tab_points);
        ajout_tab_dans_quadtree(a);
    }   
}