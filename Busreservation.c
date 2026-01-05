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
void Profile();
void Menu();
void CheckBusDetails();
void BookTicket();
void CancelTicket();

/* Main */
int main() {
    printf("\n\t****** BUS RESERVATION SYSTEM ******\n");
    Login();
    return 0;
}

/* Registration */
void Register() {
    printf("Enter Name: ");
    scanf(" %29[^\n]", reg_name);

    printf("Enter Username: ");
    scanf("%49s", reg_username);

    printf("Enter Password: ");
    scanf("%39s", reg_password);

    Registered = 1;
    printf("\nRegistration Successful! Please Login.\n");
}

/* Login */
void Login() {
    int choice;
    char username[50], password[40];

    while (1) {
        printf("\n1. Register\n2. Login\n3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            Register();
        }
        else if (choice == 2) {
            if (!Registered) {
                printf("Please register first!\n");
                continue;
            }

            printf("Enter Username: ");
            scanf("%49s", username);

            printf("Enter Password: ");
            scanf("%39s", password);

            if (strcmp(username, reg_username) == 0 &&
                strcmp(password, reg_password) == 0) {
                printf("\nLogin Successful. Welcome %s!\n", reg_name);
                Menu();
            } else {
                printf("Invalid Username or Password!\n");
            }
        }
        else if (choice == 3) {
            printf("Thank you! Goodbye.\n");
            break;
        }
        else {
            printf("Invalid choice!\n");
        }
    }
}



/* Menu */
void Menu() {
    int choice;

    while (1) {
        printf("\n=== USER MENU ===");
        printf("\n1. Book Ticket");
        printf("\n2. Cancel Ticket");
        printf("\n3. Check Bus Details");
        printf("\n4. Logout");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: BookTicket(); break;
            case 2: CancelTicket(); break;
            case 3: CheckBusDetails(); break;
            case 4: return;
            default: printf("Invalid choice!\n");
        }
    }
}

/* Check Bus Details */
void CheckBusDetails() {
    int bus, found = 0;

    printf("Enter Bus Number: ");
    scanf("%d", &bus);

    for (int i = 0; i < 3; i++) {
        if (BusNumber[i] == bus) {
            found = 1;
            printf("\nBus Number: %d", BusNumber[i]);
            printf("\nFrom: %s", SourceCity[i]);
            printf("\nTo: %s", DestinationCity[i]);
            printf("\nTotal Seats: %d", TotalSeats[i]);
            printf("\nAvailable Seats: %d", AvailableSeats[i]);
            printf("\nFare: %.2f\n", Fare[i]);
            break;
        }
    }

    if (!found)
        printf("Bus not found!\n");
}

/* Book Ticket with Payment Options */
void BookTicket() {
    int bus, seats, found = 0;
    int paymentChoice;
    float total;

    printf("Enter Bus Number: ");
    scanf("%d", &bus);

    for (int i = 0; i < 3; i++) {
        if (BusNumber[i] == bus) {
            found = 1;

            printf("Enter Seats: ");
            scanf("%d", &seats);

            if (seats > 0 && seats <= AvailableSeats[i]) {

                total = seats * Fare[i];

                printf("\nFare per seat: %.2f", Fare[i]);
                printf("\nTotal Fare: %.2f\n", total);

                /* Payment Options */
                printf("\nSelect Payment Method:");
                printf("\n1. PhonePe");
                printf("\n2. Google Pay");
                printf("\n3. UPI");
                printf("\nEnter choice: ");
                scanf("%d", &paymentChoice);

                if (paymentChoice >= 1 && paymentChoice <= 3) {

                    printf("\nPayment Successful!\n");

                    AvailableSeats[i] -= seats;

                    printf("\n--- BOOKING CONFIRMED ---");
                    printf("\nBus Number: %d", bus);
                    printf("\nSeats Booked: %d", seats);
                    printf("\nAmount Paid: %.2f\n", total);

                } else {
                    printf("\nInvalid Payment Option! Booking Failed.\n");
                }

            } else {
                printf("\nNot enough seats available!\n");
            }
            break;
        }
    }

    if (!found)
        printf("\nInvalid Bus Number!\n");
}


/* Cancel Ticket */
void CancelTicket() {
    int bus, seats, found = 0;

    printf("Enter Bus Number: ");
    scanf("%d", &bus);

    for (int i = 0; i < 3; i++) {
        if (BusNumber[i] == bus) {
            found = 1;

            printf("Enter Seats to Cancel: ");
            scanf("%d", &seats);

            if (seats > 0 && AvailableSeats[i] + seats <= TotalSeats[i]) {
                AvailableSeats[i] += seats;
                printf("Ticket Cancelled Successfully!\n");
            } else {
                printf("Invalid seat count!\n");
            }
            break;
        }
    }

    if (!found)
        printf("Invalid Bus Number!\n");
}
