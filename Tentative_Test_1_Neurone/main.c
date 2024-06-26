//Le programme permet de faire un train pour une seule neurone de 2 entrées avec la fonction d'activation sigmoid

#include <stdio.h>
#include <stdlib.h>
#include "Manipulation.h"
#include "Gradient_descent.h"
#include "Outils_optimisation.h"
#include "Derivative_activation_functions.h"
#include "Fonctions_activation.h"
#include "Save_load.h"
#include "Types.h"
#include "Train_single_neurone.h"
#include <time.h>

int main() {
    srand(time(NULL));
    train_single_neuron_network("dataset.txt");
    return 0;
}
