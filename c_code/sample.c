#include "stdio.h"
#include "string.h"

struct Pokemon {
    int number;
    char name[20];
    int hp;
    int atk;
    int def;
    int spa;
    int spd;
    int speed;
};

struct IndexNode{
    int key;
    struct Node *childNode;
};

struct Node{
    int key;
    struct Pokemon pokemon;
    struct Node *leftNode;
    struct Node *rightNode;
};

struct BPTree{
    struct Node *root;
    int degree;
};

void init(struct Pokemon *monsterballPtr);
void insertInfo(struct Pokemon *pokemonPtr, int number, char *name, int hp, int atk, int def, int spa, int spd, int speed);

int main() {
    struct Pokemon monsterball[6];
    init(monsterball);

    for(int i = 0; i < 6; i++){
        printf("Number: %d\n", monsterball[i].number);
        printf("Name: %s\n", monsterball[i].name);
        printf("HP: %d\n", monsterball[i].hp);
        printf("Attack: %d\n", monsterball[i].atk);
        printf("Defense: %d\n", monsterball[i].def);
        printf("Special Attack: %d\n", monsterball[i].spa);
        printf("Special Defense: %d\n", monsterball[i].spd);
        printf("Speed: %d\n", monsterball[i].speed);
        printf("\n");
    }

    return 0;
}

void init(struct Pokemon *monsterballPtr){
    insertInfo(monsterballPtr, 1, "Bulbasaur", 45, 49, 49, 65, 65, 45); monsterballPtr++;
    insertInfo(monsterballPtr, 4, "Charmander", 39, 52, 43, 60, 50, 65); monsterballPtr++;
    insertInfo(monsterballPtr, 7, "Squirtle", 44, 48, 65, 50, 64, 43); monsterballPtr++;
    insertInfo(monsterballPtr, 25, "Pikachu", 35, 55, 40, 50, 50, 90); monsterballPtr++;
    insertInfo(monsterballPtr, 133, "Eevee", 55, 55, 50, 45, 65, 55); monsterballPtr++;
    insertInfo(monsterballPtr, 143, "Snorlax", 160, 110, 65, 65, 65, 30);
}

void insertInfo(struct Pokemon *pokemonPtr, int number, char *name, int hp, int atk, int spa, int spd, int def, int speed){
    pokemonPtr->number = number;
    strcpy(pokemonPtr->name, name);
    pokemonPtr->hp = hp;
    pokemonPtr->atk = atk;
    pokemonPtr->def = def;
    pokemonPtr->spa = spa;
    pokemonPtr->spd = spd;
    pokemonPtr->speed = speed;
}