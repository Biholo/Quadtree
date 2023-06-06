#include "../include/Option.h"

//Initialisation des options
Option init_option(){
    Option opt;
    opt.affiche_point = 1;
    opt.deplacement = 0;
    opt.type_deplacement = Aleatoire;
    opt.play = 1;
    return opt;
}