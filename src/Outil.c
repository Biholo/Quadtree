#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../include/Outil.h"

int puissance_base_2(int n){
    int res = 0;
    while(n != 1){
        n = n/2;
        res++;
    }
    return res;
}

//Retourne le nombre de noeud maximal
int max_noeud(int n, int dim) {
    double expo = (double)puissance_base_2(n) - (double)puissance_base_2(dim);
    double base = 4.0;
    double res = 0;
    while(expo >= 0) {
        res += pow(base, expo);
        expo--;
    }
    return (int)res;
}

//Allocation des tableaux des peres
int * allocation_tab_pere(int nb_points){
    int * tab = (int*)malloc(sizeof(int) * nb_points);
    if(tab == NULL){
        fprintf(stderr, "Erreur lors de l'allocation du tableau.");
        exit(-1);
    }
    return tab;
}