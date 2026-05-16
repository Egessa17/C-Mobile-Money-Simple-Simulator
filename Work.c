#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for storing user details
struct User {
    char name[50];
    char phone[10];
    char pin[4];
    float balance;
};

// Global variable to temporarily hold user data
struct User user;

// Function declarations
void registerUser();
void depositMoney();
void withdrawMoney();
void checkBalance();
void searchUser();
void adminReport();

int main() {

    int choice;

    // Main menu loop
    do {

        printf("\n====================================\n");
        printf(" MOBILE MONEY MANAGEMENT SYSTEM\n");
        printf("====================================\n");

        printf("1. Register User\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Check Balance\n");
        printf("5. Search User\n");
        printf("6. Admin Report\n");
        printf("7. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        // Switch statement for menu selection
        switch(choice) {

            case 1:
                registerUser();
                break;

            case 2:
                depositMoney();
                break;

            case 3:
                withdrawMoney();
                break;

            case 4:
                checkBalance();
                break;

            case 5:
                searchUser();
                break;

            case 6:
                adminReport();
                break;

            case 7:
                printf("\nThank you for using the system.\n");
                break;

            default:
                printf("\nInvalid choice. Try again.\n");
        }

    } while(choice != 7);

    // Required output at the end
    printf("\n====================================\n");
    printf("Developed By: Egessa Samuel Antonio\n");
    printf("Registration Number: 2024/BSE/058/PS\n");
    printf("====================================\n");

    return 0;
}

// Function for registering a new user
void registerUser() {

    FILE *file;

    // Open file in append mode
    file = fopen("users.txt", "a");

    if(file == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    printf("\n===== USER REGISTRATION =====\n");

    printf("Enter full name: ");
    scanf(" %[^\n]", user.name);

    printf("Enter phone number: ");
    scanf("%s", user.phone);

    printf("Create PIN: ");
    scanf("%s", user.pin);

    printf("Enter starting balance: ");
    scanf("%f", &user.balance);

    // Save user details into file
    fprintf(file, "%s %s %s %.2f\n",
            user.name,
            user.phone,
            user.pin,
            user.balance);

    fclose(file);

    printf("\nUser registered successfully.\n");
}

// Function for depositing money
void depositMoney() {

    float amount;

    printf("\n===== DEPOSIT MONEY =====\n");

    printf("Enter amount to deposit: ");
    scanf("%f", &amount);

    // Add deposited amount to balance
    user.balance = user.balance + amount;

    printf("Deposit successful.\n");
    printf("New Balance: %.2f\n", user.balance);
}

// Function for withdrawing money
void withdrawMoney() {

    float amount;
    float charge = 500;

    printf("\n===== WITHDRAW MONEY =====\n");

    printf("Enter amount to withdraw: ");
    scanf("%f", &amount);

    // Check if balance is enough
    if(user.balance >= amount + charge) {

        user.balance = user.balance - (amount + charge);

        printf("Withdrawal successful.\n");
        printf("Transaction charge: %.2f\n", charge);
        printf("Remaining Balance: %.2f\n", user.balance);
    }

    else {
        printf("Insufficient balance.\n");
    }
}

// Function for checking balance
void checkBalance() {

    printf("\n===== ACCOUNT BALANCE =====\n");
    printf("Current Balance: %.2f\n", user.balance);
}

// Function for searching a user
void searchUser() {

    FILE *file;
    char searchPhone[20];
    int found = 0;

    struct User temp;

    file = fopen("users.txt", "r");

    if(file == NULL) {
        printf("File not found.\n");
        return;
    }

    printf("\n===== SEARCH USER =====\n");

    printf("Enter phone number to search: ");
    scanf("%s", searchPhone);

    // Read users from file
    while(fscanf(file, "%s %s %s %f",
                 temp.name,
                 temp.phone,
                 temp.pin,
                 &temp.balance) != EOF) {

        // Compare phone numbers
        if(strcmp(temp.phone, searchPhone) == 0) {

            printf("\nUser Found\n");
            printf("Name: %s\n", temp.name);
            printf("Phone: %s\n", temp.phone);
            printf("Balance: %.2f\n", temp.balance);

            found = 1;
            break;
        }
    }

    if(found == 0) {
        printf("User not found.\n");
    }

    fclose(file);
}

// Function for admin report
void adminReport() {

    FILE *file;
    int totalUsers = 0;
    float totalMoney = 0;

    struct User temp;

    file = fopen("users.txt", "r");

    if(file == NULL) {
        printf("No records found.\n");
        return;
    }

    // Read all users from file
    while(fscanf(file, "%s %s %s %f",
                 temp.name,
                 temp.phone,
                 temp.pin,
                 &temp.balance) != EOF) {

        totalUsers++;
        totalMoney = totalMoney + temp.balance;
    }

    fclose(file);

    printf("\n===== ADMIN REPORT =====\n");
    printf("Total Users: %d\n", totalUsers);
    printf("Total Money in System: %.2f\n", totalMoney);
}
