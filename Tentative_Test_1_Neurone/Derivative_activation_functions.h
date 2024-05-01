#ifndef NEURONE_DERIVATION_H
#define NEURONE_DERIVATION_H

#include "Fonctions_activation.h"

double derivative_sigmoid(double x) {
    return sigmoid(x) * (1 - sigmoid(x));
}

#endif
