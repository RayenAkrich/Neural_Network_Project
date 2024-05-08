#include <stdio.h>
#include "stdlib.h"

#ifndef NEURONE_SAVELOAD_H
#define NEURONE_SAVELOAD_H

// Sauvegarder les poids et les biais dans un fichier texte
void sauvegarder_reseau(Reseau* reseau, const char* fichier) {
    FILE* f = fopen(fichier, "w");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s.\n", fichier);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < reseau->num_couches; ++i) {
        for (int j = 0; j < reseau->couches[i]->num_neurones; ++j) {
            Neurone* neurone = reseau->couches[i]->neurones[j];
            for (int k = 0; k < neurone->num_xi; ++k) {
                fprintf(f, "%lf ", neurone->wi[k]);
            }
            fprintf(f, "%lf\n", neurone->bias);
        }
    }

    fclose(f);
}

// Charger les poids et les biais depuis un fichier texte
void charger_reseau(Reseau* reseau, const char* fichier) {
    FILE* f = fopen(fichier, "r");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s.\n", fichier);
        exit(EXIT_FAILURE);
    }

    // Vérifier la taille du fichier
    fseek(f, 0, SEEK_END); // Se déplacer à la fin du fichier
    long taille_fichier = ftell(f); // Obtenir la taille du fichier
    fseek(f, 0, SEEK_SET); // Se déplacer au début du fichier

    if (taille_fichier == 0) {
        printf("Le fichier %s est vide. Aucune donnée à charger.\n", fichier);
        fclose(f);
        return; // Quitter la fonction si le fichier est vide
    }

    for (int i = 0; i < reseau->num_couches; ++i) {
        for (int j = 0; j < reseau->couches[i]->num_neurones; ++j) {
            Neurone* neurone = reseau->couches[i]->neurones[j];
            for (int k = 0; k < neurone->num_xi; ++k) {
                fscanf(f, "%lf", &(neurone->wi[k]));
            }
            fscanf(f, "%lf", &(neurone->bias));
        }
    }

    fclose(f);
}

#endif
