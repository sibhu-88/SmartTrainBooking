#include"header.h"
#include"utils.h"
#include"menu.h"

void add_train(Train **trains) {
    Train *new_train = (Train *)malloc(sizeof(Train));
    if (new_train == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter train number: ");
    scanf("%d", &new_train->number);
    printf("Enter train name: ");
    scanf(" %[^\n]", new_train->name);
    printf("Enter source station: ");
    scanf(" %[^\n]", new_train->source);
    printf("Enter destination station: ");
    scanf(" %[^\n]", new_train->destination);
    printf("Enter total seats: ");
    scanf("%d", &new_train->total_seats);
    new_train->available_seats = new_train->total_seats;

    // Link the new train to the list
    new_train->next = *trains;
    *trains = new_train;

    printf("Train added successfully!\n");

}

void view_trains(Train *trains) {
    if (trains == NULL) {
        printf("No trains available.\n");
        return;
    }

    printf("\nAvailable Trains:\n");
    printf("--------------------------------------------------\n");
    printf("| %-10s | %-20s | %-20s | %-20s | %-12s | %-12s |\n",
           "Number", "Name", "Source", "Destination", "Total Seats", "Available Seats");
    printf("--------------------------------------------------\n");

    Train *current = trains;
    while (current != NULL) {
        printf("| %-10d | %-20s | %-20s | %-20s | %-12d | %-12d |\n",
               current->number, current->name, current->source, current->destination,
               current->total_seats, current->available_seats);
        current = current->next;
    }
    printf("--------------------------------------------------\n");  
    printf("End of train list.\n");
    printf("Press any key to continue...\n");
    getchar();
    getchar();  
}