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

// Calculer la sortie d'une couche de neurones
void compter_couche_yi(Couche* couche, double xi_valeurs[]) {
    for (int i = 0; i < couche->num_neurones; i++) {
        Neurone* neurone = couche->neurones[i];

        for (int j = 0; j < neurone->num_xi; j++) {
            neurone->xi[j] = xi_valeurs[j];
        }

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
}

// Fonction pour calculer la sortie du réseau
void calculer_sortie_reseau(Reseau *reseau, double xi_valeurs[]) {
    Couche *couche_actuelle = reseau->premiere_couche;
    while (couche_actuelle != NULL) {
        compter_couche_yi(couche_actuelle, xi_valeurs);
        xi_valeurs = couche_actuelle->neurones[0]->yi;
        couche_actuelle = couche_actuelle->suivante;
    }
}
