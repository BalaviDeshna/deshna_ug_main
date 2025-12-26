#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "cart.h"

void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void readString(char* buffer, int size) {
    fgets(buffer, size, stdin);
    buffer[strcspn(buffer, "\n")] = 0;  // replace \n w \0
}

int main() {
    ShoppingCart cart;
    initCart(&cart);
    int choice, id;
    char name[NAME_LENGTH];
    float price;
    while (1) {
        printf("\n--- Shopping Cart Menu ---\n");
        printf("1. Insert Item\n");
        printf("2. Delete Item\n");
        printf("3. Search Item\n");
        printf("4. Update Item\n");
        printf("5. Display Cart\n");
        printf("6. Exit\n");
        printf("Choose an option: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer(); // Clear bad input
            continue;
        }
        clearInputBuffer(); // Clear \n after scanf
        switch (choice) {
            case 1:
                printf("Enter ID: ");
                scanf("%d", &id);
                clearInputBuffer();

                printf("Enter Name: ");
                readString(name, NAME_LENGTH);

                printf("Enter Price: ");
                scanf("%f", &price);
                clearInputBuffer();

                insertItem(&cart, id, name, price);
                break;
            case 2:
                printf("Enter ID to delete: ");
                scanf("%d", &id);
                clearInputBuffer();
                deleteItem(&cart, id);
                break;
            case 3: {
                printf("Enter ID to search: ");
                scanf("%d", &id);
                clearInputBuffer();
                
                Item* item = searchItem(&cart, id);
                if (item)
                    printf("Found -> ID: %d | Name: %s | Price: $%.2f\n", item->id, item->name, item->price);
                else
                    printf("Item not found.\n");
                break;
            }
            case 4:
                printf("Enter ID to update: ");
                scanf("%d", &id);
                clearInputBuffer();

                printf("Enter new Name: ");
                readString(name, NAME_LENGTH);

                printf("Enter new Price: ");
                scanf("%f", &price);
                clearInputBuffer();
                
                updateItem(&cart, id, name, price);
                break;
            case 5:
                printCart(&cart);
                break;
            case 6:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
