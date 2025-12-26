#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cart.h"

unsigned int hashFunction(int id) {
    return id % HASH_SIZE;
}

void initCart(ShoppingCart* cart) {
    cart->count = 0;
    for (int i = 0; i < HASH_SIZE; i++) {
        cart->hashTable[i] = NULL;
    }
}

void rebuildHashTable(ShoppingCart* cart) {
    for (int i = 0; i < HASH_SIZE; i++) {
        cart->hashTable[i] = NULL;
    }
    for (int i = 0; i < cart->count; i++) {
        unsigned int hashIndex = hashFunction(cart->items[i].id);
        cart->hashTable[hashIndex] = &cart->items[i];
    }
}

void insertItem(ShoppingCart* cart, int id, const char* name, float price) {
    if (cart->count >= MAX_ITEMS) {
        printf("Cart is full!\n");
        return;
    }
    unsigned int hashIndex = hashFunction(id);
    if (cart->hashTable[hashIndex] != NULL && cart->hashTable[hashIndex]->id != id) {
        printf("Error: Hash collision detected for ID %d.\n", id);
        printf("Another item (ID %d) already uses this hash slot.\n", cart->hashTable[hashIndex]->id);
        printf("This simple hash table cannot handle this.\n");
        return;
    }
    for(int i = 0; i < cart->count; i++) {
        if (cart->items[i].id == id) {
            printf("Item with this ID already exists. Use Update.\n");
            return;
        }
    }
    Item newItem = {id, "", price};
    strncpy(newItem.name, name, NAME_LENGTH - 1);
    newItem.name[NAME_LENGTH - 1] = '\0';
    cart->items[cart->count] = newItem;
    cart->hashTable[hashIndex] = &cart->items[cart->count];
    cart->count++;
    
    printf("Item inserted: %s\n", name);
}

void deleteItem(ShoppingCart* cart, int id) {
    int foundIndex = -1;
    for (int i = 0; i < cart->count; i++) {
        if (cart->items[i].id == id) {
            foundIndex = i;
            break;
        }
    }
    if (foundIndex == -1) {
        printf("Item not found.\n");
        return;
    }
    for (int j = foundIndex; j < cart->count - 1; j++) {
        cart->items[j] = cart->items[j + 1];
    }
    cart->count--;
    rebuildHashTable(cart);
    printf("Item deleted.\n");
}

Item* searchItem(ShoppingCart* cart, int id) {
    unsigned int hashIndex = hashFunction(id);
    Item* item = cart->hashTable[hashIndex];

    if (item != NULL && item->id == id) {
        return item;
    }
    return NULL;
}

void updateItem(ShoppingCart* cart, int id, const char* name, float price) {
    Item* item = searchItem(cart, id);
    if (item != NULL) {
        strncpy(item->name, name, NAME_LENGTH - 1);
        item->name[NAME_LENGTH - 1] = '\0';
        item->price = price;
        printf("Item updated.\n");
    } else {
        printf("Item not found.\n");
    }
}

void printCart(ShoppingCart* cart) {
    if (cart->count == 0) {
        printf("\nCart is empty.\n");
        return;
    }
    printf("\n--- Items in cart (%d) ---\n", cart->count);
    for (int i = 0; i < cart->count; i++) {
        printf("ID: %-5d | Name: %-20s | Price: $%.2f\n",
               cart->items[i].id, cart->items[i].name, cart->items[i].price);
    }
    printf("---------------------------\n");
}
