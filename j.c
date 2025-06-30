#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>                   

#define MAX_PETS 4

typedef struct {
    unsigned isHungry : 1;
    unsigned isDirty : 1;
    unsigned isTired : 1;           
} PetStatus;

typedef enum {
    CAT, DOG, BIRD, RABBIT
} PetType;

typedef struct {
    int age;
    float weight;
} PetTrait;

typedef struct {
    char name[50];
    PetType type;
    int hunger;
    int cleanliness;
    int energy;
    PetStatus status;
    PetTrait trait;
} Pet;

void feed(Pet *p);
void clean(Pet *p);
void play(Pet *p);
void rest(Pet *p);
void updateStatus(Pet *p);
void decayStats(Pet *p);                            
void savePet(Pet *p, const char *filename);
void loadPet(Pet *p, const char *filename);
void printPet(const Pet *p);                    

int main() {
    Pet pets[MAX_PETS] = {
        {"Fluffy", CAT, 80, 90, 85, {0}, {2, 4.0}},
        {"Buddy", DOG, 70, 60, 80, {0}, {3, 8.0}},              
        {"Chirpy", BIRD, 75, 85, 90, {0}, {1, 0.5}},
        {"Qwerty", RABBIT, 60, 75, 85, {0},{1, 2.5}}             // name, type, hunger, clean, energy, status, age, wt
    };

    const char *filenames[MAX_PETS] = {"pet1.txt", "pet2.txt", "pet3.txt", "pet4.txt"};         

    for (int i = 0; i < MAX_PETS; i++) {
        FILE *fp = fopen(filenames[i], "rb");
        if (fp) {                                                   
            fread(&pets[i], sizeof(Pet), 1, fp);
            fclose(fp);
        } else {
            printf("Initializing default file for %s\n", pets[i].name);        
            savePet(&pets[i], filenames[i]);                              
        }
    }

    int choice, petIndex = 0;
    time_t lastTime = time(NULL);               

    while (1) {                                            
        printf("\n=== Virtual Pet Manager ===\n");
        for (int i = 0; i < MAX_PETS; i++) {
            printf("%d. %s (%s)\n", i+1, pets[i].name, pets[i].type == CAT ? "Cat" :
                                                           pets[i].type == DOG ? "Dog" :
                                                           pets[i].type == BIRD ? "Bird": "Rabbit");
        }
        printf("Choose a pet to manage (1-%d) or 0 to exit: ", MAX_PETS);
        scanf("%d", &choice);

        if (choice == 0) break;
        if (choice < 1 || choice > MAX_PETS) continue;      

        petIndex = choice - 1;
        Pet *pet = &pets[petIndex];

        while (1) {
            time_t now = time(NULL);                  
            if (difftime(now, lastTime) >= 5) {
                decayStats(pet);
                lastTime = now;
            }

            updateStatus(pet);
            printPet(pet);

            printf("\n1. Feed\n2. Clean\n3. Play\n4. Sleep\n5. Save\n6. Back\n");
            printf("Choice: ");
            scanf("%d", &choice);

            switch (choice) {
                case 1: feed(pet); break;
                case 2: clean(pet); break;
                case 3: play(pet); break;
                case 4: rest(pet); break;
                case 5: savePet(pet, filenames[petIndex]); break;
                case 6: goto outer_loop;                               
                default: printf("Invalid.\n");
            }
        }
        outer_loop:;                    
    }

    return 0;
}

void feed(Pet *p) {
    p->hunger += 25;
    if (p->hunger > 100) p->hunger = 100;
}

void clean(Pet *p) {
    p->cleanliness = 100;
}

void play(Pet *p) {
    p->energy -= 10;
    p->hunger -= 5;
    p->cleanliness -= 5;
}

void rest(Pet *p) {
    p->energy = 100;
}

void decayStats(Pet *p) {
    p->hunger -= 5;
    p->cleanliness -= 3;
    p->energy -= 4;
    if (p->hunger < 0) p->hunger = 0;
    if (p->cleanliness < 0) p->cleanliness = 0;             
    if (p->energy < 0) p->energy = 0;
}

void updateStatus(Pet *p) {
    p->status.isHungry = (p->hunger < 30);
    p->status.isDirty = (p->cleanliness < 40);
    p->status.isTired = (p->energy < 30);              
}

void savePet(Pet *p, const char *filename) {
    FILE *fp = fopen(filename, "wb");               
    if (fp) {
        fwrite(p, sizeof(Pet), 1, fp);
        fclose(fp);
    } else {
        printf("Failed to open file for writing.\n");
    }
}

void loadPet(Pet *p, const char *filename) {
    FILE *fp = fopen(filename, "rb");                   
    if (fp) {
        fread(p, sizeof(Pet), 1, fp);
        fclose(fp);
    }
}

void printPet(const Pet *p) {
    printf("\n-- Pet Status --\n");
    printf("Name: %s\n", p->name);
    printf("Satiety: %d\t(%s)\n", p->hunger, p->status.isHungry ? "Hungry" : "OK");
    printf("Cleanliness: %d\t(%s)\n", p->cleanliness, p->status.isDirty ? "Dirty" : "Clean");
    printf("Energy: %d\t(%s)\n", p->energy, p->status.isTired ? "Tired" : "Energetic");
    printf("Age: %d years\n", p->trait.age);
    printf("Weight: %.1f kg\n", p->trait.weight);
}

