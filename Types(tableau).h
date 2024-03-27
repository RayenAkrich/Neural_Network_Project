#ifndef NEURONE_TYPES_H
#define NEURONE_TYPES_H

//Type neurone
typedef struct Neurone
{
    int num_xi; //Nombre d'entrées du neurone
    //L'utilisation de  "double" plutôt que "int" ou "float" pour une meilleure précision des calculs
    double *xi; //Tableau pour stocker les valeurs d'entrée
    double *wi; //Tableau pour stocker les poids (weight) associés à chaque entrée
    double bias; //Bias ajuste la sortie du neurone indépendamment des valeurs d'entrée,
    double yi; //Valeur de sortie après activation
    int activation_function;//Type de fonction d'activation pour le neurone (il prendra 1,2,3)
} Neurone;

//Type couche
typedef struct Couche
{
    int num_neurones; //Nombre de neurones dans la couche
    Neurone **neurones; //Tableau de pointeurs de neurones
}Couche;

//Type réseau neurone
typedef struct Reseau{
    int num_couches; // Nombre de couches dans le réseau neuronal
    Couche **couches; // Tableau de pointeurs de couches
}Reseau;

#endif
