#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedList.h"
#include "parser.h"

//リストの初期化
void initList(LinkedList *list) {
    list->head = NULL;
    list->tail = NULL;
}

//整列された状況でリストに挿入
void insertSorted(LinkedList *list, Pokemon pokemon, int outputPlag) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->data = pokemon;
    newNode->next = NULL;

    if (list->head == NULL || list->head->data.number > pokemon.number) {
        //新しいノードがリストの先頭になる場合
        newNode->next = list->head;
        list->head = newNode;
        if (newNode->next == NULL) list->tail = newNode; //リストに1つのノードしかない場合

        if (outputPlag){
            printf("ポケモンがリストに追加されました。\n");
        }
    } else {
        Node *current = list->head;
        while (current->next != NULL && current->next->data.number <= pokemon.number) {
            if (current->next->data.number == pokemon.number) {
                printf("既に存在する番号です。\n");
                free(newNode); // メモリー解放
                return;
            }
            current = current->next;
        }
        //重複がない場合
        newNode->next = current->next;
        current->next = newNode;
        if (newNode->next == NULL) list->tail = newNode; //最後のノードの場合

        if (outputPlag){
            printf("ポケモンがリストに追加されました。\n");
        }
    }
}

//全体のリストを出力
void printList(LinkedList *list) {
    Node *current = list->head;
    if (current == NULL) {
        printf("リストが空っぽです。\n");
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

//特定の番号のポケモンの能力値を修正
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
            printf("ポケモンのリストがアップデートされました。\n");
            return;
        }
        current = current->next;
    }
    printf("番号に該当するポケモンが存在しません。\n");
}

// 演算子の種類によってリストを出力
void printListByOperator(LinkedList *list, char *parameter, unsigned short value, int operator) {
    Node *current = list->head;
    if (current == NULL) {
        printf("リストが空っぽです。\n");
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
            case OP_BT: // >
                if (compareValue > value) {
                    printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                    current->data.number, current->data.name, current->data.hp, 
                    current->data.atk, current->data.def, current->data.spa, 
                    current->data.spd, current->data.speed, current->data.name);
                }
                break;
            case OP_EBT: // >=
                if (compareValue >= value) {
                    printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                    current->data.number, current->data.name, current->data.hp, 
                    current->data.atk, current->data.def, current->data.spa, 
                    current->data.spd, current->data.speed, current->data.name);
                }
                break;
            case OP_EQ: // ==
                if (compareValue == value) {
                    printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                    current->data.number, current->data.name, current->data.hp, 
                    current->data.atk, current->data.def, current->data.spa, 
                    current->data.spd, current->data.speed, current->data.name);
                }
                break;
            case OP_LT: // <
                if (compareValue < value) {
                    printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                    current->data.number, current->data.name, current->data.hp, 
                    current->data.atk, current->data.def, current->data.spa, 
                    current->data.spd, current->data.speed, current->data.name);
                }
                break;
            case OP_ELT: // <=
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

// 2つの演算子の種類によってリストを出力
void printListByTwoOperator(LinkedList *list, char *parameter1, unsigned short value1, int operator1, char *parameter2, unsigned short value2, int operator2) {
    Node *current = list->head;
    if (current == NULL) {
        printf("リストが空っぽです。\n");
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
            case OP_BT: // >
                if (compareValue1 > value1) {
                    switch (operator2) {
                        case OP_BT: // >
                            if (compareValue2 > value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                    current->data.number, current->data.name, current->data.hp, 
                                    current->data.atk, current->data.def, current->data.spa, 
                                    current->data.spd, current->data.speed, current->data.name);
                            }
                            break;
                        case OP_EBT: // >=
                            if (compareValue2 >= value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                    current->data.number, current->data.name, current->data.hp, 
                                    current->data.atk, current->data.def, current->data.spa, 
                                    current->data.spd, current->data.speed, current->data.name);
                            }
                            break;
                        case OP_EQ: // ==
                            if (compareValue2 == value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        case OP_LT: // <
                            if (compareValue2 < value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        case OP_ELT: // <=
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
            case OP_EBT: // >=
                if (compareValue1 >= value1) {
                    switch (operator2) {
                        case OP_BT: // >
                            if (compareValue2 > value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        case OP_EBT: // >=
                            if (compareValue2 >= value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        case OP_EQ: // ==
                            if (compareValue2 == value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        case OP_LT: // <
                            if (compareValue2 < value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        case OP_ELT: // <=
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
            case OP_EQ: // ==
                if (compareValue1 == value1) {
                    switch (operator2) {
                        case OP_BT: // >
                            if (compareValue2 > value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        case OP_EBT: // >=
                            if (compareValue2 >= value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        case OP_EQ: // ==
                            if (compareValue2 == value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        case OP_LT: // <
                            if (compareValue2 < value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        case OP_ELT: // <=
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
            case OP_LT: // <
                if (compareValue1 < value1) {
                    switch (operator2) {
                        case OP_BT: // >
                            if (compareValue2 > value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        case OP_EBT: // >=
                            if (compareValue2 >= value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        case OP_EQ: // ==
                            if (compareValue2 == value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        case OP_LT: // <
                            if (compareValue2 < value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        case OP_ELT: // <=
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
            case OP_ELT: // <=
                if (compareValue1 <= value1) {
                    switch (operator2) {
                        case OP_BT: // >
                            if (compareValue2 > value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        case OP_EBT: // >=
                            if (compareValue2 >= value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        case OP_EQ: // ==
                            if (compareValue2 == value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        case OP_LT: // <
                            if (compareValue2 < value2) {
                                printf("number: %d\t Name: %-23s\t  hp: %-6d atk: %-6d def:%-6d spa:%-6d spd:%-6d speed:%-6d\n",
                                       current->data.number, current->data.name, current->data.hp, 
                                       current->data.atk, current->data.def, current->data.spa, 
                                       current->data.spd, current->data.speed);
                            }
                            break;
                        case OP_ELT: // <=
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

// 特定の番号のノードを削除
void deleteNode(LinkedList *list, unsigned short number) {
    if (list->head == NULL) {
        printf("リストが空っぽです。\n");
        return;
    }

    Node *current = list->head;
    Node *prev = NULL;

    while (current != NULL) {
        if (current->data.number == number) {
            if (prev == NULL) { //最初のノードを削除する場合
                list->head = current->next;
                if (list->head == NULL) { // リストが空の場合
                    list->tail = NULL;
                }
            } else {
                prev->next = current->next;
                if (current->next == NULL) { //　最後のノードを削除する場合
                    list->tail = prev;
                }
            }
            free(current);  // メモリー解放
            printf("番号に該当するポケモンが削除されました。\n");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("番号に該当するポケモンが存在しません。\n");
}

//メモリー解放
void freeLinkedList(LinkedList *list) {
    Node *current = list->head;
    Node *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    list->head = NULL;
    list->tail = NULL;
}