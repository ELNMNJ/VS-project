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

    if (list->head == NULL || list->head->data.number > pokemon.number) {
        // 새로운 노드가 첫 번째 노드보다 작을 때
        newNode->next = list->head;
        list->head = newNode;
        if (newNode->next == NULL) list->tail = newNode; // 리스트에 노드가 하나뿐이었을 때
    } else {
        Node *current = list->head;
        while (current->next != NULL && current->next->data.number <= pokemon.number) {
            if (current->next->data.number == pokemon.number) {
                printf("이미 존재하는 번호입니다.\n");
                free(newNode); // 메모리 누수를 방지하기 위해 할당된 메모리 해제
                return;
            }
            current = current->next;
        }
        // 중복이 없고, 삽입 위치를 찾았다면
        newNode->next = current->next;
        current->next = newNode;
        if (newNode->next == NULL) list->tail = newNode; // 마지막 노드일 경우
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

void updateNode(LinkedList *list, unsigned short number, char *parameter, unsigned short value) {
    Node *current = list->head;
    while (current != NULL) {
        if (current->data.number == number) {
            if (strcmp(parameter, "hp") == 0) {
                current->data.hp = value;
            } else if (strcmp(parameter, "atk") == 0) {
                current->data.atk = value;
            } else if (strcmp(parameter, "def") == 0) {
                current->data.def = value;
            } else if (strcmp(parameter, "spa") == 0) {
                current->data.spa = value;
            } else if (strcmp(parameter, "spd") == 0) {
                current->data.spd = value;
            } else if (strcmp(parameter, "speed") == 0) {
                current->data.speed = value;
            } else {
                printf("Unknown parameter : %s\n", parameter);
                return;
            }
            printf("노드가 업데이트 되었습니다.\n");
            return;
        }
        current = current->next;
    }
    printf("해당 번호의 포켓몬을 찾을 수 없습니다.\n");
}

// 특정 operator에 따라 노드 출력
void printListByOperator(LinkedList *list, char *parameter, unsigned short value, int operator) {
    Node *current = list->head;
    if (current == NULL) {
        printf("리스트가 비어있습니다.\n");
        return;
    }
    while (current != NULL) {
        int compareValue = 0;
        if(strcmp(parameter, "number") == 0){
            compareValue = current->data.number;
        } else if (strcmp(parameter, "hp") == 0) {
            compareValue = current->data.hp;
        } else if (strcmp(parameter, "atk") == 0) {
            compareValue = current->data.atk;
        } else if (strcmp(parameter, "def") == 0) {
            compareValue = current->data.def;
        } else if (strcmp(parameter, "spa") == 0) {
            compareValue = current->data.spa;
        } else if (strcmp(parameter, "spd") == 0) {
            compareValue = current->data.spd;
        } else if (strcmp(parameter, "speed") == 0) {
            compareValue = current->data.speed;
        } else {
            printf("Unknown parameter : %s\n", parameter);
            return;
        }

        switch (operator) {
            case 0: // >
                if (compareValue > value) {
                    printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                    current->data.number, current->data.name, current->data.hp, 
                    current->data.atk, current->data.def, current->data.spa, 
                    current->data.spd, current->data.speed, current->data.name);
                }
                break;
            case 1: // >=
                if (compareValue >= value) {
                    printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                    current->data.number, current->data.name, current->data.hp, 
                    current->data.atk, current->data.def, current->data.spa, 
                    current->data.spd, current->data.speed, current->data.name);
                }
                break;
            case 2: // ==
                if (compareValue == value) {
                    printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                    current->data.number, current->data.name, current->data.hp, 
                    current->data.atk, current->data.def, current->data.spa, 
                    current->data.spd, current->data.speed, current->data.name);
                }
                break;
            case 3: // <
                if (compareValue < value) {
                    printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                    current->data.number, current->data.name, current->data.hp, 
                    current->data.atk, current->data.def, current->data.spa, 
                    current->data.spd, current->data.speed, current->data.name);
                }
                break;
            case 4: // <=
                if (compareValue <= value) {
                    printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                    current->data.number, current->data.name, current->data.hp, 
                    current->data.atk, current->data.def, current->data.spa, 
                    current->data.spd, current->data.speed, current->data.name);
                }
                break;
            default:
                printf("Unknown operator\n");
                return; 
        }
        current = current->next;
    }
}

// 두 개의 operator에 따라 노드 출력
void printListByTwoOperator(LinkedList *list, char *parameter1, unsigned short value1, int operator1, char *parameter2, unsigned short value2, int operator2) {
    Node *current = list->head;
    if (current == NULL) {
        printf("리스트가 비어있습니다.\n");
        return;
    }
    while (current != NULL) {
        int compareValue1 = 0;
        int compareValue2 = 0;
        if (strcmp(parameter1, "number") == 0){
            compareValue1 = current->data.number;
        }else if (strcmp(parameter1, "hp") == 0) {
            compareValue1 = current->data.hp;
        } else if (strcmp(parameter1, "atk") == 0) {
            compareValue1 = current->data.atk;
        } else if (strcmp(parameter1, "def") == 0) {
            compareValue1 = current->data.def;
        } else if (strcmp(parameter1, "spa") == 0) {
            compareValue1 = current->data.spa;
        } else if (strcmp(parameter1, "spd") == 0) {
            compareValue1 = current->data.spd;
        } else if (strcmp(parameter1, "speed") == 0) {
            compareValue1 = current->data.speed;
        } else if (strcmp(parameter1, "number") == 0) {
            compareValue1 = current->data.number;
        } else {
            printf("Unknown parameter : %s\n", parameter1);
            return;
        }

        if (strcmp(parameter2, "number") == 0){
            compareValue2 = current->data.number;
        }else if (strcmp(parameter2, "hp") == 0) {
            compareValue2 = current->data.hp;
        } else if (strcmp(parameter2, "atk") == 0) {
            compareValue2 = current->data.atk;
        } else if (strcmp(parameter2, "def") == 0) {
            compareValue2 = current->data.def;
        } else if (strcmp(parameter2, "spa") == 0) {
            compareValue2 = current->data.spa;
        } else if (strcmp(parameter2, "spd") == 0) {
            compareValue2 = current->data.spd;
        } else if (strcmp(parameter2, "speed") == 0) {
            compareValue2 = current->data.speed;
        } else if(strcmp(parameter2, "number") == 0) {
            compareValue2 = current->data.number;
        } else {
            printf("Unknown parameter : %s\n", parameter2);
            return;
        }

        switch (operator1) {
            case 0: // >
                if (compareValue1 > value1) {
                    switch (operator2) {
                        case 0: // >
                            if (compareValue2 > value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                    current->data.number, current->data.name, current->data.hp, 
                                    current->data.atk, current->data.def, current->data.spa, 
                                    current->data.spd, current->data.speed, current->data.name);
                            }
                            break;
                        case 1: // >=
                            if (compareValue2 >= value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                    current->data.number, current->data.name, current->data.hp, 
                                    current->data.atk, current->data.def, current->data.spa, 
                                    current->data.spd, current->data.speed, current->data.name);
                            }
                            break;
                        case 2: // ==
                            if (compareValue2 == value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        case 3: // <
                            if (compareValue2 < value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        case 4: // <=
                            if (compareValue2 <= value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        default:
                            printf("Unknown operator\n");
                            return;
                    }
                }
                break;
            case 1: // >=
                if (compareValue1 >= value1) {
                    switch (operator2) {
                        case 0: // >
                            if (compareValue2 > value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        case 1: // >=
                            if (compareValue2 >= value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        case 2: // ==
                            if (compareValue2 == value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        case 3: // <
                            if (compareValue2 < value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        case 4: // <=
                            if (compareValue2 <= value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        default:
                            printf("Unknown operator\n");
                            return;
                    }
                }
                break;
            case 2: // ==
                if (compareValue1 == value1) {
                    switch (operator2) {
                        case 0: // >
                            if (compareValue2 > value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        case 1: // >=
                            if (compareValue2 >= value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        case 2: // ==
                            if (compareValue2 == value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        case 3: // <
                            if (compareValue2 < value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        case 4: // <=
                            if (compareValue2 <= value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        default:
                            printf("Unknown operator\n");
                            return;
                    }
                }
                break;
            case 3: // <
                if (compareValue1 < value1) {
                    switch (operator2) {
                        case 0: // >
                            if (compareValue2 > value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        case 1: // >=
                            if (compareValue2 >= value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        case 2: // ==
                            if (compareValue2 == value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        case 3: // <
                            if (compareValue2 < value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        case 4: // <=
                            if (compareValue2 <= value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        default:
                            printf("Unknown operator\n");
                            return;
                    }
                }
                break;
            case 4: // <=
                if (compareValue1 <= value1) {
                    switch (operator2) {
                        case 0: // >
                            if (compareValue2 > value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        case 1: // >=
                            if (compareValue2 >= value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        case 2: // ==
                            if (compareValue2 == value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        case 3: // <
                            if (compareValue2 < value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        case 4: // <=
                            if (compareValue2 <= value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        default:
                            printf("Unknown operator\n");
                            return;
                    }
                }
                break;
            default:
                printf("Unknown operator\n");
                return;
        }
        current = current->next;
    }
}

// 특정 number의 노드 삭제
void deleteNode(LinkedList *list, unsigned short number) {
    if (list->head == NULL) {
        printf("리스트가 비어 있습니다.\n");
        return;
    }

    Node *current = list->head;
    Node *prev = NULL;

    while (current != NULL) {
        if (current->data.number == number) {
            if (prev == NULL) { // 첫 번째 노드 삭제
                list->head = current->next;
                if (list->head == NULL) { // 리스트가 비어졌을 때
                    list->tail = NULL;
                }
            } else {
                prev->next = current->next;
                if (current->next == NULL) { // 마지막 노드 삭제
                    list->tail = prev;
                }
            }
            free(current);  // 메모리 해제
            printf("노드가 삭제되었습니다.\n");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("해당 번호의 포켓몬을 찾을 수 없습니다.\n");
}

void freeLinkedList(LinkedList *list) {
    Node *current = list->head;
    Node *next;

    while (current != NULL) {
        next = current->next;
        free(current); // 현재 노드 해제
        current = next;
    }
    
    // 리스트의 헤드와 테일을 NULL로 설정하여 리스트가 비어있음을 나타냅니다.
    list->head = NULL;
    list->tail = NULL;
}