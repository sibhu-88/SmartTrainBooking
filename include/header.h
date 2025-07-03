#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>

typedef enum
{
    ADMIN,
    CUSTOMER
} UserRole;

typedef struct
{
    char username[20];
    char password[20];
    UserRole role;
    struct User *next;
} User;

typedef enum
{
    MALE = 'M',
    FEMALE = 'F',
    OTHER = 'O'
} Gender;

typedef struct
{
    char first_name[25];
    char last_name[25];
    int age;
    Gender gender;
} Passenger;

typedef struct
{
    int number;
    char name[50];
    char source[50];
    char destination[50];
    int total_seats;
    int available_seats;
    struct Train *next;
} Train;

typedef struct
{
    unsigned long pnr;
    char seat_number[10];
    Passenger passenger;
    Train train;
    char date[11]; // DD-MM-YYYY format
    struct Ticket *next;
} Ticket;

typedef struct
{
    User users[100];
    int count;
    Ticket *bookings;
    Train trains[5];
    int train_count;
} BookingSystem;
