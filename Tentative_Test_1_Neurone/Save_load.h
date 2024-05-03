#include <stdio.h>
#include "neurone_types.h"
#include "Types.h"
#include "stdlib.h"

#ifndef NEURONE_SAVELOAD_H
#define NEURONE_SAVELOAD_H

#define MAX_ROWS 100
#define MAX_COLS 3

typedef struct {
    double feature1;
    double feature2;
    double label;
} DataRow;

DataRow data[MAX_ROWS];

int readDataFromFile(const char* filename){
    FILE* file=fopen(filename,"r");
    if (!file){
        printf("Impossible d'ouvrir le fichier.\n");
        return -1;
    }

    int row=0;
    while(row < MAX_ROWS && fscanf(file,"%ld,%lf,%lf\n",&data[row].feature1,&data[row].feature2,&data[row].label)==3){
        row++;
    }

    fclose(file);
    return row;
}

// Sauvegarder les poids et les biais dans un fichier
void sauvegarder_reseau(Reseau* reseau, const char* fichier) {
    FILE* f = fopen(fichier, "wb");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s.\n", fichier);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < reseau->num_couches; ++i) {
        for (int j = 0; j < reseau->couches[i]->num_neurones; ++j) {
            Neurone* neurone = reseau->couches[i]->neurones[j];
            fwrite(neurone->wi, sizeof(double), neurone->num_xi, f);
            fwrite(&neurone->bias, sizeof(double), 1, f);
        }
    }

    fclose(f);
}

// Charger les poids et les biais depuis un fichier
void charger_reseau(Reseau* reseau, const char* fichier) {
    FILE* f = fopen(fichier, "rb");
    if (f == NULL) {
        printf("Erreur lors de l'ouverture du fichier %s.\n", fichier);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < reseau->num_couches; ++i) {
        for (int j = 0; j < reseau->couches[i]->num_neurones; ++j) {
            Neurone* neurone = reseau->couches[i]->neurones[j];
            fread(neurone->wi, sizeof(double), neurone->num_xi, f);
            fread(&neurone->bias, sizeof(double), 1, f);
        }
    }
    fclose(f);
}

#endif
