#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Structure Definition
struct Account {
    int accNo;
    char name[50];
    float balance;
};
//Function Prototypes
void createAccount();
void deposit();
void withdraw();
void checkBalance();
//Main Function
int main() {
    int choice;
    
    while(1) {
    	printf("\n-----------------------------------------------\n");
        printf("    Bank Account Management System    ");
        printf("\n-----------------------------------------------\n");        
        printf("\n1. Create New Account\n"); // Added for utility
        printf("\n2. Deposit Money\n");
        printf("\n3. Withdraw Money\n");
        printf("\n4. Check Balance\n");
        printf("\n5. Exit\n");
        printf("\n-----------------------------------------------\n\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: createAccount(); break;
            case 2: deposit(); break;
            case 3: withdraw(); break;
            case 4: checkBalance(); break;
            case 5: 
                printf("\n\nExiting... Thank you for banking with us.\n");
                exit(0);
            default: printf("\nInvalid choice! Please try again.\n");
        }
    }
    return 0;
}

//Function Definitions
// 1. Create a new account and save to file
void createAccount() {
    struct Account acc;
    FILE *fp = fopen("bank_data.dat", "ab"); // Append binary mode
    
    if (fp == NULL) {
        printf("\nError opening file!\n");
        return;
    }
    printf("\n   Create Account   \n");
    printf("\nEnter Account Number: ");
    scanf("%d", &acc.accNo);
    // Clear input buffer to handle string input correctly
    while(getchar() != '\n'); 

    printf("\nEnter Name: ");
    fgets(acc.name, sizeof(acc.name), stdin);
    acc.name[strcspn(acc.name, "\n")] = 0; // Remove newline char

    acc.balance = 0.0; // Initial balance is 0
    
    fwrite(&acc, sizeof(struct Account), 1, fp);
    printf("\nAccount created successfully!\n");
    
    fclose(fp);
}
// 2. Deposit money into a specific account
void deposit() {
    struct Account acc;
    FILE *fp, *tempFp;
    int targetAcc, found = 0;
    float amount;

    fp = fopen("bank_data.dat", "rb");
    tempFp = fopen("temp.dat", "wb");

    if (fp == NULL || tempFp == NULL) {
        printf("\nError: File not found or could not be opened.\n");
        return;
    }

    printf("\n-- Deposit Money --\n");
    printf("\nEnter Account Number: ");
    scanf("%d", &targetAcc);
    printf("\nEnter Amount to Deposit: ");
    scanf("%f", &amount);

    while (fread(&acc, sizeof(struct Account), 1, fp)) {
        if (acc.accNo == targetAcc) {
            acc.balance += amount;
            printf("\nDeposited %.2f successfully. New Balance: %.2f\n", amount, acc.balance);
            found = 1;
        }
        fwrite(&acc, sizeof(struct Account), 1, tempFp);
    }

    fclose(fp);
    fclose(tempFp);

    if (found) {
        remove("bank_data.dat");
        rename("temp.dat", "bank_data.dat");
    } else {
        remove("temp.dat");
        printf("\nAccount not found!\n");
    }
}
// 3. Withdraw money from a specific account
void withdraw() {
    struct Account acc;
    FILE *fp, *tempFp;
    int targetAcc, found = 0;
    float amount;

    fp = fopen("bank_data.dat", "rb");
    tempFp = fopen("temp.dat", "wb");

    if (fp == NULL || tempFp == NULL) {
        printf("\nError: File not found.\n");
        return;
    }

    printf("\n-- Withdraw Money --\n");
    printf("\nEnter Account Number: ");
    scanf("%d", &targetAcc);
    printf("\nEnter Amount to Withdraw: ");
    scanf("%f", &amount);

    while (fread(&acc, sizeof(struct Account), 1, fp)) {
        if (acc.accNo == targetAcc) {
            found = 1;
            if (acc.balance >= amount) {
                acc.balance -= amount;
                printf("\nWithdrawn %.2f successfully. New Balance: %.2f\n", amount, acc.balance);
            } else {
                printf("\nInsufficient Balance! Current Balance: %.2f\n", acc.balance);
            }
        }
        fwrite(&acc, sizeof(struct Account), 1, tempFp);
    }

    fclose(fp);
    fclose(tempFp);

    if (found) {
        remove("bank_data.dat");
        rename("temp.dat", "bank_data.dat");
    } else {
        remove("temp.dat");
        printf("\nAccount not found!\n");
    }
}
// 4. Check the balance of a specific account
void checkBalance() {
    struct Account acc;
    FILE *fp = fopen("bank_data.dat", "rb");
    int targetAcc, found = 0;

    if (fp == NULL) {
        printf("\nNo accounts found. Create one first!\n");
        return;
    }

    printf("\n   Check Balance   \n");
    printf("\nEnter Account Number: ");
    scanf("%d", &targetAcc);

    while (fread(&acc, sizeof(struct Account), 1, fp)) {
        if (acc.accNo == targetAcc) {
            printf("\nAccount No: %d\n", acc.accNo);
            printf("\nName: %s\n", acc.name);
            printf("\nCurrent Balance: $%.2f\n", acc.balance);
            found = 1;
            break; // Stop searching once found
        }
    }

    if (!found) {
        printf("\nAccount not found!\n");
    }

    fclose(fp);
}
