#include "header.h"
#include "utils.h"
// #include"menu.h"

Train *trains = NULL;

int main()
{
	system("clear");
	printf("\n\n\t\t\tWelcome To Train Ticke Booking Software!!!!...\n");
	char user = login();
	printf("\n\t\t\tYou are logged in as: %c\n", user);
	usleep(500000);
	read_trains(&trains);
	if (tolower(user) == 'a')
	{
		printf("\n\t\t\tWelcome to the Admin Page.\n");
		usleep(500000);
		do
		{
			char op;
			admin_menu();
			scanf(" %c", &op);
			switch (tolower(op))
			{
			case 'a':
				printf("\n\t\t\tAdding Train...\n");
				usleep(500000);
				add_train(&trains);
				break;
			case 'v':
				printf("\n\t\t\tViewing Trains...\n");
				usleep(500000);
				view_trains(trains);
				break;
			case 'd':
				printf("\n\t\t\tDeleting Train...\n");
				usleep(500000);
				delete_train(&trains);
				break;
			case 'u':
				printf("\n\t\t\tUpdating Train...\n");
				usleep(500000);
				update_train(&trains);
				break;
			case 's':
				printf("\n\t\t\tSaving Train...\n");
				usleep(500000);
				save_trains(trains);
				break;
			case 'e':
				printf("\n\t\t\tExiting the system...\n");
				usleep(500000);
				printf("\n\t\t\tThank you for using Smart Train Booking System!\n");
				printf("\t\t\tHave a great day!\n");
				usleep(1000000);
				exit(0);
			}
		} while (1);
		usleep(1000000);
	}
	else if (tolower(user) == 'c')
	{
		printf("\n\t\t\tYou are logged in as a customer.\n");
		do
		{
			char op;
			customer_menu();
			scanf(" %c", &op);
			switch (tolower(op))
			{
			case 'b':
				printf("\n\t\t\tBooking Ticket...\n");
				usleep(500000);
				book_ticket();
				break;
			case 't':
				printf("\n\t\t\tTrain Details...\n");
				usleep(500000);
				view_trains(trains);
				break;
			case 'c':
				printf("\n\t\t\tCancel Ticket...\n");
				usleep(500000);
				// cancel_ticket();
				break;
			case 'v':
				printf("\n\t\t\tView Tickets...\n");
				usleep(500000);
				// view_tickets();
				break;
			case 'e':
				printf("\n\t\t\tExiting the system...\n");
				usleep(500000);
				printf("\n\t\t\tThank you for using Smart Train Booking System!\n");
				printf("\t\t\tHave a great day!\n");
				usleep(1000000);
				exit(0);
			default:
				printf("\n\t\t\tInvalid option. Please try again.\n");
				usleep(1000000);
			}

		} while (1);
		usleep(1000000);
	}
	else
	{
		printf("\n\t\t\tInvalid user type. Exiting...\n");
		usleep(1000000);
		exit(1);
	}
}
