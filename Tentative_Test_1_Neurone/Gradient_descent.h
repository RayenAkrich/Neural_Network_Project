#include "Outils_optimisation.h"
#include "Fonctions_activation.h"
#include "Derivative_activation_functions.h"

#ifndef NEURONE_GRADIENT_DESCENT_H
#define NEURONE_GRADIENT_DESCENT_H

void gradient_descent(double input, double target_output, double learning_rate, int num_iterations, double *weight, double *bias,int count) {
    double predicted_output, error, loss_value;

        // Forward pass
        predicted_output = sigmoid((*weight) * input + (*bias));

        // Backpropagation
        error = predicted_output - target_output;

        // Gradient descent update
        (*weight) -= learning_rate * error * derivative_sigmoid(predicted_output) * input;
        (*bias) -= learning_rate * error * derivative_sigmoid(predicted_output);

    }

#endif
