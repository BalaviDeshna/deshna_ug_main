#ifndef SHOPPING_CART_H
#define SHOPPING_CART_H

#define MAX_ITEMS 100
#define NAME_LENGTH 50
#define HASH_SIZE 50

typedef struct {
    int id;
    char name[NAME_LENGTH];
    float price;
} Item;

typedef struct {
    Item items[MAX_ITEMS];
    int count;
    Item* hashTable[HASH_SIZE];
} ShoppingCart;

unsigned int hashFunction(int id);
void initCart(ShoppingCart* cart);
void insertItem(ShoppingCart* cart, int id, const char* name, float price);
void deleteItem(ShoppingCart* cart, int id);
Item* searchItem(ShoppingCart* cart, int id);
void updateItem(ShoppingCart* cart, int id, const char* name, float price);
void printCart(ShoppingCart* cart);

#endif