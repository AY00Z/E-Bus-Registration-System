#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Stocker les données d'un voyageur
struct Voyageur {
    char nom[50];
    char prenom[50];
    int NumVoyageur;
};

// Stocker les données d'un Bus
struct Bus {
    int NumBus;
    char destination[50];
    int capacite;
    int PlacesDisponibles;
};

// Stocker les données d'une réservation
struct Reservation {
    int NumReservation;
    int NumBus;
    struct Voyageur voyageur;
};

// Créer un compte voyageur
struct Voyageur creerVoyageur() {
    struct Voyageur nouveauVoyageur;
    printf("Nom: ");
    scanf("%s", nouveauVoyageur.nom);
    printf("Prenom: ");
    scanf("%s", nouveauVoyageur.prenom);
    printf("NumVoyageur: ");
    scanf("%d", &nouveauVoyageur.NumVoyageur);
    return nouveauVoyageur;
}

// Créer une nouvelle réservation avec vérification des places disponibles
struct Reservation creerReservation(int numero_reservation, int numero_bus, struct Voyageur voyageur, struct Bus listeBuses[], int nombreBuses) {
    struct Reservation nouvelleReservation;

    // Vérifier si le numéro du bus est valide
    if (numero_bus < 0 || numero_bus >= nombreBuses) {
        printf("Numéro de bus invalide.\n");
        nouvelleReservation.NumReservation = -1; // Indiquer une réservation invalide
        return nouvelleReservation;
    }

    // Vérifier si le bus est complet
    if (listeBuses[numero_bus].PlacesDisponibles <= 0) {
        printf("Le bus est complet. Veuillez attendre un autre bus.\n");
        nouvelleReservation.NumReservation = -1; // Indiquer une réservation invalide
        return nouvelleReservation;
    }

    // Si le bus a des places disponibles, créer la réservation
    nouvelleReservation.NumReservation = numero_reservation;
    nouvelleReservation.NumBus = numero_bus;
    nouvelleReservation.voyageur = voyageur;
    
    // Mettre à jour les places disponibles dans le bus
    listeBuses[numero_bus].PlacesDisponibles--;

    return nouvelleReservation;
}

// Ajouter un nouveau bus à la base de données
struct Bus ajouterBus() {
    struct Bus bus;
    printf("Num Bus : ");
    scanf("%d", &bus.NumBus);
    printf("Destination : ");
    scanf("%s", bus.destination);
    printf("Capacité : ");
    scanf("%d", &bus.capacite);
    printf("Places Disponibles : ");
    scanf("%d", &bus.PlacesDisponibles);
    return bus;
}

// Fonction pour afficher les détails d'une réservation
void afficherDetailsReservation(struct Reservation reservation) {
    printf("Détail de la réservation :\n");
    printf("Num Reservation: %d\n", reservation.NumReservation);
    printf("Numéro du bus : %d\n", reservation.NumBus);
    printf("Num du voyageur : %d\n", reservation.voyageur.NumVoyageur);
}

// Fonction pour changer les détails d'une réservation
void ChangerReservation(struct Reservation *reservation) {
    printf("Enter the new name, surname, and NumVoyageur: ");
    scanf("%s %s %d", reservation->voyageur.nom, reservation->voyageur.prenom, &reservation->voyageur.NumVoyageur);
    printf("Enter the new bus number: ");
    scanf("%d", &reservation->NumBus);
}

// Fonction pour afficher les détails d'un bus
void afficherBus(struct Bus bus) {
    printf("Détail du bus :\n");
    printf("Num Bus : %d\n", bus.NumBus);
    printf("Destination: %s\n", bus.destination);
    printf("Capacité : %d\n", bus.capacite);
    printf("Places Disponibles : %d\n", bus.PlacesDisponibles);
}

int main() {
    struct Bus listeBuses[100];
    struct Reservation listeReservations[1000];

    printf("Hello and welcome to our bus station!\n");

    char action[10];

    while (1) {
        printf("Enter an action (+ to add a reservation, modify to modify a reservation, bus to see details about a bus, res to see details about your reservation, addBus to add a bus, exit to exit): ");
        scanf("%s", action);

        if (strcmp(action, "+") == 0) {
            // Ajouter une réservation
            struct Bus nouvbus = ajouterBus();
            if (nouvbus.NumBus >= 0 && nouvbus.NumBus < 100) {
                listeBuses[nouvbus.NumBus] = nouvbus;

                printf("Enter the reservation number: ");
                int x;
                scanf("%d", &x);

                struct Voyageur nouvVoyageur = creerVoyageur();
                struct Reservation nouvReserv = creerReservation(x, nouvbus.NumBus, nouvVoyageur, listeBuses, 100);

                if (nouvReserv.NumReservation >= 0 && nouvReserv.NumReservation < 1000) {
                    listeReservations[nouvReserv.NumReservation] = nouvReserv;
                    printf("Reservation successful.\n");
                } else {
                    printf("Failed to make a reservation. Please try again.\n");
                }
            } else {
                printf("Invalid bus number.\n");
            }
        } else if (strcmp(action, "modify") == 0) {
            // Modifier une réservation
            printf("Enter the reservation number you want to modify: ");
            int a;
            scanf("%d", &a);
            if (a >= 0 && a < 1000) {
                ChangerReservation(&listeReservations[a]);
                printf("Reservation modified successfully.\n");
            } else {
                printf("Invalid reservation number.\n");
            }
        } else if (strcmp(action, "bus") == 0) {
            // Voir les détails d'un bus
            printf("Enter the bus number you want to see details: ");
            int y;
            scanf("%d", &y);
            if (y >= 0 && y < 100) {
                afficherBus(listeBuses[y]);
            } else {
                printf("Invalid bus number.\n");
            }
        } else if (strcmp(action, "res") == 0) {
            // Voir les détails de la réservation
            printf("Enter the reservation number you want to see details: ");
            int r;
            scanf("%d", &r);
            if (r >= 0 && r < 1000) {
                afficherDetailsReservation(listeReservations[r]);
            } else {
                printf("Invalid reservation number.\n");
            }
        } else if (strcmp(action, "addBus") == 0) {
            // Ajouter un nouveau bus à la base de données
            struct Bus nouvbus = ajouterBus();
            if (nouvbus.NumBus >= 0 && nouvbus.NumBus < 100) {
                listeBuses[nouvbus.NumBus] = nouvbus;
                printf("Bus added to the database.\n");
            } else {
                printf("Invalid bus number.\n");
            }
        } else if (strcmp(action, "exit") == 0) {
            // Quitter le programme
            printf("Take a seat and wait. Exiting the program.\n");
            break;
        } else {
            printf("Invalid action. Please try again.\n");
        }
    }

    return 0;
}
