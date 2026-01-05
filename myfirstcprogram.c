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

/* Main */
int main() {
    printf("\t\t****** BUS RESERVATION SYSTEM ******\n");
    printf("\t\t_______________________________\n");
    Login();
    return 0;
}

/* Registration */
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

/* Login */
void Login() {
    int choice;
    char username[50];
    char password[40];

    printf("\n1. Register\n2. Login\n3. Exit\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        Register();
        Login();
    }
    else if (choice == 2) {
        if (!Registered) {
            printf("Please register first!\n");
            Login();
            return;
        }

        printf("Enter username: ");
        scanf("%s", username);

        printf("Enter password: ");
        scanf("%s", password);

        if (strcmp(username, reg_username) == 0 &&
            strcmp(password, reg_password) == 0) {
            printf("\nLogin successful. Welcome %s\n", username);
            Menu();
        } else {
            printf("Login failed!\n");
            Login();
        }
    }
    else if (choice == 3) {
        printf("Thank you! Goodbye.\n");
    }
    else {
        printf("Invalid choice!\n");
        Login();
    }
}

/* Menu */
void Menu() {
    int choice;

    printf("\n=== USER MENU ===");
    printf("\n1. Book Ticket");
    printf("\n2. Cancel Ticket");
    printf("\n3. Check Bus Details");
    printf("\n4. Logout");
    printf("\nEnter choice: ");
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
            printf("Invalid choice!\n");
            Menu();
    }
}

/* Check Bus Details */
void CheckBusDetails() {
    int inputbusnumber, found = 0;

    printf("Enter Bus Number: ");
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
        printf("\nBus not available!\n");
    }
}

/* Book Ticket with Payment & Fare Calculation */
void BookTicket() {
    int inputbusnumber, numberofseats, found = 0;
    int paymentChoice;
    float totalFare;

    printf("Enter Bus Number: ");
    scanf("%d", &inputbusnumber);

    for (int i = 0; i < 3; i++) {
        if (BusNumber[i] == inputbusnumber) {
            found = 1;

            printf("Enter Number of Seats: ");
            scanf("%d", &numberofseats);

            if (numberofseats <= AvailableSeats[i]) {

                /* Fare Calculation */
                totalFare = numberofseats * Fare[i];

                printf("\nFare per seat: %.2f", Fare[i]);
                printf("\nTotal Fare (%d seats): %.2f\n",
                       numberofseats, totalFare);

                /* Payment Options */
                printf("\nSelect Payment Method:");
                printf("\n1. UPI");
                printf("\n2. PhonePe");
                printf("\n3. Google Pay");
                printf("\nEnter choice: ");
                scanf("%d", &paymentChoice);

                if (paymentChoice >= 1 && paymentChoice <= 3) {
                    printf("\nPayment of %.2f Successful!\n", totalFare);

                    AvailableSeats[i] -= numberofseats;

                    printf("Booking Confirmed!\n");
                    printf("Bus Number: %d\n", inputbusnumber);
                    printf("Seats Booked: %d\n", numberofseats);
                    printf("Amount Paid: %.2f\n", totalFare);
                } else {
                    printf("\nInvalid Payment Option. Booking Failed!\n");
                }

            } else {
                printf("\nError: Not enough seats available!\n");
            }
            break;
        }
    }

    if (!found) {
        printf("\nInvalid Bus Number!\n");
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

            printf("Enter seats to cancel: ");
            scanf("%d", &numberofseats);

            if (AvailableSeats[i] + numberofseats <= TotalSeats[i]) {
                AvailableSeats[i] += numberofseats;
                printf("\nTicket Cancelled Successfully!\n");
            } else {
                printf("\nInvalid cancel seats!\n");
            }
            break;
        }
    }

    if (!found) {
        printf("\nInvalid Bus Number!\n");
    }
}
