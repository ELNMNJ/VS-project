#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"

// 리스트 초기화
void initList(LinkedList *list) {
    list->head = NULL;
    list->tail = NULL;
}

// 정렬된 상태로 노드 추가
void insertSorted(LinkedList *list, Pokemon pokemon) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = pokemon;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else if (list->head->data.number >= pokemon.number) {
        // 새로운 노드가 첫 번째 노드보다 작거나 같을 때
        newNode->next = list->head;
        list->head = newNode;
    } else {
        Node *current = list->head;
        while (current->next != NULL && current->next->data.number < pokemon.number) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

// 리스트 순환하며 출력
void printList(LinkedList *list) {
    Node *current = list->head;
    if (current == NULL) {
        printf("리스트가 비어있습니다.\n");
        return;
    }
    while (current != NULL) {
        printf("Number: %d, Name: %s, HP: %d, ATK: %d, DEF: %d, SPA: %d, SPD: %d, SPEED: %d\n",
               current->data.number, current->data.name, current->data.hp, 
               current->data.atk, current->data.def, current->data.spa, 
               current->data.spd, current->data.speed);
        current = current->next;
    }
}

// 특정 number의 노드 업데이트
void updateNode(LinkedList *list, unsigned short number, Pokemon newData) {
    Node *current = list->head;
    while (current != NULL) {
        if (current->data.number == number) {
            current->data = newData;
            printf("노드가 업데이트 되었습니다.\n");
            return;
        }
        current = current->next;
    }
    printf("해당 번호의 포켓몬을 찾을 수 없습니다.\n");
}

// 특정 number의 노드 삭제
void deleteNode(LinkedList *list, unsigned short number) {
    Node *current = list->head;
    Node *prev = NULL;

    while (current != NULL) {
        if (current->data.number == number) {
            if (prev == NULL) { // 첫 번째 노드 삭제
                list->head = current->next;
                if (list->head == NULL) { // 마지막 노드까지 삭제된 경우
                    list->tail = NULL;
                }
            } else {
                prev->next = current->next;
                if (current->next == NULL) { // 마지막 노드 삭제
                    list->tail = prev;
                }
            }
            free(current);
            printf("노드가 삭제되었습니다.\n");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("해당 번호의 포켓몬을 찾을 수 없습니다.\n");
}

/*
int main() {
    LinkedList list;
    initList(&list);

    // 예시 데이터 추가
    Pokemon p1 = {1, "Bulbasaur", 45, 49, 49, 65, 65, 45};
    Pokemon p2 = {4, "Charmander", 39, 52, 43, 60, 50, 65};
    addNode(&list, p1);
    addNode(&list, p2);

    printList(&list);

    // 업데이트 예시
    Pokemon newData = {1, "Updated Bulbasaur", 50, 50, 50, 70, 70, 50};
    updateNode(&list, 1, newData);

    printList(&list);

    // 삭제 예시
    deleteNode(&list, 4);

    printList(&list);

    // 리스트의 헤드와 테일을 NULL로 설정하여 리스트가 비어있음을 나타냅니다.
    list->head = NULL;
    list->tail = NULL;
}