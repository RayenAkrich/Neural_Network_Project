#ifndef NEURONE_MANIPULATION_H
#define NEURONE_MANIPULATION_H

//Initialiser un neurone avec un nombre d'entrées donné
Neurone* initializer_neurone(int num_xi)
{
    Neurone* neurone = (Neurone*)malloc(sizeof(Neurone));//Allouer de la mémoire pour un nouveau neurone
    
    //Vérifier si l'allocation de mémoire a réussi
    if (neurone == NULL)
	{
        printf( "Erreur : Impossible d'allouer de la mémoire pour le neurone.\n");
        exit ;
    }
    
    neurone->num_xi = num_xi; //Assigner le nombre d'entrées du neurone
    neurone->xi = (double*)malloc(num_xi * sizeof(double));//Allouer de la mémoire pour le tableau d'entrées (xi)
    
    //Vérifier si l'allocation de mémoire a réussi
	if (neurone->xi == NULL)
	{
        printf( "Erreur : Impossible d'allouer de la mémoire pour les entrées du neurone.\n");
        exit ;
    }
    
    neurone->wi = (double*)malloc(num_xi * sizeof(double));// Allouer de la mémoire pour le tableau de poids (weights)(wi)
    
    //Vérifier si l'allocation de mémoire a réussi
    if (neurone->wi == NULL)
	{
        printf("Erreur : Impossible d'allouer de la mémoire pour les weights du neurone.\n");
        exit ;
    }
    
    //Initialiser les poids (weight) et le biais (bias) de manière aléatoire de façon qu'on assure que les poids initiaux du neurone sont aléatoires mais centrés autour de zéro, ce qui est une pratique courante dans l'initialisation des réseaux neuronaux, aidant ainsi à prévenir le blocage du réseau dans des optima locaux pendant l'entraînement et permettant un meilleur apprentissage
    for (int i = 0; i < num_xi; i++)
    {
        neurone->wi[i] = ((double)rand() / RAND_MAX) * 2 - 1;//On utilise rand() pour assurer que le nombre soit aléatoire//On divise le nmbre obtenu par RAND_MAX pour obtenir une valeur entre 0 et 1//On maintient la valeur entre -1 et 1 par lamultiplication de 2 et la soustraction de 1
    }
    neurone->bias = ((double)rand() / RAND_MAX) * 2 - 1;//Même démarche que wi
    
    return neurone;//Retourner le pointeur vers le neurone initialisé
}

//Initialiser une couche de neuron
Couche* initializer_couche(int num_neurones, int num_xi_par_neurone)
{
    Couche* couche = (Couche*)malloc(sizeof(Couche)); //Allouer de la mémoire pour une nouvelle couche
    
    // Vérifier si l'allocation de mémoire a réussi
    if (couche == NULL)
	{
        printf("Erreur : Impossible d'allouer de la mémoire pour la couche de neurones.\n");
        exit ;
    }
    couche->num_neurones = num_neurones;//Assigner le nombre de neurones dans la couche

    couche->neurones = (Neurone**)malloc(num_neurones * sizeof(Neurone*));//Allouer de la mémoire pour le tableau de pointeurs de neurones
    
    //Vérifier si l'allocation de mémoire a réussi
    if (couche->neurones == NULL)
	{
        printf ("Erreur : Impossible d'allouer de la mémoire pour les neurones de la couche.\n");
        exit ;
    }

    //Initialiser les neurones dans la couche
    for (int i = 0; i < num_neurones; i++)
    {
        couche->neurones[i] = initializer_neurone(num_xi_par_neurone);
    }
    
    return couche;//Retourner le pointeur vers la couche initialisée
}

//Calculer la sortie d'une couche de neurones
int compter_couche_yi(Couche* couche, double xi_valeurs[])
{
    //Pour chaque neurone de la couche
    for (int i = 0; i < couche->num_neurones; i++)
    {
        Neurone *neurone = couche->neurones[i];

        //Attribuer les entrées au neurone
        for (int j = 0; j < neurone->num_xi; j++)
        {
            neurone->xi[j] = xi_valeurs[j]; //Assigner les valeurs d'entrée au neurone
        }

        //Calculer la somme de wi
        double somme = neurone->bias; //On commence avec la valeur de Bias
        for (int j = 0; j < neurone->num_xi; j++)
        {
            somme += neurone->xi[j] * neurone->wi[j]; //Additionner les valeurs d'entrée pondérées
        }

        //Appliquer lese fonctions d'activation en se basant sur le type de neurone
        switch (neurone->activation_function) {
            case 1:
                neurone->yi = relu(somme); //Appliquer la fonction d'activation ReLu
                break;
            case 2:
                neurone->yi = sigmoid(somme); //Appliquer la fonction d'activation Sigmoide
                break;
            case 3:
                //Appliquer la fonction d'activation Softmax
                softmax(neurone->xi, neurone->num_xi, &neurone->yi);
                break;
            default:
                break;
        }
    }
    return 0;
}
#endif
