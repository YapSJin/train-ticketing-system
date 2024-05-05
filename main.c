#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#pragma warning(disable : 4996)

#define SIZE 100

typedef struct {
    char ID[7], username[50], password[50], gender, ic_num[13], phoneNo[12];
} User;

typedef struct {
    char employeeID[10], employeeName[40], password[20], passRecovery[20], position[30], gender;
    int age;
} Staff;

struct Ticket {
    char destination[50], trainID[6], departureDate[11], departureTime[6];
    double price;
};

typedef struct {
    char bookingID[6], memberID[7], bookingDate[11];
    struct Ticket ticket;
    char seats[4][5];
    int quantity;
    double total;
    char status[20];
} MemberTickets;

// Member Functions
void member();
void newMember();
void memberLogin();
void memberInfo(User);

void buyTicket(char);
void viewTickets(User);
void changeTicket(char);
void cancelTicket(char);

// Staff Functions
void staff();
void staffLogin();
void recoverPass();

void memberMenu();
void viewMembers();
void deleteMember();

void staffMenu();
void displayStaff();
void newStaff();
void editStaff();
void deleteStaff();

// void scheduleMenu();

void ticketMenu();
void searchTicket();
void addTicket();
void editTicket();
void deleteTicket();

// Misc Functions
FILE* openFile(char*, char*);
void generateID(char, int, char*);

void memberHeader();
void ticketsHeader();
void displayTickets();
void memberTicketHeader();
void memberTickets(char, int);

void main() {
    int choice;
    do {
        system("cls");
        printf("_____   ____________________________^__\n");
        printf(" ___ |||  ___   ___   ___  |   __  ,----\n");
        printf("|   |||| |   | |   | |   | |  |  | |_____\\\n");
        printf("|___|||| |___| |___| | O | |  |  |        \\\n");
        printf("     |||             |___| |  |__|         )\n");
        printf("_____|||___________________|______________/\n");
        printf("     |||                             /\n");
        printf("-----'''----------------------------'\n");

        printf("================================================\n\nWelcome to GS Train Systems!\n\n1. Member\n2. Staff\n3. Exit\n\n");

        printf("Enter option: ");
        rewind(stdin);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                member();
                break;
            case 2:
                staff();
                break;
            case 3:
                printf("\nHave a good day!\n");
                break;
            default:
                printf("\nInvalid option!\n");
                break;
        }
    } while (choice != 3);
    system("pause");
}

void member() {
    int choice;
    do {
        system("cls");
        printf(" _   _               ___               _\n");
        printf("| | | |___ ___ _ _  | _ \\__ _ _ _  ___| |\n");
        printf("| |_| (_-</ -_) '_| |  _/ _` | ' \\/ -_) |\n");
        printf(" \\___//__/\\___|_|   |_| \\__,_|_||_\\___|_|\n\n");

        printf("1. Login\n2. Register\n3. Back\n\n");

        printf("Enter option: ");
        rewind(stdin);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                memberLogin();
                break;
            case 2:
                newMember();
                break;
            case 3:
                break;
            default:
                printf("\nInvalid option!\n");
                system("pause");
                break;
        }
    } while (choice != 3);
}

void staff() {
    int choice;
    do {
        system("cls");
        printf(" ___ _         __  __   ___               _\n");
        printf("/ __| |_ __ _ / _|/ _| | _ \\__ _ _ _  ___| |\n");
        printf("\\__ \\  _/ _` |  _|  _| |  _/ _` | ' \\/ -_) |\n");
        printf("|___/\\__\\__,_|_| |_|   |_| \\__,_|_||_\\___|_|\n\n");

        printf("1. Login\n2. Forgot Password\n3. Back\n\n");

        printf("Enter option: ");
        rewind(stdin);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                staffLogin();
                break;
            case 2:
                recoverPass();
                system("pause");
                break;
            case 3:
                break;
            default:
                printf("\nInvalid option!\n");
                system("pause");
                break;
        }
    } while (choice != 3);
}

void staffLogin() {
    Staff currentStaff;
    char username[50], password[50];

    FILE* file = openFile("staff.bin", "rb");

    printf("\nEnter Username: ");
    rewind(stdin);
    scanf("%[^\n]", &username);

    printf("Password: ");
    rewind(stdin);
    scanf("%[^\n]", &password);

    int found = 0;
    while (fread(&currentStaff, sizeof(Staff), 1, file)) {
        if (strcmp(currentStaff.employeeID, username) == 0 && strcmp(currentStaff.password, password) == 0) {
            found = 1;
            break;
        }
    }

    if (found) {
        int choice;
        do {
            system("cls");
            printf("Welcome %s, what would you like to do?\n\n", currentStaff.employeeID);
            printf("1. User Management\n2. Staff Management\n3. Schedule Management\n4. Ticket Management\n5. Back\n\n");

            printf("Enter option: ");
            rewind(stdin);
            scanf("%d", &choice);
            switch (choice) {
                case 1:
                    memberMenu();
                    break;
                case 2:
                    staffMenu();
                    break;
                case 3:
                    // scheduleMenu();
                    break;
                case 4:
                    ticketMenu();
                    break;
                case 5:
                    break;
                default:
                    printf("\nInvalid option!\n");
                    system("pause");
                    break;
            }
        } while (choice != 5);
    } else {
        printf("\nInvalid Username or password.\n");
        system("pause");
    }
    fclose(file);
}

void recoverPass() {
    Staff staff[SIZE];
    int count = 0, i, found = 0;
    char enteredID[10];

    FILE* fptr = openFile("staff.bin", "rb+");

    while (fread(&staff[count], sizeof(Staff), 1, fptr) == 1) {
        count++;
    }

    printf("\nEnter the Employee ID to recover: ");
    rewind(stdin);
    scanf("%s", enteredID);

    for (i = 0; i < count; i++) {
        if (strcmp(staff[i].employeeID, enteredID) == 0) {
            found = 1;
            break;
        }
    }

    if (found) {
        printf("Enter your new password: ");
        rewind(stdin);
        scanf("%[^\n]", &staff[i].password);

        fseek(fptr, i * sizeof(Staff), SEEK_SET);

        fwrite(&staff[i], sizeof(Staff), 1, fptr);

        printf("\nEmployee password changed successfully.\n\n");
    } else {
        printf("\nEmployee not found.\n\n");
    }
    fclose(fptr);
}

// Member Functions
void newMember() {
    User newUser, existingUser;

    system("cls");
    printf("Member Registration\n=====================\n");

    FILE* file = openFile("user.bin", "ab+");

    generateID('M', 6, newUser.ID);

    printf("Enter Username: ");
    rewind(stdin);
    scanf("%[^\n]", &newUser.username);

    int usernameExists = 0;
    while (fread(&existingUser, sizeof(User), 1, file)) {
        if (strcmp(existingUser.username, newUser.username) == 0) {
            printf("Username '%s' already exists. Please enter a different username.\n", newUser.username);
            usernameExists = 1;
            break;
        }
    }

    if (!usernameExists) {
        printf("Enter Password: ");
        rewind(stdin);
        scanf("%[^\n]", &newUser.password);

        do {
            printf("Enter Gender (M/F): ");
            rewind(stdin);
            newUser.gender = toupper(getchar());
        } while (newUser.gender != 'M' && newUser.gender != 'F');

        do {
            printf("Enter IC Number (DDMMYY########): ");
            rewind(stdin);
            scanf("%s", &newUser.ic_num);

            if (strlen(newUser.ic_num) != 12) {
                printf("\nIC number must be 12 digits long.\n\n");
            }
        } while (strlen(newUser.ic_num) != 12);

        do {
            printf("Enter Phone Number (01#########): ");
            rewind(stdin);
            scanf("%s", newUser.phoneNo);

            if ((strlen(newUser.phoneNo) < 10 || strlen(newUser.phoneNo) > 11)) {
                printf("\nPhone Number must be between 10 and 11 digits long.\n\n");
            } else if (strncmp(newUser.phoneNo, "01", 2)) {
                printf("\nPhone Number must start with \"01\".\n\n");
            }
        } while ((strlen(newUser.phoneNo) < 10 || strlen(newUser.phoneNo) > 11) || strncmp(newUser.phoneNo, "01", 2));

        fwrite(&newUser, sizeof(User), 1, file);
        fclose(file);

        printf("\nYou have been successfully registered!\n\n");
    }
}

void memberLogin() {
    User currentUser;
    char username[50], password[50];

    FILE* file = fopen("user.bin", "rb");
    if (file == NULL) {
        printf("\nNo registered user!\n");
        system("pause");
        return;
    }

    printf("\nEnter Username: ");
    rewind(stdin);
    scanf("%[^\n]", &username);

    printf("Password: ");
    rewind(stdin);
    scanf("%[^\n]", &password);

    int found = 0;
    while (fread(&currentUser, sizeof(User), 1, file)) {
        if (strcmp(currentUser.username, username) == 0 && strcmp(currentUser.password, password) == 0) {
            found = 1;
            break;
        }
    }

    if (found) {
        int choice;
        do {
            system("cls");
            printf("Welcome %s, what would you like to do?\n\n", currentUser.username);
            printf("1. View User Information\n2. Buy Tickets\n3. View My Tickets\n4. Logout\n\n");

            printf("Enter option: ");
            rewind(stdin);
            scanf("%d", &choice);

            switch (choice) {
                case 1:
                    memberInfo(currentUser);
                    system("pause");
                    break;
                case 2:
                    buyTicket(currentUser.ID);
                    system("pause");
                    break;
                case 3:
                    viewTickets(currentUser);
                    system("pause");
                    break;
                case 4:
                    break;
                default:
                    printf("\nInvalid option!\n");
                    system("pause");
                    break;
            }
        } while (choice != 4);
    } else {
        printf("\nInvalid Username or password.\n");
        system("pause");
    }
    fclose(file);
}

void memberInfo(User currentUser) {
    char choice;
    printf("\nUser Information\n");
    printf("==========================\n");
    printf("Name: %s\n", currentUser.username);
    printf("Gender: %c\n", currentUser.gender);
    printf("IC: %s\n", currentUser.ic_num);
    printf("Contact: %s\n", currentUser.phoneNo);
    printf("==========================\n\n");

    printf("Edit User Information (y/n)? ");
    rewind(stdin);
    choice = toupper(getchar());

    if (choice == 'Y') {
        FILE* file = openFile("user.bin", "rb+");

        User updatedUser = currentUser;

        printf("Enter new gender (M/F): ");
        rewind(stdin);
        scanf(" %c", &updatedUser.gender);

        printf("Enter new IC number (DDMMYY########): ");
        rewind(stdin);
        scanf("%s", updatedUser.ic_num);

        printf("Enter new phone number (01#########): ");
        rewind(stdin);
        scanf("%s", updatedUser.phoneNo);

        fseek(file, -sizeof(User), SEEK_CUR);

        fwrite(&updatedUser, sizeof(User), 1, file);
        printf("\nUser information updated successfully.\n");

        fclose(file);

        printf("\nUpdated User Information\n");
        printf("=====================================\n");
        printf("Name: %s\n", updatedUser.username);
        printf("Gender: %c\n", updatedUser.gender);
        printf("IC: %s\n", updatedUser.ic_num);
        printf("Contact: %s\n", updatedUser.phoneNo);
        printf("=====================================\n\n");

        system("pause");
    }
}

void buyTicket(char memberID) {
    struct Ticket ticket[SIZE];
    MemberTickets memberTicket;

    displayTickets();

    FILE* ptrView = openFile("tickets.txt", "r");

    int count = 0;
    while (fscanf(ptrView, "%[^|]|%[^|]|%[^|]|%[^|]|%lf\n", &ticket[count].destination, &ticket[count].trainID, &ticket[count].departureDate, &ticket[count].departureTime, &ticket[count].price) != EOF) {
        count++;
    }
    fclose(ptrView);

    if (count > 0) {
        int id;

        printf("\nEnter ID of ticket you'd like to buy: ");
        rewind(stdin);
        scanf("%d", &id);

        if (id < 1 || id > count) {
            printf("\nNo record found!\n");
        } else {
            do {
                printf("Enter quantity of tickets to buy (max 5): ");
                rewind(stdin);
                scanf("%d", &memberTicket.quantity);
            } while (memberTicket.quantity > 5);

            memberTicket.total = ticket[id - 1].price * memberTicket.quantity;

            char confirm;
            printf("\nGrand total: %.2lf\n", memberTicket.total);
            printf("Proceed (y/n)? ");
            rewind(stdin);
            confirm = tolower(getchar());

            if (confirm == 'y') {
                FILE* ptrWrite = openFile("memberTickets.txt", "a+");

                time_t now = time(NULL);
                struct tm* local = localtime(&now);

                int day, month, year;
                char date[11];

                day = local->tm_mday;
                month = local->tm_mon + 1;
                year = local->tm_year + 1900;

                sprintf(date, "%02d/%02d/%d", day, month, year);

                generateID('B', 5, memberTicket.bookingID);
                memberTicket.ticket = ticket[id - 1];

                strcpy(memberTicket.bookingDate, date);

                for (int i = 0; i < memberTicket.quantity; i++) {
                    char coach;
                    int seat;

                    do {
                        printf("\nEnter desired seat for ticket %d (coach: A-F, seat: 1-48) eg. A14: ", i + 1);
                        rewind(stdin);
                        scanf("%c%d", &coach, &seat);

                        coach = toupper(coach);
                    } while ((coach < 'A' || coach > 'F') || (seat < 1 || seat > 48));

                    sprintf(memberTicket.seats[i], "%c%02d", coach, seat);
                }

                strcpy(memberTicket.status, "Booked");

                fprintf(ptrWrite, "%s|%s|%s|%s|%s|%s|", memberID, memberTicket.bookingID, memberTicket.ticket.destination, memberTicket.ticket.trainID, memberTicket.ticket.departureDate, memberTicket.ticket.departureTime, memberTicket.bookingDate);

                for (int i = 0; i < memberTicket.quantity; i++) {
                    fprintf(ptrWrite, "%s", memberTicket.seats[i]);
                    if (i < memberTicket.quantity - 1) {
                        fprintf(ptrWrite, ",");
                    }
                }

                fprintf(ptrWrite, "|%d|%.2lf|%s\n", memberTicket.quantity, memberTicket.total, memberTicket.status);

                printf("Booking Successful!\n");
                fclose(ptrWrite);
            }
        }
    }
}

void viewTickets(User currentUser) {
    int choice;
    do {
        memberTickets(currentUser.ID, 1);

        printf("\nWhat would you like to do? \n\n");
        printf("1. Change Time\n2. Cancel Ticket\n3. Back\n\n");

        printf("Enter option: ");
        rewind(stdin);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                changeTicket(currentUser.ID);
                break;
            case 2:
                cancelTicket(currentUser.ID);
                break;
            case 3:
                break;
            default:
                printf("\nInvalid option!\n");
                system("pause");
                break;
        }
    } while (choice != 3);
}

void changeTicket(char memberID) {
    struct Ticket ticket[SIZE];
    MemberTickets memberTicket[SIZE];
    int found = 0, count = 0, id = 0;
    char bookingID[6], destination[50], departureDate[11], departureTime[11];

    FILE* ptrRead = openFile("memberTickets.txt", "r");

    while (fscanf(ptrRead, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%lf|%s\n", &memberTicket[count].memberID, &memberTicket[count].bookingID, &memberTicket[count].ticket.destination, &memberTicket[count].ticket.trainID, &memberTicket[count].ticket.departureDate, &memberTicket[count].ticket.departureTime, &memberTicket[count].bookingDate, &memberTicket[count].seats, &memberTicket[count].quantity, &memberTicket[count].total, &memberTicket[count].status) != EOF) {
        count++;
    }
    fclose(ptrRead);

    memberTickets(memberID, 0);

    printf("\nEnter Booking ID of ticket to edit: ");
    rewind(stdin);
    toupper(gets(bookingID));

    for (int i = 0; i < count; i++) {
        if (strcmp(bookingID, memberTicket[i].bookingID) == 0) {
            strcpy(destination, memberTicket[i].ticket.destination);
            strcpy(departureDate, memberTicket[i].ticket.departureDate);
            strcpy(departureTime, memberTicket[i].ticket.departureTime);
            found = 1;

            printf("\nAvaiable Tickets:\n");
            ticketsHeader();

            ptrRead = openFile("tickets.txt", "r");

            while (fscanf(ptrRead, "%[^|]|%[^|]|%[^|]|%[^|]|%lf\n", &ticket[id].destination, &ticket[id].trainID, &ticket[id].departureDate, &ticket[id].departureTime, &ticket[id].price) != EOF) {
                if (strcmp(destination, ticket[id].destination) == 0 && (strcmp(departureDate, ticket[id].departureDate) != 0 || strcmp(departureTime, ticket[id].departureTime) != 0)) {
                    printf("%-3d %-15s %-10s %-15s %-15s %.2lf\n", id + 1, ticket[id].destination, ticket[id].trainID, ticket[id].departureDate, ticket[id].departureTime, ticket[id].price);
                }
                id++;
            }
            fclose(ptrRead);

            int choice;
            printf("\nEnter No. to choose: ");
            rewind(stdin);
            scanf("%d", &choice);

            printf("\nUpdated Booking:\n");

            printf("\n%-13s %-15s %-10s %-15s %-15s %s\n", "Booking ID", "Destination", "Train ID", "Seat(s)", "Departure Date", "Departure Time");
            printf("========================================================================================\n");
            printf("%-13s %-15s %-10s %-15s %-15s %s\n", memberTicket[i].bookingID, memberTicket[i].ticket.destination, ticket[choice - 1].trainID, memberTicket[i].seats, ticket[choice - 1].departureDate, ticket[choice - 1].departureTime, memberTicket[i].bookingDate, memberTicket[i].total, memberTicket[i].status);

            printf("\nConfirm edit (y/n)? ");
            rewind(stdin);
            char confirm = tolower(getchar());
            if (confirm == 'y') {
                strcpy(memberTicket[i].ticket.trainID, ticket[choice - 1].trainID);
                strcpy(memberTicket[i].ticket.departureDate, ticket[choice - 1].departureDate);
                strcpy(memberTicket[i].ticket.departureTime, ticket[choice - 1].departureTime);
            }
        }
    }

    if (!found) {
        printf("No records found!\n");
    } else {
        FILE* ptrWrite = openFile("memberTickets.txt", "w");

        for (int i = 0; i < count; i++) {
            fprintf(ptrWrite, "%s|%s|%s|%s|%s|%s|%s|%s|%d|%.2lf|%s\n", memberTicket[i].memberID, memberTicket[i].bookingID, memberTicket[i].ticket.destination, memberTicket[i].ticket.trainID, memberTicket[i].ticket.departureDate, memberTicket[i].ticket.departureTime, memberTicket[i].bookingDate, memberTicket[i].seats, memberTicket[i].quantity, memberTicket[i].total, memberTicket[i].status);
        }

        fclose(ptrWrite);
        printf("Ticket update successful.\n");
    }
}

void cancelTicket(char memberID) {
    MemberTickets memberTicket[SIZE];
    int count = 0, found = 0;
    char bookingID[6];

    FILE* ptrRead = openFile("memberTickets.txt", "r");

    while (fscanf(ptrRead, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%lf|%s\n", &memberTicket[count].memberID, &memberTicket[count].bookingID, &memberTicket[count].ticket.destination, &memberTicket[count].ticket.trainID, &memberTicket[count].ticket.departureDate, &memberTicket[count].ticket.departureTime, &memberTicket[count].bookingDate, &memberTicket[count].seats, &memberTicket[count].quantity, &memberTicket[count].total, &memberTicket[count].status) != EOF) {
        count++;
    }
    fclose(ptrRead);

    memberTickets(memberID, 0);

    printf("\nEnter Booking ID of ticket to cancel: ");
    rewind(stdin);
    toupper(gets(bookingID));

    for (int i = 0; i < count; i++) {
        if (strcmp(memberTicket[i].bookingID, bookingID) == 0) {
            if (strcmp(memberTicket[i].status, "Cancelled") != 0) {
                memberHeader();

                printf("%-15s %-15s %-10s %-15s %-15s %-15s %-15s %-10.2lf %s\n", memberTicket[i].bookingID, memberTicket[i].ticket.destination, memberTicket[i].ticket.trainID, memberTicket[i].seats, memberTicket[i].ticket.departureDate, memberTicket[i].ticket.departureTime, memberTicket[i].bookingDate, memberTicket[i].total, memberTicket[i].status);

                printf("\nConfirm cancellation (y/n)? ");
                rewind(stdin);
                char confirm = tolower(getchar());
                if (confirm == 'y') {
                    strcpy(memberTicket[i].status, "Cancelled");
                    found = 1;
                }
            } else {
                printf("Ticket has already been cancelled!\n");
            }
        }
    }

    if (!found) {
        printf("No records found!\n");
    } else {
        FILE* ptrWrite = openFile("memberTickets.txt", "w");

        for (int i = 0; i < count; i++) {
            fprintf(ptrWrite, "%s|%s|%s|%s|%s|%s|%s|%s|%d|%.2lf|%s\n", memberTicket[i].memberID, memberTicket[i].bookingID, memberTicket[i].ticket.destination, memberTicket[i].ticket.trainID, memberTicket[i].ticket.departureDate, memberTicket[i].ticket.departureTime, memberTicket[i].bookingDate, memberTicket[i].seats, memberTicket[i].quantity, memberTicket[i].total, memberTicket[i].status);
        }

        fclose(ptrWrite);
        printf("Ticket cancellation successful.\n");
    }
}

// Staff Functions
void memberMenu() {
    int choice;
    do {
        system("cls");
        printf("GS Train System Member Management\n\n");
        printf("1. View Members\n2. Delete Members\n3. Back\n\n");

        printf("Enter option: ");
        rewind(stdin);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                viewMembers();
                system("pause");
                break;
            case 2:
                deleteMember();
                break;
            case 3:
                break;
            default:
                printf("\nInvalid option!\n");
                break;
        }
    } while (choice != 3);
}

void viewMembers() {
    User users;
    FILE* file = openFile("user.bin", "rb");

    memberHeader();

    while (fread(&users, sizeof(User), 1, file)) {
        printf("%-10s %-20s %-7c %-14s %s\n", users.ID, users.username, users.gender, users.ic_num, users.phoneNo);
    }

    fclose(file);
}

void deleteMember() {
    char prompt;
    do {
        User member[50];

        FILE* ptr = openFile("user.bin", "rb");

        int count = 0;
        while (fread(&member[count], sizeof(User), 1, ptr)) {
            count++;
        }
        fclose(ptr);

        viewMembers();

        FILE* ptrDelete = openFile("user.bin", "wb");
        char id[7];

        printf("\nEnter ID to delete: ");
        rewind(stdin);
        scanf("%s", &id);

        for (int i = 0; i < count; i++) {
            if (strcmp(id, member[i].ID) == 0) {
                memberHeader();
                printf("%-10s %-20s %-7c %-14s %s\n", member[i].ID, member[i].username, member[i].gender, member[i].ic_num, member[i].phoneNo);

                printf("\nConfirm delete (y/n)? ");
                rewind(stdin);
                char confirm = tolower(getchar());
                if (confirm == 'y') {
                } else {
                    printf("\nUpdate cancelled!\n");
                    fwrite(&member[i], sizeof(User), 1, ptrDelete);
                }
            } else {
                fwrite(&member[i], sizeof(User), 1, ptrDelete);
            }
        }
        fclose(ptrDelete);

        printf("\nContinue deleting (y/n)? ");
        rewind(stdin);
        prompt = tolower(getchar());
    } while (prompt == 'y');
}

void staffMenu() {
    int choice;
    do {
        system("cls");
        printf("GS Train System Staff Management\n\n");
        printf("1. View Staff\n2. Add Staff\n3. Edit Staff\n4. Delete Staff\n5. Back\n\n");

        printf("Enter option: ");
        rewind(stdin);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayStaff();
                system("pause");
                break;
            case 2:
                newStaff();
                break;
            case 3:
                editStaff();
                break;
            case 4:
                deleteStaff();
                break;
            case 5:
                break;
            default:
                printf("\nInvalid option!\n");
                break;
        }
    } while (choice != 5);
}

void displayStaff() {
    Staff info;
    FILE* fptr = openFile("staff.bin", "rb");

    printf("\n%-15s %-15s %-5s %-8s %s\n", "EmployeeID", "Employee Name", "Age", "Gender", "Position");
    printf("====================================================================================\n");

    while (fread(&info, sizeof(Staff), 1, fptr)) {
        printf("%-15s %-15s %-5d %-8c %s\n", info.employeeID, info.employeeName, info.age, info.gender, info.position);
    }
    fclose(fptr);
}

void newStaff() {
    Staff info;
    FILE* fptr = openFile("staff.bin", "ab");

    printf("\nEnter new employee ID:");
    rewind(stdin);
    scanf("%[^\n]", &info.employeeID);

    printf("Enter new employee name:");
    rewind(stdin);
    scanf("%[^\n]", &info.employeeName);

    printf("Enter new employee gender:");
    rewind(stdin);
    scanf(" %c", &info.gender);

    printf("Enter new employee age:");
    rewind(stdin);
    scanf("%d", &info.age);

    printf("Enter new password exp (john123):");
    rewind(stdin);
    scanf("%[^\n]", &info.password);

    printf("Enter your new position:");
    rewind(stdin);
    scanf("%[^\n]", &info.position);

    fwrite(&info, sizeof(Staff), 1, fptr);
    if (ferror(fptr)) {
        printf("Error writing to file.\n");
    } else {
        printf("\n");
        printf("Employee added successfully!\n");
        printf("\n");
    }
    fclose(fptr);
}

void editStaff() {
    Staff staff[SIZE];
    int count = 0, i, found = 0;
    char enteredID[10];

    FILE* fptr = openFile("staff.bin", "rb+");

    while (fread(&staff[count], sizeof(Staff), 1, fptr)) {
        count++;
    }

    printf("\nEnter the Employee ID to modify: ");
    rewind(stdin);
    scanf("%s", enteredID);

    for (i = 0; i < count; i++) {
        if (strcmp(staff[i].employeeID, enteredID) == 0) {
            found = 1;
            break;
        }
    }

    if (found) {
        printf("Enter new details to modify (leave unchanged for no modification):\n");
        printf("Enter employee name (current: %s): ", staff[i].employeeName);
        rewind(stdin);
        scanf("%[^\n]", &staff[i].employeeName);

        printf("Enter employee gender (current: %c): ", staff[i].gender);
        rewind(stdin);
        scanf(" %c", &staff[i].gender);

        printf("Enter employee age (current: %d): ", staff[i].age);
        scanf("%d", &staff[i].age);

        printf("Enter your new password (leave blank for no change): ");
        rewind(stdin);
        scanf("%[^\n]", &staff[i].password);

        printf("Enter your new position (leave blank for no change): ");
        rewind(stdin);
        scanf("%[^\n]", &staff[i].position);

        fseek(fptr, i * sizeof(Staff), SEEK_SET);

        fwrite(&staff[i], sizeof(Staff), 1, fptr);

        printf("\nEmployee details modified successfully.\n");
    } else {
        printf("\nEmployee not found.\n");
    }
    fclose(fptr);
}

void deleteStaff() {
    Staff staff[SIZE];
    int count = 0, i, found = 0;
    char enteredID[10];

    FILE* fptr = openFile("staff.bin", "rb");

    while (fread(&staff[count], sizeof(Staff), 1, fptr)) {
        count++;
    }
    fclose(fptr);

    printf("\nEnter the Employee ID to delete: ");
    rewind(stdin);
    scanf("%s", enteredID);

    for (i = 0; i < count; i++) {
        if (strcmp(staff[i].employeeID, enteredID) == 0) {
            found = 1;
            break;
        }
    }

    if (found) {
        for (i = found; i < count - 1; i++) {
            staff[i] = staff[i + 1];
        }
        count--;

        fptr = openFile("staff.bin", "wb");

        fwrite(staff, sizeof(Staff), count, fptr);
        fclose(fptr);

        printf("\nEmployee deleted successfully.\n");
    } else {
        printf("\nEmployee not found.\n");
    }
}

void ticketMenu() {
    int choice;
    do {
        system("cls");
        printf("GS Train System Ticket Management\n\n");
        printf("1. View Tickets\n2. Add Ticket\n3. Edit Ticket\n4. Delete Ticket\n5. Back\n\n");

        printf("Enter option: ");
        rewind(stdin);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                searchTicket();
                system("pause");
                break;
            case 2:
                addTicket();
                break;
            case 3:
                editTicket();
                break;
            case 4:
                deleteTicket();
                break;
            case 5:
                break;
            default:
                printf("\nInvalid option!\n");
                break;
        }
    } while (choice != 5);
}

void searchTicket() {
    struct Ticket ticket;
    char keyword[50], destination[50];
    int found = 0, count = 1;

    displayTickets();

    printf("\nEnter keyword to search: ");
    rewind(stdin);
    strlwr(gets(keyword));

    FILE* ptrSearch = openFile("tickets.txt", "r");

    ticketsHeader();
    while (fscanf(ptrSearch, "%[^|]|%[^|]|%[^|]|%[^|]|%lf\n", &ticket.destination, &ticket.trainID, &ticket.departureDate, &ticket.departureTime, &ticket.price) != EOF) {
        strcpy(destination, ticket.destination);
        if (strcmp(strlwr(destination), keyword) == 0) {
            printf("%-3d %-15s %-10s %-15s %-15s %.2lf\n", count++, ticket.destination, ticket.trainID, ticket.departureDate, ticket.departureTime, ticket.price);
            found = 1;
        }
    }

    if (!found) {
        printf("No results found!\n");
    } else {
        printf("\n%d result(s) found.\n", count);
    }
    fclose(ptrSearch);
}

void addTicket() {
    struct Ticket ticket;
    FILE* ptrAdd = openFile("tickets.txt", "a");

    char prompt;

    do {
        printf("\nEnter destination (eg. Kuala Lumpur): ");
        rewind(stdin);
        gets(ticket.destination);

        printf("Enter train ID (eg. T1001): ");
        rewind(stdin);
        gets(ticket.trainID);

        printf("Enter departure date (eg. 21/01/2024): ");
        rewind(stdin);
        gets(ticket.departureDate);

        printf("Enter departure time (eg. 07:00): ");
        rewind(stdin);
        gets(ticket.departureTime);

        printf("Enter price (eg. 100.00): ");
        rewind(stdin);
        scanf("%lf", &ticket.price);

        printf("\nConfirm ticket (y/n)? ");
        rewind(stdin);
        char confirm = tolower(getchar());

        if (confirm == 'y') {
            fprintf(ptrAdd, "%s|%s|%s|%s|%.2lf\n", ticket.destination, ticket.trainID, ticket.departureDate, ticket.departureTime, ticket.price);
        } else {
            printf("No changes made!\n");
        }

        printf("\nAdd more ticket (y/n)? ");
        rewind(stdin);
        prompt = tolower(getchar());

    } while (prompt != 'n');
    fclose(ptrAdd);
}

void editTicket() {
    struct Ticket ticket[SIZE];
    FILE* ptrRead = openFile("tickets.txt", "r");

    int count = 0;
    while (fscanf(ptrRead, "%[^|]|%[^|]|%[^|]|%[^|]|%lf\n", &ticket[count].destination, &ticket[count].trainID, &ticket[count].departureDate, &ticket[count].departureTime, &ticket[count].price) != EOF) {
        count++;
    }
    fclose(ptrRead);

    char prompt;
    do {
        char destination[50], trainID[6], departureDate[11], departureTime[6];
        double price;
        int id;

        displayTickets();

        printf("\nEnter No. to edit (0 to exit): ");
        rewind(stdin);
        scanf("%d", &id);

        if (id != 0) {
            if (id < 0 || id > count) {
                printf("\nNo record found!\n");
            } else {
                printf("\nEnter destination (eg. Kuala Lumpur): ");
                rewind(stdin);
                gets(destination);

                printf("Enter train ID (eg. T1001): ");
                rewind(stdin);
                gets(trainID);

                printf("Enter departure date (eg. 21/01/2024): ");
                rewind(stdin);
                gets(departureDate);

                printf("Enter departure time (eg. 07:00): ");
                rewind(stdin);
                gets(departureTime);

                printf("Enter price (eg. 100.00): ");
                rewind(stdin);
                scanf("%lf", &price);

                printf("Confirm update (y/n)? ");
                rewind(stdin);
                char confirm = tolower(getchar());
                if (confirm == 'y') {
                    strcpy(ticket[id - 1].destination, destination);
                    strcpy(ticket[id - 1].trainID, trainID);
                    strcpy(ticket[id - 1].departureDate, departureDate);
                    strcpy(ticket[id - 1].departureTime, departureTime);
                    ticket[id - 1].price = price;

                    printf("\nUpdate successful!\n");
                } else {
                    printf("\nUpdate cancelled!\n");
                }
            }
        }

        printf("\nContinue editing (y/n)? ");
        rewind(stdin);
        prompt = tolower(getchar());

    } while (prompt != 'n');

    FILE* ptrWrite = openFile("tickets.txt", "w");

    for (int i = 0; i < count; i++) {
        fprintf(ptrWrite, "%s|%s|%s|%s|%.2lf\n", ticket[i].destination, ticket[i].trainID, ticket[i].departureDate, ticket[i].departureTime, ticket[i].price);
    }

    fclose(ptrWrite);
}

void deleteTicket() {
    char prompt;
    int id;
    do {
        struct Ticket ticket[SIZE];
        FILE* ptrRead = openFile("tickets.txt", "r");

        int count = 0;
        while (fscanf(ptrRead, "%[^|]|%[^|]|%[^|]|%lf\n", &ticket[count].destination, &ticket[count].trainID, &ticket[count].departureDate, &ticket[count].price) != EOF) {
            count++;
        }
        fclose(ptrRead);

        displayTickets();

        printf("\nEnter No. to delete (0 to exit): ");
        rewind(stdin);
        scanf("%d", &id);

        if (id != 0) {
            if (id < 0 || id > count) {
                printf("\nNo record found!\n");
            } else {
                FILE* ptrDelete = openFile("tickets.txt", "w");

                for (int i = 0; i < count; i++) {
                    if (id - 1 == i) {
                        ticketsHeader();
                        printf("%-3d %-15s %-10s %-15s %-15s %.2lf\n", id, ticket[id - 1].destination, ticket[id - 1].trainID, ticket[id - 1].departureDate, ticket[id - 1].departureTime, ticket[id - 1].price);

                        printf("\nConfirm delete (y/n)? ");
                        rewind(stdin);
                        char confirm = tolower(getchar());
                        if (confirm == 'y') {
                            printf("\nRecord deleted successfully\n");
                        } else {
                            printf("\nUpdate cancelled!\n");
                            fprintf(ptrDelete, "%s|%s|%s|%s|%.2lf\n", ticket[i].destination, ticket[i].trainID, ticket[i].departureDate, ticket[i].departureTime, ticket[i].price);
                        }
                    } else {
                        fprintf(ptrDelete, "%s|%s|%s|%s|%.2lf\n", ticket[i].destination, ticket[i].trainID, ticket[i].departureDate, ticket[i].departureTime, ticket[i].price);
                    }
                }
                fclose(ptrDelete);
            }
        }

        printf("\nContinue deleting (y/n)? ");
        rewind(stdin);
        prompt = tolower(getchar());
    } while (prompt == 'y' || id == 0);
}

// Misc Functions
FILE* openFile(char* filename, char* mode) {
    FILE* ptr = fopen(filename, mode);
    if (ptr == NULL) {
        printf("Unable to open %s in %s mode, please try again.", filename, mode);
        return;
    }

    return ptr;
}

void generateID(char head, int length, char* id) {
    id[0] = head;
    srand(time(NULL));
    for (int i = 1; i < length; i++) {
        id[i] = '0' + rand() % 10;
    }
    id[length] = '\0';
}

void memberHeader() {
    printf("\n%-10s %-20s %-7s %-14s %s\n", "ID", "Username", "Gender", "IC Number", "Phone Number");
    printf("=========================================================================\n");
}

void ticketsHeader() {
    printf("\n%-3s %-15s %-10s %-15s %-15s %s\n", "ID", "Destination", "Train ID", "Departure Date", "Departure Time", "Price");
    printf("=======================================================================\n");
}

void displayTickets() {
    struct Ticket ticket;
    FILE* ptrView = openFile("tickets.txt", "r");

    ticketsHeader();

    int count = 0;
    while (fscanf(ptrView, "%[^|]|%[^|]|%[^|]|%[^|]|%lf\n", &ticket.destination, &ticket.trainID, &ticket.departureDate, &ticket.departureTime, &ticket.price) != EOF) {
        count++;
        printf("%-3d %-15s %-10s %-15s %-15s %.2lf\n", count, ticket.destination, ticket.trainID, ticket.departureDate, ticket.departureTime, ticket.price);
    }

    if (count == 0) {
        printf("No records found.\n\n");
    }
    fclose(ptrView);
}

void memberTicketHeader() {
    printf("\n%-15s %-15s %-10s %-15s %-15s %-15s %-15s %-10s %s\n", "Booking ID", "Destination", "Train ID", "Seat(s)", "Departure Date", "Departure Time", "Booking Date", "Total", "Status");
    printf("==================================================================================================================================\n");
}

void memberTickets(char memberID, int showCancelled) {
    MemberTickets memberTicket;
    int found = 0;

    memberHeader();

    FILE* ptrRead = openFile("memberTickets.txt", "r");

    while (fscanf(ptrRead, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%lf|%s\n", &memberTicket.memberID, &memberTicket.bookingID, &memberTicket.ticket.destination, &memberTicket.ticket.trainID, &memberTicket.ticket.departureDate, &memberTicket.ticket.departureTime, &memberTicket.bookingDate, &memberTicket.seats, &memberTicket.quantity, &memberTicket.total, &memberTicket.status) != EOF) {
        if (strcmp(memberTicket.memberID, memberID) == 0 &&
            (showCancelled || strcmp(memberTicket.status, "Cancelled") != 0)) {
            printf("%-15s %-15s %-10s %-15s %-15s %-15s %-15s %-10.2lf %s\n", memberTicket.bookingID, memberTicket.ticket.destination, memberTicket.ticket.trainID, memberTicket.seats, memberTicket.ticket.departureDate, memberTicket.ticket.departureTime, memberTicket.bookingDate, memberTicket.total, memberTicket.status);
            found = 1;
        }
    }
    fclose(ptrRead);

    if (!found) {
        printf("No records found.\n");
    }
}
