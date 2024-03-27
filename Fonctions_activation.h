//Cette librairie contient quelques fonctions d'activations

#include<math.h>
#ifndef NEURONE_FONCTIONS_ACTIVATIONS_H
#define NEURONE_FONCTIONS_ACTIVATIONS_H

//Fonction ReLu:éteint les entrées négatives et maintient les entrées positives
double relu (double x)
{
    return fmax(0,x);
}

//Fonction Segmoide:comprime les entrées dans une plage de probabilités entre 0 et 1
double sigmoid (double x)
{
    return 1 / (1 + exp(-x));
}

//Fonction Softmax :transforme les entrées en probabilités et garantit qu'elles s'additionnent à 1
void softmax(double *x, int numb_xi, double *yi) {
    double max_xi = x[0];
    double sum_exp = 0.0;

    //Rechercher le maximum dans le tableau d'entrées
    for (int i = 1; i < numb_xi; i++) {
        if (x[i] > max_xi) {
            max_xi = x[i];
        }
    }

    //Calculer la somme exponentielle
    for (int i = 0; i < numb_xi; i++) {
        sum_exp += exp(x[i] - max_xi); // Soustraction du maximum pour éviter le débordement numérique
    }

    //Calculer les probabilités normalisées
    for (int i = 0; i < numb_xi; i++) {
        yi[i] = exp(x[i] - max_xi) / sum_exp;
    }
}

#endif
