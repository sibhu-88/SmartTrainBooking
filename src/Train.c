#include "header.h"
#include "utils.h"
#include "menu.h"

void add_train(Train **trains)
{
    Train *new_train = (Train *)malloc(sizeof(Train));
    if (new_train == NULL)
    {
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
    new_train->next = NULL;

    if (*trains == NULL)
    {
        *trains = new_train;
    }
    else
    {
        Train *current = *trains;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = new_train;
    }

    printf("Train added successfully!\n");
}

void delete_train(Train **trains)
{
    if (*trains == NULL)
    {
        printf("No trains available to delete.\n");
        return;
    }
    int train_number;
    printf("Enter the train number to delete: ");
    scanf("%d", &train_number);
    Train *current = *trains;
    Train *previous = NULL;
    while (current != NULL && current->number != train_number)
    {
        previous = current;
        current = current->next;
    }
    if (current == NULL)
    {
        printf("Train with number %d not found.\n", train_number);
        return;
    }
    if (previous == NULL)
    {
        *trains = current->next;
    }
    else
    {
        previous->next = current->next;
    }
    free(current);
    printf("Train with number %d deleted successfully.\n", train_number);
    printf("Press any key to continue...\n");
    getchar();
    getchar();
}

void update_train(Train **trains)
{
    if (*trains == NULL)
    {
        printf("No trains available to update.\n");
        return;
    }

    int train_number;
    printf("Enter the train number to update: ");
    scanf("%d", &train_number);

    Train *current = *trains;
    while (current != NULL && current->number != train_number)
    {
        current = current->next;
    }
    if (current == NULL)
    {
        printf("Train with number %d not found.\n", train_number);
        return;
    }

    train_update_menu();
    char option;
    scanf(" %c", &option);
    switch (tolower(option))
    {
    case 'n':
        printf("Enter new train number: ");
        scanf("%d", &current->number);
        break;
    case 's':
        printf("Enter new source station: ");
        scanf(" %[^\n]", current->source);
        break;
    case 'd':
        printf("Enter new destination station: ");
        scanf(" %[^\n]", current->destination);
        break;
    case 't':
        int new_total_seats;
        printf("Enter new total seats: ");
        scanf("%d", &new_total_seats);
        if (new_total_seats < current->total_seats)
        {
            int seats_to_release = current->total_seats - new_total_seats;
            current->available_seats -= seats_to_release;
        }
        else if (new_total_seats > current->total_seats)
        {
            int seats_to_add = new_total_seats - current->total_seats;
            current->available_seats += seats_to_add;
        }
        current->total_seats = new_total_seats;
        break;
    case 'e':
        printf("Exiting update menu.\n");
        usleep(500000);
        return;
    default:
        printf("Invalid option. Please try again.\n");
        break;
    }
    printf("Train updated successfully!\n");
    printf("Press any key to continue...\n");
    getchar();
    getchar();
}

void view_trains(Train *trains)
{
    if (trains == NULL)
    {
        printf("No trains available.\n");
        printf("Press any key to continue...\n");
        getchar();
        getchar();
        return;
    }

    printf("\nAvailable Trains:\n");
    printf("--------------------------------------------------\n");
    printf("| %-10s | %-20s | %-20s | %-20s | %-12s | %-12s |\n",
           "Number", "Name", "Source", "Destination", "Total Seats", "Available Seats");
    printf("--------------------------------------------------\n");

    Train *current = trains;
    while (current != NULL)
    {
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

void save_trains(Train *trains)
{
    if (trains == NULL)
    {
        printf("No trains available to save to file.\n");
        return;
    }

    FILE *train_file = fopen("train_details.xls", "w"); // Corrected to "w"
    if (train_file == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    fprintf(train_file, "Train Number\tTrain Name\tSource\tDestination\tTotal Seats\tAvailable Seats\n");
    Train *current = trains;
    while (current != NULL)
    {
        fprintf(train_file, "%d\t%s\t%s\t%s\t%d\t%d\n",
                current->number, current->name, current->source,
                current->destination, current->total_seats, current->available_seats);
        current = current->next;
    }
    fclose(train_file);
    printf("Train details saved to train_details.xls successfully.\n");
}

void read_trains(Train **trains)
{
    FILE *train_file = fopen("train_details.xls", "r");
    if (train_file == NULL)
    {
        printf("Error opening train details file for reading.\n");
        return;
    }

    char line[256];
    fgets(line, sizeof(line), train_file); // Skip header line
    while (fgets(line, sizeof(line), train_file))
    {
        Train *new_train = (Train *)malloc(sizeof(Train));
        if (new_train == NULL)
        {
            printf("Memory allocation failed!\n");
            fclose(train_file);
            return;
        }
        sscanf(line, "%d\t%[^\t]\t%[^\t]\t%[^\t]\t%d\t%d",
               &new_train->number, new_train->name, new_train->source,
               new_train->destination, &new_train->total_seats, &new_train->available_seats);
        new_train->next = NULL;

        if (*trains == NULL)
        {
            *trains = new_train;
        }
        else
        {
            Train *current = *trains;
            while (current->next != NULL)
            {
                current = current->next;
            }
            current->next = new_train;
        }
    }
    fclose(train_file);
}