#include "header.h"
#include "utils.h"
#include "menu.h"

void book_ticket()
{
    Ticket ticket;
    Train train;
    int train_number;
    char date[11];
    static int seat_number = 1;
    unsigned long pnr = generate_pnr();
    char gender;

    printf("\n\t\t\tBooking Details:\n");
    printf("\n\t\t\tEnter Train Number: ");
    scanf("%d", &train_number);

    printf("\n\t\t\tEnter passenger count: ");
    scanf("%d", &ticket.passenger_count);
    if (ticket.passenger_count <= 0)
    {
        printf("\n\t\t\tInvalid passenger count. Please try again.\n");
        return;
    }

    if (train.available_seats <= 0)
    {
        ticket.status = waiting;
        ticket.waiting_count += ticket.passenger_count;
    }

    ticket.passenger = (Passenger *)malloc(ticket.passenger_count * sizeof(Passenger));
    if (ticket.passenger == NULL)
    {
        printf("\n\t\t\tMemory allocation failed. Please try again.\n");
        return;
    }

    for (int i = 0; i < ticket.passenger_count; i++)
    {
        printf("\n\t\tPassenger %d:\n", i + 1);
        printf("\n\t\t\tEnter Passenger First Name: ");
        scanf("%s", ticket.passenger[i].first_name);
        printf("\n\t\t\tEnter Passenger Last Name: ");
        scanf("%s", ticket.passenger[i].last_name);
        printf("\n\t\t\tEnter Passenger Age: ");
        scanf("%d", &ticket.passenger[i].age);
        printf("\n\t\t\tEnter Passenger Gender (M/F/O): ");
        scanf(" %c", &gender);
        ticket.passenger[i].gender = gender; // Store gender in the Passenger struct
    }

    printf("\n\t\t\tEnter Date of Journey (DD-MM-YYYY): ");
    scanf("%s", date);

    ticket.pnr = pnr;
    ticket.train.number = train_number;
    if (train.available_seats <= 0)
    {
        ticket.status = waiting;
        ticket.waiting_count += ticket.passenger_count;
    }
    else
    {
        ticket.status = confirmed;
        ticket.train.available_seats -= ticket.passenger_count;
    }
    strcpy(ticket.date, date);
    ticket.passenger->seat_number = seat_number; // Ensure seat_number is a valid member of Train
    seat_number += ticket.passenger_count;       // Increment seat number for next booking

    system("clear");
    printf("\n\t\t\tTicket booked successfully!\n");
    printf("\n\t\t\tPNR: %lu\n", ticket.pnr);
    printf("\n\t\t\tTrain Number: %d\n", ticket.train.number);
    printf("\n\t\t\tDate of Journey: %s\n", ticket.date);
    printf("\n\t\t\tPassenger Details:\n");

    for (int i = 0; i < ticket.passenger_count; i++)
    {

        printf("\n\t\t\tPassenger %d:\n", i + 1);
        printf("\t\t\tFirst Name: %s\n", ticket.passenger[i].first_name);
        printf("\t\t\tLast Name: %s\n", ticket.passenger[i].last_name);
        printf("\t\t\tAge: %d\n", ticket.passenger[i].age);
        printf("\t\t\tGender: %c\n", ticket.passenger[i].gender);
        if (ticket.status == waiting)
        {
            printf("\n\t\t\tYour ticket is on the waiting list.\n");
            printf("\t\t\tYou will be notified once your ticket is confirmed.\n");
            printf("\t\t\tWaiting Count: %d\n", ticket.waiting_count);
        }
        else
            printf("\t\t\tSeat Number: %d\n", ticket.passenger->seat_number + i);
    }
    printf("\n\t\t\tThank you for booking with us!\n");
    printf("\t\t\tHave a great journey!\n");

    printf("\n\t\t\tPress any key to continue...\n");
    getchar();
    getchar();

    // Free allocated memory for passengers
    free(ticket.passenger);
}

unsigned long generate_pnr(void)
{
    srand(time(NULL));

    unsigned long pnr = rand() % 9000000000 + 1000000000;
    return pnr;
}
