#ifndef LINKEDLIST_H
#define LINKEDLIST_H

// 演算子の種類
typedef enum {
    OP_BT, OP_EBT, OP_EQ, OP_LT, OP_ELT, OP_UNKNOWN
} Operator;

//構造体宣言部
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

//関数宣言部
void initList(LinkedList *list);
void insertSorted(LinkedList *list, Pokemon pokemon, int outputPlag);
void printList(LinkedList *list);
void updateNode(LinkedList *list, unsigned short number, char *parameter, unsigned short value);
void deleteNode(LinkedList *list, unsigned short number);
void printListByOperator(LinkedList *list, char *parameter, unsigned short value, int operator);
void printListByTwoOperator(LinkedList *list, char *parameter1, unsigned short value1, int operator1, char *parameter2, unsigned short value2, int operator2);
void freeLinkedList(LinkedList *list);

#endif