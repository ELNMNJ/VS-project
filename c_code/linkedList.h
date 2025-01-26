#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct Pokemon {
    unsigned short number;
    char name[22];
    unsigned short hp;
    unsigned short atk;
    unsigned short def;
    unsigned short spa;
    unsigned short spd;
    unsigned short speed;
} Pokemon;

typedef struct Node {
    Pokemon data;
    struct Node *next;
} Node;

typedef struct LinkedList {
    Node *head;
    Node *tail;
} LinkedList;

void initList(LinkedList *list);
void insertSorted(LinkedList *list, Pokemon pokemon);
void printList(LinkedList *list);
void updateNode(LinkedList *list, unsigned short number, Pokemon newData);
void deleteNode(LinkedList *list, unsigned short number);

#endif