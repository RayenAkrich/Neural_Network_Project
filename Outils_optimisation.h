#include "math.h"

#ifndef NEURONE_OUTILS_OPTIMISATION_H
#define NEURONE_OUTILS_OPTIMISATION_H

//Calcul de Loss pour les fonctions d'activations Sigmoid
double Calcul_Loss_Sigmoid(double* valeurs_machine, int nb_input, double* valeurs_attendues) {
    double LOSS = 0;
    for(int i = 0; i <= nb_input; i++) {
        LOSS = LOSS + ( (valeurs_attendues[i] * log(valeurs_machine[i])) + ((1 - valeurs_attendues[i]) * log(1 - valeurs_machine[i])) );
    }
    LOSS = -LOSS / nb_input;
    return LOSS;
}

#endif 
