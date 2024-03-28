#ifndef NEURONE_MANIPULATION_H
#define NEURONE_MANIPULATION_H

// Initialiser un neurone avec un nombre d'entrées donné
Neurone* initializer_neurone(int num_xi) {
    Neurone* neurone = (Neurone*)malloc(sizeof(Neurone));
    if (neurone == NULL) {
        printf("Erreur : Impossible d'allouer de la mémoire pour le neurone.\n");
        exit;
    }

    neurone->num_xi = num_xi;
    neurone->xi = (double*)malloc(num_xi * sizeof(double));
    neurone->wi = (double*)malloc(num_xi * sizeof(double));
    if (neurone->xi == NULL || neurone->wi == NULL) {
        printf("Erreur : Impossible d'allouer de la mémoire pour les entrées ou les poids du neurone.\n");
        exit;
    }

    for (int i = 0; i < num_xi; i++) {
        neurone->wi[i] = ((double)rand() / RAND_MAX) * 2 - 1;
    }
    neurone->bias = ((double)rand() / RAND_MAX) * 2 - 1;

    return neurone;
}

//Demander à l'utilisateur de choisir la fonction d'activation
int choisir_type_activation() {
    int choix;
    printf("Choisir le type de fonction d'activation :\n");
    printf("1. ReLU\n");
    printf("2. Sigmoid\n");
    printf("3. Softmax\n");
    printf("Votre choix : ");
    scanf("%d", &choix);
    return choix;
}
neurone->activation_function=choix;

// Initialiser une couche de neurones avec un nombre donné de neurones et d'entrées par neurone
Couche* initializer_couche(int num_neurones, int num_xi_par_neurone) {
    Couche* couche = (Couche*)malloc(sizeof(Couche));
    if (couche == NULL) {
        printf("Erreur : Impossible d'allouer de la mémoire pour la couche de neurones.\n");
        exit;
    }

    couche->num_neurones = num_neurones;
    couche->neurones = (Neurone**)malloc(num_neurones * sizeof(Neurone*));
    if (couche->neurones == NULL) {
        printf("Erreur : Impossible d'allouer de la mémoire pour les neurones de la couche.\n");
        exit;
    }

    for (int i = 0; i < num_neurones; i++) {
        couche->neurones[i] = initializer_neurone(num_xi_par_neurone);
    }

    couche->suivante = NULL;

    return couche;
}

// Initialiser un réseau de neurones avec une première couche donnée
Reseau* initializer_reseau(Couche* premiere_couche) {
    Reseau* reseau = (Reseau*)malloc(sizeof(Reseau));
    if (reseau == NULL) {
        printf("Erreur : Impossible d'allouer de la mémoire pour le réseau neuronal.\n");
        exit;
    }

    reseau->premiere_couche = premiere_couche;

    return reseau;
}

// Remplir la première couche du réseau avec des valeurs aléatoires pour les poids et le biais
Couche* remplir_premiere_couche(Reseau* reseau, int num_neurones, int num_xi_par_neurone, int activation_function) {
    if (reseau == NULL) {
        printf("Erreur : Réseau non initialisé.\n");
        return NULL;
    }

    Couche* premiere_couche = initializer_couche(num_neurones, num_xi_par_neurone, activation_function);
    reseau->premiere_couche = premiere_couche;

    return premiere_couche;
}

// Calculer la sortie d'une couche de neurones
double compter_couche_yi(Couche* couche) {
    for (int i = 0; i < couche->num_neurones; i++) {
        Neurone* neurone = couche->neurones[i];

        double somme = neurone->bias;
        for (int j = 0; j < neurone->num_xi; j++) {
            somme += neurone->xi[j] * neurone->wi[j];
        }

        switch (neurone->activation_function) {
            case 1:
                neurone->yi = relu(somme);
                break;
            case 2:
                neurone->yi = sigmoid(somme);
                break;
            case 3:
                softmax(neurone->xi, neurone->num_xi, &neurone->yi);
                break;
            default:
                break;
        }
    }
    return neurone->yi;
}
