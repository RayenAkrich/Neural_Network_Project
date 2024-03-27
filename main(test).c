#include <stdio.h>
#include <stdlib.h>
#include "Fonctions_activations.h"
#include "Types.h"
#include "Manipulation.h"
#include "Outils_optimisation.h"
#include <time.h>


//Fonction principale
int main() 
{
    srand(time(NULL));//Initialisation du random
    int num_couches;
    int* num_neurones;//Tableau des nombres de neurones par couche
    int* num_xi_par_neurone;//Tableau des nombres d'entrées par neurone dans une couche
    int choix_fonction;//Type de fonction d'activation(prendra 1 , 2 ou 3)

    //Saisie du nombres de couches,neurones et entrées par couches
    Saisie(&num_couches,&num_neurones,&num_xi_par_neurone);

    //Initialisation du réseau
    Reseau* reseau=initializer_reseau(num_couches,num_neurones,num_xi_par_neurone);

    //Entrer les valeurs d'entrée pour la premiere couche
    double*** xi_values;
    xi_values=SaisieValeurs(num_couches,reseau,num_neurones,num_xi_par_neurone);

    // Calculer la sortie uniquement pour les couches pour lesquelles les valeurs ont été saisies
    for(int i = 0; i < num_couches; i++) {
        if (xi_values[i] != NULL) { // Vérifier si les valeurs ont été saisies pour cette couche
            for(int j=0; j<reseau->couches[i]->num_neurones;j++) {
                reseau->couches[i]->neurones[j]->yi = compter_couche_yi(reseau->couches[i], xi_values[i][j]);
            }
        }
    }

    // Afficher la sortie de la première couche seulement
    printf("Sortie de la premiere couche :\n");
    for (int j = 0; j < reseau->couches[0]->num_neurones; j++) {
        printf("Sortie du neurone %d : %lf\n",j+1,reseau->couches[0]->neurones[j]->yi);
    }


    // Libérer la mémoire allouée pour les neurones et le réseau neuronal
    for (int i=0;i<num_couches; i++) {
        for (int j = 0; j < reseau->couches[i]->num_neurones; j++) {
            free(reseau->couches[i]->neurones[j]->xi);
            free(reseau->couches[i]->neurones[j]->wi);
            free(reseau->couches[i]->neurones[j]);
        }
        free(reseau->couches[i]->neurones);
        free(reseau->couches[i]);
    }
    // Libérer la mémoire allouée pour xi_values
    for (int i = 0; i < num_couches; i++) {
        for (int j = 0; j < num_neurones[i]; j++) {
            free(xi_values[i][j]);
        }
        free(xi_values[i]);
    }
    free(xi_values);
    free(reseau->couches);
    free(reseau);

    return 0;
}
