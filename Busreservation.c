#include <stdio.h>
#include <string.h>

/* Registered user data */
char reg_name[30];
char reg_username[50];
char reg_password[40];
int Registered = 0;

/* Bus details */
int BusNumber[3] = {202, 203, 204};
char SourceCity[3][50] = {"Bihar", "Patna", "Delhi"};
char DestinationCity[3][50] = {"Delhi", "Lucknow", "Agra"};
int TotalSeats[3] = {50, 40, 45};
int AvailableSeats[3] = {50, 40, 45};
float Fare[3] = {500.0, 600.0, 700.0};

/* Function Declaration */
void Register();
void Login();
void Menu();
void CheckBusDetails();
void BookTicket();
void CancelTicket();

/* Menu Function */
int main() {
    printf("\t\t****** BUS RESERVATION SYSTEM ******\n");
    printf("\t\t_______________________________\n");
    Login();
    return 0;
}

/* Registration Function */
void Register() {
    printf("Enter name: ");
    scanf("%s", reg_name);

    printf("Enter Username: ");
    scanf("%s", reg_username);

    printf("Enter Password: ");
    scanf("%s", reg_password);

    Registered = 1;
    printf("\nRegistration successful! Please login.\n");
}

/* Login Function */
void Login() {
    int choice;
    char username[50];
    char password[40];

    printf("\n1. Register\n");
    printf("2. Login\n");
    printf("3. Exit\n");
    printf("Please enter your choice: ");
    scanf("%d", &choice);
    printf("\n");

    if (choice == 1) {
        Register();
        Login();
    } else if (choice == 2) {
        if (!Registered) {
            printf("Please register first!\n");
            Login();
            return;
        }

        printf("Please enter username: ");
        scanf("%s", username);

        printf("Please enter password: ");
        scanf("%s", password);

        if (strcmp(username, reg_username) == 0 && strcmp(password, reg_password) == 0) {
            printf("Login successful. Welcome, %s\n", username);
            Menu();
        } else {
            printf("Login failed for user - %s\n", username);
            Login();  // retry login
        }
    } else if (choice == 3) {
        printf("Exiting program. Goodbye!\n");
        return;
    } else {
        printf("Invalid choice! Try again.\n");
        Login();
    }
}

/* Cancel Ticket */
void CancelTicket() {
    int inputbusnumber, numberofseats, found = 0;

    printf("Enter Bus Number: ");
    scanf("%d", &inputbusnumber);

    for (int i = 0; i < 3; i++) {
        if (BusNumber[i] == inputbusnumber) {
            found = 1;
            printf("Enter Number Of Seats to cancel: ");
            scanf("%d", &numberofseats);

            if (AvailableSeats[i] + numberofseats <= TotalSeats[i]) {
                AvailableSeats[i] += numberofseats;
                printf("\nCancellation Successful! %d seats canceled on Bus Number %d\n", numberofseats, inputbusnumber);
            } else {
                printf("\nError - Number of cancel seats exceeds total seats.\n");
            }
            break;
        }
    }

    if (!found) {
        printf("\nPlease Enter correct Bus Number!\n");
    }
}

/* Book Ticket */
void BookTicket() {
    int inputbusnumber, numberofseats, found = 0;

    printf("Enter Bus Number: ");
    scanf("%d", &inputbusnumber);

    for (int i = 0; i < 3; i++) {
        if (BusNumber[i] == inputbusnumber) {
            found = 1;
            printf("Enter Number of seats: ");
            scanf("%d", &numberofseats);

            if (numberofseats <= AvailableSeats[i]) {
                AvailableSeats[i] -= numberofseats;
                printf("\nBooking Successful! %d seats booked on Bus Number %d\n", numberofseats, inputbusnumber);
            } else {
                printf("\nError - Not enough available seats.\n");
            }
            break;
        }
    }

    if (!found) {
        printf("\nPlease enter correct bus number.\n");
    }
}

/* Check Bus Details */
void CheckBusDetails() {
    int inputbusnumber, found = 0;

    printf("Please Enter Bus Number: ");
    scanf("%d", &inputbusnumber);

    for (int i = 0; i < 3; i++) {
        if (BusNumber[i] == inputbusnumber) {
            found = 1;
            printf("\nBus Number: %d", BusNumber[i]);
            printf("\nSource City: %s", SourceCity[i]);
            printf("\nDestination City: %s", DestinationCity[i]);
            printf("\nTotal Seats: %d", TotalSeats[i]);
            printf("\nAvailable Seats: %d", AvailableSeats[i]);
            printf("\nFare: %.2f\n", Fare[i]);
            break;
        }
    }

    if (!found) {
        printf("\nThis Bus is not Available!\n");
    }
}

/* User Menu */
void Menu() {
    int choice;

    printf("\n\n=== User Menu ===");
    printf("\n1. Book a Ticket");
    printf("\n2. Cancel a Ticket");
    printf("\n3. Check Bus Status");
    printf("\n4. Logout");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            BookTicket();
            Menu();
            break;

        case 2:
            CancelTicket();
            Menu();
            break;

        case 3:
            CheckBusDetails();
            Menu();
            break;

        case 4:
            Login();
            break;

        default:
            printf("Invalid choice! Try again.\n");
            Menu();
            break;
    }
}
