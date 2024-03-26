#include<stdio.h>
#include<stdlib.h>
#include"Fonctions_activations.h"
#include "Types.h"
#include "Manipulation.h"

//Fonction principale
int main() 
{
    //Variables pour l'exemple d'utilisation
    int num_neurones;//Nombre de neurones
    int num_xi_par_neurone;//Nombre d'entrées par neurone
    int activation_function;//Type de fonction d'activation

    //Demander à l'utilisateur le nombre de neurones 
    printf("Entrer le nombre des neurones: ");
    scanf("%d", &num_neurones);
    
    //Demander à l'utilisateur le nombre d'entrées par neurone
    printf("Entrer le nombre des entres par neurone: ");
    scanf("%d", &num_xi_par_neurone);

    //Demander à l'utilisateur de choisir la fonction d'activation
    int choix_fonction;
    printf("Choisir votre fonction d'activation:\n");
    printf("1. ReLU\n");
    printf("2. Sigmoid\n");
    printf("3. Softmax\n");
    printf("Enter your choice: ");
    scanf("%d", &choix_fonction);

    //Initialiser une couche de neurones
    Couche* Couche = initializer_couche(num_neurones, num_xi_par_neurone);

    //Entrer les valeurs d'entrée pour chaque neurone
    double xi_valeurs[num_xi_par_neurone];
    printf("Entrer les entres pour chaque neurone:\n");
    for (int i = 0; i < num_neurones; i++)
    {
		printf("Neurone %d valeurs des entres:", i+1);
        for (int j = 0; j < num_xi_par_neurone; j++)
        {
            printf("\n Valeur %d:",j+1);
            scanf("%lf", &xi_valeurs[j]);
        }
        //Choisir la fonction d'activation en fonction du choix de l'utilisateur
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
                printf("Choix invalide.");
                return 1;
        }
        //Changer le type de neurone en fonction de la fonction d'activation choisie
        for (int j = 0; j < num_xi_par_neurone; j++)
        {
            Couche->neurones[i]->activation_function = activation_function;
        }
        //Calculer la sortie de la couche
        compter_couche_yi(Couche, xi_valeurs);
    }

    //Afficher la sortie de chaque neurone dans la couche
    printf("Sortie de la couche:\n");
    for (int i = 0; i < Couche->num_neurones; i++)
    {
        printf("Neurone %d sortie: %.2f\n", i+1, Couche->neurones[i]->yi);
    }

    //Libérer la mémoire allouée pour les neurones et la couche de neurones
    for (int i = 0; i < Couche->num_neurones; i++)
    {
        free(Couche->neurones[i]->xi);//Libérer la mémoire allouée pour les valeurs d'entrée du neurone
        free(Couche->neurones[i]->wi);//Libérer la mémoire allouée pour les poids (weights) du neurone
        free(Couche->neurones[i]);//Libérer la mémoire allouée pour le neurone lui-même
    }
    free(Couche->neurones);//Libérer la mémoire allouée pour le tableau de pointeurs de neurones
    free(Couche);//Libérer la mémoire allouée pour la structure de la couche de neurones

    return 0;
}
