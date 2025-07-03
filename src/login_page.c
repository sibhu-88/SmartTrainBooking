#include "header.h"
#include "utils.h"
#include "menu.h"

User *user = NULL; // Global user pointer

char login(void)
{
	char op;
	int flag = 1;
	do
	{
		login_menu();
		scanf(" %c", &op);
		switch (tolower(op))
		{
		case 'l':
		{
			char role = login_page(user);
			if (role == 'A')
			{
				return 'A';
			}
			else if (role == 'C')
			{
				return 'C';
			}
			flag = 0;
			break;
		}
		case 'r':
			register_page(&user);
			break;
		case 'q':
			flag = 0;
			printf("\n\t\t\tThank you for using Smart Train Booking System!\n");
			printf("\t\t\tHave a great day!\n");
			usleep(1000000);
			exit(0);
			break;
		default:
			break;
		}
		if (flag)
		{
			printf("\n\t\t\tPress Enter to continue...");
			getchar();
		}
	} while (flag);
	return 0;
}

char login_page(User *user)
{
	char username[50], password[50];
	int flag = 1;
	do
	{
		system("clear");
		printf("\n\n\t\t\t\t\tLogin Page\n\n");
		printf("\n\t\t\tEnter username: ");
		scanf("%s", username);
		printf("\n\t\t\tEnter password: ");
		scanf("%s", password);
		char role = check_user(user, username, password);
		if (role == 0)
		{
			printf("\n\t\t\tInvalid username or password. Please try again.\n");
			usleep(1000000);
			continue;
		}
		else
		{
			printf("\n\t\t\tLogin successful! Welcome, %s.\n", username);
			usleep(1000000);
			return role;
		}
	} while (flag);
	return 0; // Return 0 if login fails
}

void register_page(User **user)
{
	char username[50], password[50], confirm_password[50];
	char role;
	int flag = 1;
	do
	{
		system("clear");
		printf("\n\n\t\t\t\t\tRegister Page\n\n");
		printf("\n\t\t\tEnter new username: ");
		scanf("%s", username);
		printf("\n\t\t\tEnter new password: ");
		scanf("%s", password);
		printf("\n\t\t\tEnter confirm password: ");
		scanf("%s", confirm_password);
		printf("\n\t\t\tSelect role (A for Admin, C for Customer): ");
		scanf(" %c", &role);
		if (strcmp(password, confirm_password) != 0)
		{
			printf("\n\t\t\tPasswords do not match. Please try again.\n");
			usleep(1000000); // Sleep for 1 second
			continue;
		}
		flag = 0;
	} while (flag);
	add_user(user, username, password, role);
	save_users(*user); // Pass the dereferenced user pointer
	printf("\n\t\t\tRegistration successful for user: %s\n", username);
}

void add_user(User **user, char *username, char *password, char role)
{
	User *new_user = (User *)malloc(sizeof(User));
	if (new_user == NULL)
	{
		printf("Memory allocation failed!\n");
		return;
	}
	strcpy(new_user->username, username);
	strcpy(new_user->password, password);

	if (tolower(role) == 'a')
	{
		new_user->role = ADMIN;
	}
	else if (tolower(role) == 'c')
	{
		new_user->role = CUSTOMER;
	}
	else
	{
		printf("Invalid role selected. Defaulting to Customer.\n");
		new_user->role = CUSTOMER;
	}

	new_user->next = *user;
	*user = new_user;
}

char check_user(User *user, char *username, char *password)
{
	FILE *user_file = fopen("user_credential.xls", "r");
	if (user_file == NULL)
	{
		printf("Error opening user credential file for reading.\n");
		return 0; // Indicate failure
	}

	char line[256];
	while (fgets(line, sizeof(line), user_file))
	{
		char *file_username = strtok(line, "\t");
		if (!file_username)
			continue;
		char *file_password = strtok(NULL, "\t");
		if (!file_password)
			continue;
		char *user_role = strtok(NULL, "\t");
		if (!user_role)
			continue;

		user_role[strcspn(user_role, "\n")] = 0;

		if (strcmp(file_username, username) == 0 && strcmp(file_password, password) == 0)
		{
			return (strcmp(user_role, "ADMIN") == 0) ? 'A' : 'C';
		}
	}
	fclose(user_file);
	return 0;
}

void save_users(User *users)
{
	if (users == NULL)
	{
		printf("No Users To save\n");
		return;
	}

	FILE *user_file = fopen("user_credential.xls", "w"); // Corrected to "w"
	if (user_file == NULL)
	{
		printf("Error opening file for writing\n");
		return;
	}
	fprintf(user_file, "User  name\tpassword\tUser  Role\n");

	User *current = users;
	char role[15];
	while (current != NULL)
	{
		if (current->role == 0)
		{
			strcpy(role, "ADMIN");
		}
		else if (current->role == 0)
		{
			strcpy(role, "CUSTOMER");
		}

		fprintf(user_file, "%s\t%s\t%s\n", current->username, current->password, role);
		current = current->next;
	}
	fclose(user_file);
	printf("User  details saved to user_credential.xls successfully.\n");
}
