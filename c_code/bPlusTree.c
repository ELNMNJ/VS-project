#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bPlusTree.h"

#define MAX_KEYS 3  // B+트리에서 최대 키 개수 (차수 - 1)

// B+트리 생성 함수
BPlusTree* createBPlusTree(int order) {
    BPlusTree *tree = (BPlusTree *)malloc(sizeof(BPlusTree));
    tree->order = order;
    tree->root = NULL;
    tree->first_leaf = NULL;
    return tree;
}

Node* createNode(int order, int is_leaf) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->is_leaf = is_leaf;
    node->num_keys = 0;
    node->keys = (unsigned short *)malloc((order - 1) * sizeof(unsigned short));
    if (is_leaf) {
        node->ptr.records = (Pokemon **)malloc(order * sizeof(Pokemon *));
        node->next = NULL;
        node->prev = NULL; // 새 노드의 prev 포인터를 NULL로 초기화
    } else {
        node->ptr.children = (Node **)malloc(order * sizeof(Node *));
    }
    return node;
}

// B+트리 삽입
void insertBPlusTree(BPlusTree *tree, Pokemon *pokemon, unsigned short key) {
    if (tree->root == NULL) {
        // 트리가 비어있는 경우, 새로운 리프 노드를 루트로 만듦
        Node *new_leaf = createNode(tree->order, 1);
        tree->root = new_leaf;
        tree->first_leaf = new_leaf;
        new_leaf->keys[0] = key;
        new_leaf->ptr.records[0] = pokemon;
        new_leaf->num_keys = 1;
        return;
    }

    Node *root = tree->root;
    if (root->num_keys == (tree->order - 1)) {
        // 루트가 꽉 차면, 새 루트를 만들고 기존 루트를 분할
        Node *new_root = createNode(tree->order, 0);
        tree->root = new_root;
        new_root->ptr.children[0] = root;
        splitChild(new_root, 0, tree->order);
        insertNonFull(new_root, tree, pokemon, key);
    } else {
        insertNonFull(root, tree, pokemon, key);
    }
}

// 비어있지 않은 노드에 삽입
void insertNonFull(Node *node, BPlusTree *tree, Pokemon *pokemon, unsigned short key) {
    int i = node->num_keys - 1;
    if (node->is_leaf) {
        // 리프 노드에 삽입
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            node->ptr.records[i + 1] = node->ptr.records[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->ptr.records[i + 1] = pokemon;
        node->num_keys++;
    } else {
        // 내부 노드에 삽입
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;

        if (node->ptr.children[i]->num_keys == (tree->order - 1)) {
            splitChild(node, i, tree->order);
            if (key > node->keys[i]) {
                i++;
            }
        }
        insertNonFull(node->ptr.children[i], tree, pokemon, key);
    }
}

// 자식 노드 분할
void splitChild(Node *parent, int i, int order) {
    Node *y = parent->ptr.children[i];
    Node *z = createNode(order, y->is_leaf);
    z->num_keys = order - 1 - (order / 2);

    // 키와 레코드(또는 자식 노드)를 z로 이동
    for (int j = 0; j < z->num_keys; j++) {
        z->keys[j] = y->keys[j + order / 2];
        if (!y->is_leaf) {
            z->ptr.children[j] = y->ptr.children[j + order / 2];
        } else {
            z->ptr.records[j] = y->ptr.records[j + order / 2];
        }
    }
    if (y->is_leaf) {
        z->next = y->next;
        y->next = z;
    } else {
        z->ptr.children[z->num_keys] = y->ptr.children[order - 1];
    }

    // y의 키와 레코드 수 조정
    y->num_keys = order / 2;

    // 부모 노드에 삽입할 키와 자식 포인터 조정
    for (int j = parent->num_keys; j > i; j--) {
        parent->ptr.children[j + 1] = parent->ptr.children[j];
    }
    parent->ptr.children[i + 1] = z;

    for (int j = parent->num_keys - 1; j >= i; j--) {
        parent->keys[j + 1] = parent->keys[j];
    }
    parent->keys[i] = y->keys[y->num_keys - 1];
    parent->num_keys++;
}

Pokemon* searchBPlusTree(BPlusTree *tree, unsigned short key) {
    Node *current = tree->root;
    int i;

    while (current != NULL) {
        i = 0;
        // 현재 노드에서 키를 찾아가기
        while (i < current->num_keys && key > current->keys[i]) {
            i++;
        }

        if (current->is_leaf) {
            // 현재 노드가 리프 노드인 경우, 키와 일치하는 레코드를 찾음
            return (i < current->num_keys && key == current->keys[i]) ? current->ptr.records[i] : NULL;
        } else {
            // 내부 노드라면, 다음 노드로 이동
            current = current->ptr.children[i];
        }
    }
    return NULL;
}

void printTree(Node *node, int level) {
    if (node == NULL) {
        return;
    }

    // 현재 노드의 깊이만큼 들여쓰기
    for (int i = 0; i < level; i++) {
        printf("  ");
    }

    // 노드의 키 출력
    printf("Node (keys: ");
    for (int i = 0; i < node->num_keys; i++) {
        printf("%hu", node->keys[i]);
        if (i < node->num_keys - 1) {
            printf(", ");
        }
    }
    printf(")");

    if (node->is_leaf) {
        // 리프 노드인 경우, 포켓몬 정보 출력
        printf(", Leaf [");
        for (int i = 0; i < node->num_keys; i++) {
            Pokemon *pokemon = node->ptr.records[i];
            printf("(%hu, %s)", pokemon->number, pokemon->name);
            if (i < node->num_keys - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    } else {
        // 내부 노드인 경우, 다음 줄에 자식 노드 출력
        printf("\n");
        for (int i = 0; i <= node->num_keys; i++) {
            printTree(node->ptr.children[i], level + 1);
        }
    }
}

// 트리의 전체 구조를 출력하는 함수
void printBPlusTree(BPlusTree *tree) {
    if (tree == NULL || tree->root == NULL) {
        printf("Tree is empty.\n");
        return;
    }
    printf("B+ Tree:\n");
    printTree(tree->root, 0);
}

void printAllLeafNodes(BPlusTree *tree) {
    if (tree == NULL || tree->first_leaf == NULL) {
        printf("Tree is empty or has no leaf nodes.\n");
        return;
    }

    printf("All Leaf Nodes:\n");
    Node *current = tree->first_leaf;

    // 첫 번째 리프 노드부터 시작하여 마지막 노드까지 순회
    while (current != NULL) {
        printf("Leaf Node (keys: ");
        for (int i = 0; i < current->num_keys; i++) {
            printf("%hu", current->keys[i]);
            if (i < current->num_keys - 1) {
                printf(", ");
            }
        }
        printf(") [");

        // 포켓몬 정보 출력
        for (int i = 0; i < current->num_keys; i++) {
            Pokemon *pokemon = current->ptr.records[i];
            printf("(%hu, %s)", pokemon->number, pokemon->name);
            if (i < current->num_keys - 1) {
                printf(", ");
            }
        }
        printf("]\n");

        // 다음 리프 노드로 이동
        current = current->next;
    }
}

void removeFromBPlusTree(BPlusTree *tree, unsigned short key) {
    if (tree->root == NULL) {
        printf("Tree is empty.\n");
        return;
    }

    removeInternal(tree, tree->root, key);

    // 삭제 후 루트가 비었으면, 루트를 첫 번째 자식으로 설정
    if (tree->root->num_keys == 0 && !tree->root->is_leaf) {
        Node *tmp = tree->root;
        tree->root = tree->root->ptr.children[0];
        free(tmp);
    }
}

void removeInternal(BPlusTree *tree, Node *node, unsigned short key) {
    int idx = 0;
    while (idx < node->num_keys && key > node->keys[idx]) {
        idx++;
    }

    if (node->is_leaf) {
        // 리프 노드에서 삭제
        if (idx < node->num_keys && key == node->keys[idx]) {
            for (int i = idx + 1; i < node->num_keys; i++) {
                node->keys[i - 1] = node->keys[i];
                node->ptr.records[i - 1] = node->ptr.records[i];
            }
            node->num_keys--;
        }
        return;
    } else {
        // 내부 노드에서 삭제
        Node *child = node->ptr.children[idx];
        if (child->num_keys >= tree->order / 2) {
            removeInternal(tree, child, key);
        } else {
            int leftSibling = (idx > 0) ? idx - 1 : -1;
            int rightSibling = (idx < node->num_keys) ? idx + 1 : -1;
            int toMerge;

            if (leftSibling != -1 && node->ptr.children[leftSibling]->num_keys > tree->order / 2 - 1) {
                toMerge = leftSibling;
                borrowFromLeftSibling(node, idx, toMerge);
            } else if (rightSibling != -1 && node->ptr.children[rightSibling]->num_keys > tree->order / 2 - 1) {
                toMerge = rightSibling;
                borrowFromRightSibling(node, idx, toMerge);
            } else {
                if (leftSibling != -1) {
                    toMerge = leftSibling;
                    mergeNodes(node, toMerge, idx);
                } else {
                    toMerge = rightSibling;
                    mergeNodes(node, idx, toMerge);
                }
                removeInternal(tree, node->ptr.children[toMerge], key);
                return;
            }
            removeInternal(tree, child, key);
        }
    }
}

void borrowFromLeftSibling(Node *parent, int idx, int leftSibling) {
    Node *child = parent->ptr.children[idx];
    Node *left = parent->ptr.children[leftSibling];

    // child에 left의 마지막 키를 추가
    for (int i = child->num_keys - 1; i >= 0; i--) {
        child->keys[i + 1] = child->keys[i];
    }
    child->keys[0] = left->keys[left->num_keys - 1];
    if (!child->is_leaf) {
        for (int i = child->num_keys; i >= 0; i--) {
            child->ptr.children[i + 1] = child->ptr.children[i];
        }
        child->ptr.children[0] = left->ptr.children[left->num_keys];
    }

    // parent의 키를 수정
    parent->keys[idx - 1] = left->keys[left->num_keys - 1];

    child->num_keys++;
    left->num_keys--;
}

void borrowFromRightSibling(Node *parent, int idx, int rightSibling) {
    Node *child = parent->ptr.children[idx];
    Node *right = parent->ptr.children[rightSibling];

    // child에 right의 첫 번째 키를 추가
    child->keys[child->num_keys] = right->keys[0];
    if (!child->is_leaf) {
        child->ptr.children[child->num_keys + 1] = right->ptr.children[0];
    }

    // parent의 키를 수정
    parent->keys[idx] = right->keys[0];

    // right에서 키를 하나 제거
    for (int i = 1; i < right->num_keys; i++) {
        right->keys[i - 1] = right->keys[i];
    }
    if (!right->is_leaf) {
        for (int i = 1; i <= right->num_keys; i++) {
            right->ptr.children[i - 1] = right->ptr.children[i];
        }
    }

    child->num_keys++;
    right->num_keys--;
}

void mergeNodes(Node *parent, int idx1, int idx2) {
    Node *child1 = parent->ptr.children[idx1];
    Node *child2 = parent->ptr.children[idx2];

    // child1에 child2의 모든 키와 자식(있으면) 추가
    child1->keys[child1->num_keys] = parent->keys[idx1 > idx2 ? idx1 - 1 : idx1];

    for (int i = 0; i < child2->num_keys; i++) {
        child1->keys[child1->num_keys + 1 + i] = child2->keys[i];
    }
    if (!child1->is_leaf) {
        for (int i = 0; i <= child2->num_keys; i++) {
            child1->ptr.children[child1->num_keys + 1 + i] = child2->ptr.children[i];
        }
    }
    child1->num_keys = child1->num_keys + child2->num_keys + 1;

    // parent에서 키와 자식 노드 수정
    for (int i = idx1 + 1; i < parent->num_keys; i++) {
        parent->keys[i - 1] = parent->keys[i];
        parent->ptr.children[i] = parent->ptr.children[i + 1];
    }
    parent->num_keys--;

    free(child2);
}

