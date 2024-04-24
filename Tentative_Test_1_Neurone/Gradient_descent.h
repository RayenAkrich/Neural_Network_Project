#ifndef NEURONE_GRADIENT_DESCENT_H
#define NEURONE_GRADIENT_DESCENT_H

#include "Outils_optimisation.h"
#include "Fonctions_activation.h"
#include "Derivative_activation_functions.h"

double gradient_descent(double input, double target_output, double learning_rate, int num_iterations) {
  // P.S : the learning rate is usually low so the predicted output is close to the target
    double predicted_output, error;

    for (int i = 0; i < num_iterations; i++) {
        // Forward pass, it shows us the predicted output of the neural network
        predicted_output = sigmoid(weight * input + bias); // in this example, we used the Sigmoid function, we could use ReLU

        // Backpropagation, it computes the gradients of the loss function with respect to the parameters, enabling the model to learn from the training data and improve its predictions over time
        error = predicted_output - target_output;

        // Gradient descent update
        weight -= learning_rate * error * derivative_sigmoid(predicted_output) * input;
        bias -= learning_rate * error * derivative_sigmoid(predicted_output);

        // Calculate binary cross-entropy loss for monitoring
        double loss_value = Calcul_Loss_Sigmoid(&predicted_output, 1, &target_output);
        printf("Iteration %d: Predicted Output = %.4f, Error = %.4f, Loss = %.4f\n", i+1, predicted_output, error, loss_value);
    }
    printf("FINAL Predicted Output = %.4f,FINAL Error = %.4f,FINAL Loss = %.4f\n", predicted_output, error, loss_value);
    return predicted_output;
}


#endif
