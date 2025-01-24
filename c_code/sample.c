#include "stdio.h"
#include "string.h"

typedef struct Pokemon {
    unsigned short number;
    char name[18];
    unsigned short hp;
    unsigned short atk;
    unsigned short def;
    unsigned short spa;
    unsigned short spd;
    unsigned short speed;
}Pokemon;

void init(Pokemon *monsterballPtr);
void insertInfo(Pokemon *pokemonPtr, unsigned short number, char *name, unsigned short hp, unsigned short atk, unsigned short def, unsigned short spa, unsigned short spd, unsigned short speed);

int main() {
    struct Pokemon monsterball[6];
    init(monsterball);

    for(int i = 0; i < 6; i++){
        Pokemon *temp = &monsterball[i];
        printf("%d\t\t", temp->number);
        printf("%-18s", temp->name);
        printf("%d\t", temp->hp);
        printf("%d\t", temp->atk);
        printf("%d\t", temp->def);
        printf("%d\t", temp->spa);
        printf("%d\t", temp->spd);
        printf("%d\n", temp->speed);
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

void insertInfo(Pokemon *pokemonPtr, unsigned short number, char *name, unsigned short hp, unsigned short atk, unsigned short def, unsigned short spa, unsigned short spd, unsigned short speed){
    pokemonPtr->number = number;
    strcpy(pokemonPtr->name, name);
    pokemonPtr->hp = hp;
    pokemonPtr->atk = atk;
    pokemonPtr->def = def;
    pokemonPtr->spa = spa;
    pokemonPtr->spd = spd;
    pokemonPtr->speed = speed;
}