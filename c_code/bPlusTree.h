#ifndef BPLUSTREE_H
#define BPLUSTREE_H

// 포켓몬 구조체 정의
typedef struct Pokemon {
    unsigned short number;
    char name[22];
    unsigned short atk;
    unsigned short hp;
    unsigned short def;
    unsigned short spa;
    unsigned short spd;
    unsigned short speed;
} Pokemon;

typedef struct Node {
    unsigned short is_leaf; // 이 노드가 리프 노드인지 여부
    int num_keys;           // 현재 노드에 있는 키의 수
    unsigned short *keys;   // 노드의 키 배열
    union {
        struct Node **children; // 내부 노드일 경우 자식 노드 포인터
        Pokemon **records;      // 리프 노드일 경우 포켓몬 레코드
    } ptr;
    struct Node *next;      // 다음 리프 노드에 대한 포인터
    struct Node *prev;      // 이전 리프 노드에 대한 포인터 (양방향 연결)
} Node;

// B+트리 자체의 구조체
typedef struct BPlusTree {
    int order;           // B+트리의 차수
    Node *root;          // 루트 노드
    Node *first_leaf;    // 첫 번째 리프 노드
} BPlusTree;

//함수 선언부
BPlusTree* createBPlusTree(int order);
Node* createNode(int order, int is_leaf);
void insertBPlusTree(BPlusTree *tree, Pokemon *pokemon, unsigned short key);
void insertNonFull(Node *node, BPlusTree *tree, Pokemon *pokemon, unsigned short key);
void splitChild(Node *parent, int i, int order);
void printTree(Node *node, int level);
void printBPlusTree(BPlusTree *tree);
void printAllLeafNodes(BPlusTree *tree);
void removeFromBPlusTree(BPlusTree *tree, unsigned short key);
void removeInternal(BPlusTree *tree, Node *node, unsigned short key);
void borrowFromLeftSibling(Node *parent, int idx, int leftSibling);
void borrowFromRightSibling(Node *parent, int idx, int rightSibling);
void mergeNodes(Node *parent, int idx1, int idx2);

#endif