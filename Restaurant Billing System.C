#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Item {
    char name[30];
    int quantity;
    float price;
};

struct Bill {
    char customer[50];
    struct Item items[10];
    int itemCount;
    float total;
};

void generateInvoice() {
    struct Bill bill;
    printf("Enter customer name: ");
    scanf(" %[^\n]", bill.customer);

    printf("Enter number of items: ");
    scanf("%d", &bill.itemCount);

    bill.total = 0;
    for (int i = 0; i < bill.itemCount; i++) {
        printf("Item %d name: ", i + 1);
        scanf(" %[^\n]", bill.items[i].name);
        printf("Quantity: ");
        scanf("%d", &bill.items[i].quantity);
        printf("Price: ");
        scanf("%f", &bill.items[i].price);
        bill.total += bill.items[i].quantity * bill.items[i].price;
    }

    FILE *fp = fopen("RestaurantBill.dat", "ab");
    fwrite(&bill, sizeof(struct Bill), 1, fp);
    fclose(fp);

    printf("\n--- Invoice ---\n");
    printf("Customer: %s\n", bill.customer);
    for (int i = 0; i < bill.itemCount; i++) {
        printf("%s x %d = ₹%.2f\n", bill.items[i].name, bill.items[i].quantity,
               bill.items[i].quantity * bill.items[i].price);
    }
    printf("Total: ₹%.2f\n", bill.total);
}

void showAllInvoices() {
    struct Bill bill;
    FILE *fp = fopen("RestaurantBill.dat", "rb");

    if (fp == NULL) {
        printf("No invoices found.\n");
        return;
    }

    printf("\n--- All Invoices ---\n");
    while (fread(&bill, sizeof(struct Bill), 1, fp)) {
        printf("\nCustomer: %s\n", bill.customer);
        for (int i = 0; i < bill.itemCount; i++) {
            printf("%s x %d = ₹%.2f\n", bill.items[i].name, bill.items[i].quantity,
                   bill.items[i].quantity * bill.items[i].price);
        }
        printf("Total: ₹%.2f\n", bill.total);
    }
    fclose(fp);
}

void searchInvoice() {
    char name[50];
    struct Bill bill;
    int found = 0;

    printf("Enter customer name to search: ");
    scanf(" %[^\n]", name);

    FILE *fp = fopen("RestaurantBill.dat", "rb");
    if (fp == NULL) {
        printf("No invoices found.\n");
        return;
    }

    while (fread(&bill, sizeof(struct Bill), 1, fp)) {
        if (strcmp(bill.customer, name) == 0) {
            printf("\n--- Invoice Found ---\n");
            printf("Customer: %s\n", bill.customer);
            for (int i = 0; i < bill.itemCount; i++) {
                printf("%s x %d = ₹%.2f\n", bill.items[i].name, bill.items[i].quantity,
                       bill.items[i].quantity * bill.items[i].price);
            }
            printf("Total: ₹%.2f\n", bill.total);
            found = 1;
        }
    }
    fclose(fp);
    if (!found) {
        printf("No invoice found for %s\n", name);
    }
}

int main() {
    int choice;
    while (1) {
        printf("\n--- Copilot Café Billing System ---\n");
        printf("1. Generate Invoice\n");
        printf("2. Show All Invoices\n");
        printf("3. Search Invoice by Customer Name\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: generateInvoice(); break;
            case 2: showAllInvoices(); break;
            case 3: searchInvoice(); break;
            case 4: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}
