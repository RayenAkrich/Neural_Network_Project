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
void train_single_neuron_network(const char* filename) {
    // Initialize network
    int num_couches = 1;
    int num_neurones[1] = {1};
    int num_xi_par_neurone[1] = {2};
    Reseau* reseau = initializer_reseau(num_couches, num_neurones, num_xi_par_neurone);

    // Load initial weights and bias
    charger_reseau(reseau, "C:\\Users\\junio\\Desktop\\Rayen\\Prog\\Neurone\\weights_bias.txt");

    double learning_rate = 0.01;
    int num_iterations = 100;

    // Set activation function to sigmoid
    reseau->couches[0]->neurones[0]->activation_function = 2;

    // Open the Excel file
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        liberer_reseau(reseau);
        return;
    }

    // Read feature 1, feature 2, and label from each row
    double feature1, feature2, label;
    int count = 0; // Déclaration de la variable count
    while (fscanf(file, "%lf %lf %lf", &feature1, &feature2, &label) == 3) {
        // Assign inputs to neuron
        reseau->couches[0]->neurones[0]->xi[0] = feature1;
        reseau->couches[0]->neurones[0]->xi[1] = feature2;

        // Forward pass
        double predicted_output = compter_couche_yi(reseau->couches[0], reseau->couches[0]->neurones[0]->xi);

        // Backpropagation and gradient descent
        double error = predicted_output - label;
        gradient_descent(feature1, label, learning_rate, num_iterations, &reseau->couches[0]->neurones[0]->wi[0], &reseau->couches[0]->neurones[0]->bias);
        gradient_descent(feature2, label, learning_rate, num_iterations, &reseau->couches[0]->neurones[0]->wi[1], &reseau->couches[0]->neurones[0]->bias);

        // Display progress
        if (count % 10 == 0) {
            double loss_value = Calcul_Loss_Sigmoid(predicted_output, label);
            printf("Iteration %d: Predicted Output = %.4f, Loss = %.4f\n", count, predicted_output, loss_value);
        }
        count++; // Incrémentation de count
    }

    // Close the file
    fclose(file);

    // Save trained weights and bias
    sauvegarder_reseau(reseau, "C:\\Users\\junio\\Desktop\\Rayen\\Prog\\Neurone\\weights_bias.txt");

    // Cleanup
    liberer_reseau(reseau);
}




#endif
