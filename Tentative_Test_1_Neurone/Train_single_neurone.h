#include <stdio.h>
#include <stdlib.h>
#include "Manipulation.h"
#include "Outils_optimisation.h"
#include "Fonctions_activation.h"
#include "Derivative_activation_functions.h"
#include "Types.h"
#include "Save_load.h"
#include "Gradient_descent.h"

#ifndef NEURONE_TRAIN_H
#define NEURONE_TRAIN_H


// Train a single neuron network
void train_single_neuron_network() {
    // Initialize network
    int num_couches = 1;
    int num_neurones[1] = {1};
    int num_xi_par_neurone[1] = {2};
    Reseau* reseau = initializer_reseau(num_couches, num_neurones, num_xi_par_neurone);

    // Input data
    double inputs[2];
    double target_output;

    // Load initial weights and bias
    charger_reseau(reseau, "weights_bias.bin");

    double learning_rate = 0.01;
    int num_iterations = 100;

    // Set activation function to sigmoid
    reseau->couches[0]->neurones[0]->activation_function = 2;

    // Train the network
    for (int i = 0; i < num_iterations; ++i) {
        // Retrieve input data
        printf("Enter input 1: ");
        scanf("%lf", &inputs[0]);
        printf("Enter input 2: ");
        scanf("%lf", &inputs[1]);
        printf("Enter target output: ");
        scanf("%lf", &target_output);

        // Forward pass
        double predicted_output = compter_couche_yi(reseau->couches[0], inputs);

        // Backpropagation and gradient descent
        double error = predicted_output - target_output;
        gradient_descent(inputs[0], target_output, learning_rate, num_iterations);
        gradient_descent(inputs[1], target_output, learning_rate, num_iterations);
        
        // Display progress
        if (i % 10 == 0) {
            double loss_value = Calcul_Loss_Sigmoid(&predicted_output, 1, &target_output);
            printf("Iteration %d: Predicted Output = %.4f, Loss = %.4f\n", i, predicted_output, loss_value);
        }
    }

    // Save trained weights and bias
    sauvegarder_reseau(reseau, "weights_bias.bin");

    // Cleanup
    liberer_reseau(reseau);
}

#endif
