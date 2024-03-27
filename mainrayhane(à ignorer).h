int main()
{
    // Variables for the example usage
    int num_neurones;            // Number of neurons
    int num_xi_par_neurone;      // Number of inputs per neuron
    int choix_fonction;          // Activation function choice
    int activation_function;    // Activation function for each neuron

    // Prompt the user to input the number of neurons
    printf("Enter the number of neurons: ");
    scanf("%d", &num_neurones);

    // Prompt the user to input the number of inputs per neuron
    printf("Enter the number of inputs per neuron: ");
    scanf("%d", &num_xi_par_neurone);

    // Prompt the user to choose the activation function
    printf("Choose the activation function:\n");
    printf("1. ReLU\n");
    printf("2. Sigmoid\n");
    printf("3. Softmax\n");
    printf("Enter your choice: ");
    scanf("%d", &choix_fonction);

    // Initialize a layer of neurons
    Couche* couche = initializer_couche(num_neurones, num_xi_par_neurone);

    // Allocate memory for input values for each neuron
    double* xi_valeurs = malloc(num_xi_par_neurone * sizeof(double));

    // Check if memory allocation succeeded
    if (xi_valeurs == NULL)
    {
        printf("Error: Memory allocation failed for input values.\n");
        exit(EXIT_FAILURE);
    }

    // Prompt the user to input values for each neuron
    printf("Enter the input values for each neuron:\n");
    for (int i = 0; i < num_neurones; i++)
    {
        printf("Neuron %d input values:\n", i + 1);
        for (int j = 0; j < num_xi_par_neurone; j++)
        {
            printf("Value %d: ", j + 1);
            scanf("%lf", &xi_valeurs[j]);
        }

        // Assign the activation function for each neuron based on user choice
        switch (choix_fonction)
        {
            case 1:
                activation_function = 1;
                break;
            case 2:
                activation_function = 2;
                break;
            case 3:
                activation_function = 3;
                break;
            default:
                printf("Invalid choice.\n");
                exit(EXIT_FAILURE);
        }

        // Change the neuron's activation function based on the user's choice
        couche->neurones[i]->activation_function = activation_function;
    }

    // Calculate the output of the layer
    compter_couche_yi(couche, xi_valeurs);

    // Display the output of each neuron in the layer
    printf("Output of the layer:\n");
    for (int i = 0; i < couche->num_neurones; i++)
    {
        printf("Neuron %d output: %.2f\n", i + 1, couche->neurones[i]->yi);
    }

    // Free memory allocated for input values
    free(xi_valeurs);

    // Free memory allocated for neurons and the neuron layer
    free_couche(couche);

    return 0;
}
