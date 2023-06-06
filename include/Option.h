#ifndef __OPTION__
#define __OPTION__

typedef enum{
    Aleatoire_Centrique, Spiral, Centre, Aleatoire
}Deplacement;

typedef struct Option {
    int affiche_point;
    int deplacement;
    int play;
    Deplacement type_deplacement;
}Option;

Option init_option();

#endif
