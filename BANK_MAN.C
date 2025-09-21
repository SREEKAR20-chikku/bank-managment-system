#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

struct Account {
    int acc_no;
    char name[50];
    float balance;
    struct Account *left, *right;
};

struct Account *root = NULL;

struct Account* createAccount(int acc_no, char name[], float balance) {
    struct Account *newAcc;
    newAcc = (struct Account*) malloc(sizeof(struct Account));
    newAcc->acc_no = acc_no;
    strcpy(newAcc->name, name);
    newAcc->balance = balance;
    newAcc->left = newAcc->right = NULL;
    return newAcc;
}

struct Account* insert(struct Account *node, int acc_no, char name[], float balance) {
    if (node == NULL) {
        return createAccount(acc_no, name, balance);
    }
    if (acc_no < node->acc_no) {
        node->left = insert(node->left, acc_no, name, balance);
    } else if (acc_no > node->acc_no) {
        node->right = insert(node->right, acc_no, name, balance);
    } else {
        printf("\nAccount number already exists!\n");
    }
    return node;
}

void display(struct Account *node) {
    if (node != NULL) {
        display(node->left);
        printf("\nAccount No: %d", node->acc_no);
        printf("\nName: %s", node->name);
        printf("\nBalance: %.2f\n", node->balance);
        display(node->right);
    }
}

struct Account* search(struct Account *node, int acc_no) {
    if (node == NULL || node->acc_no == acc_no) {
        return node;
    }
    if (acc_no < node->acc_no) {
        return search(node->left, acc_no);
    }
    return search(node->right, acc_no);
}

void depositAmount() {
    int acc_no;
    float amount;
    struct Account *acc;

    printf("\nEnter Account Number (1000-9999): ");
    scanf("%d", &acc_no);
    while (acc_no < 1000 || acc_no > 9999) {
        printf("Invalid! Please enter a 4-digit account number: ");
        scanf("%d", &acc_no);
    }

    acc = search(root, acc_no);
    if (acc != NULL) {
        printf("Enter amount to deposit: ");
        scanf("%f", &amount);
        if (amount > 0) {
            acc->balance += amount;
            printf("Amount deposited successfully! New Balance: %.2f\n", acc->balance);
        } else {
            printf("Invalid deposit amount!\n");
        }
    } else {
        printf("Account not found!\n");
    }
}

void withdrawAmount() {
    int acc_no;
    float amount;
    struct Account *acc;

    printf("\nEnter Account Number (1000-9999): ");
    scanf("%d", &acc_no);
    while (acc_no < 1000 || acc_no > 9999) {
        printf("Invalid! Please enter a 4-digit account number: ");
        scanf("%d", &acc_no);
    }

    acc = search(root, acc_no);
    if (acc != NULL) {
        printf("Enter amount to withdraw: ");
        scanf("%f", &amount);
        if (amount > 0 && amount <= acc->balance) {
            acc->balance -= amount;
            printf("Amount withdrawn successfully! New Balance: %.2f\n", acc->balance);
        } else {
            printf("Invalid withdrawal amount or insufficient balance!\n");
        }
    } else {
        printf("Account not found!\n");
    }
}

void addAccount() {
    int acc_no;
    char name[50];
    float balance;

    printf("\nEnter Account Number (1000-9999): ");
    scanf("%d", &acc_no);
    while (acc_no < 1000 || acc_no > 9999) {
        printf("Invalid! Please enter a 4-digit account number: ");
        scanf("%d", &acc_no);
    }

    printf("Enter Name: ");
    fflush(stdin);
    gets(name);

    printf("Enter Initial Balance: ");
    scanf("%f", &balance);

    root = insert(root, acc_no, name, balance);
}

void searchAccount() {
    int acc_no;
    struct Account *acc;

    printf("\nEnter Account Number (1000-9999): ");
    scanf("%d", &acc_no);
    while (acc_no < 1000 || acc_no > 9999) {
        printf("Invalid! Please enter a 4-digit account number: ");
        scanf("%d", &acc_no);
    }

    acc = search(root, acc_no);
    if (acc != NULL) {
        printf("\nAccount No: %d", acc->acc_no);
        printf("\nName: %s", acc->name);
        printf("\nBalance: %.2f\n", acc->balance);
    } else {
        printf("Account not found!\n");
    }
}

void main() {
    int choice;
    clrscr();

    while (1) {
        printf("\n===== BANK MANAGEMENT SYSTEM =====");
        printf("\n1. Add Account");
        printf("\n2. Display All Accounts");
        printf("\n3. Search Account");
        printf("\n4. Deposit");
        printf("\n5. Withdraw");
        printf("\n6. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addAccount(); break;
            case 2: display(root); break;
            case 3: searchAccount(); break;
            case 4: depositAmount(); break;
            case 5: withdrawAmount(); break;
            case 6: exit(0);
            default: printf("Invalid choice!\n");
        }
        getch();
    }
}

