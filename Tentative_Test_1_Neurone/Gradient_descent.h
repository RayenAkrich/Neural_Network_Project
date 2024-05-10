#include "Outils_optimisation.h"
#include "Fonctions_activation.h"
#include "Derivative_activation_functions.h"

#ifndef NEURONE_GRADIENT_DESCENT_H
#define NEURONE_GRADIENT_DESCENT_H

void gradient_descent(double input, double target_output, double learning_rate, int num_iterations, double *weight, double *bias,int count) {
    double predicted_output, error, loss_value;

    FILE *file = fopen("weights_bias.txt", "a"); // Ouvre le fichier en mode ajout 

    if (file == NULL) {
        printf("Erreur lors de l'ouverture du fichier weights_bias.txt\n");
        exit(EXIT_FAILURE);
    }
        // Forward pass
        predicted_output = sigmoid((*weight) * input + (*bias));

        // Backpropagation
        error = predicted_output - target_output;

        // Gradient descent update
        (*weight) -= learning_rate * error * derivative_sigmoid(predicted_output) * input;
        (*bias) -= learning_rate * error * derivative_sigmoid(predicted_output);

        // Calculate loss for monitoring
        loss_value = Calcul_Loss_Sigmoid(predicted_output,target_output);
        printf("Iteration %d: Predicted Output = %.4f, Error = %.4f, Loss = %.4f\n", count+1, predicted_output, error, loss_value);

        // Write loss value to the file
        fprintf(file, "Iteration %d: Predicted Output = %.4f, Error = %.4f, Loss = %.4f\n", count+1, predicted_output, error, loss_value);
    fclose(file);
    }

#endif
