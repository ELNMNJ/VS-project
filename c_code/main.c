#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "linkedList.h"

// 테스트
int main() {
    
    LinkedList list;
    initList(&list);

    FILE *file = fopen("pokemonList.txt", "r");
    if (file == NULL) {
        perror("파일 열기 실패");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        // 배열 크기 재조정
        Pokemon *pokemon = malloc(sizeof(Pokemon));
        // 각 라인의 데이터를 구조체에 매핑
        if (sscanf(line, "%hu %21s %hu %hu %hu %hu %hu %hu", 
            &pokemon->number, pokemon->name, &pokemon->hp, &pokemon->atk, &pokemon->def, &pokemon->spa, &pokemon->spd, &pokemon->speed) == 8) {
            insertSorted(&list, *pokemon);
        } else {
            // 형식이 맞지 않는 경우 처리. 여기서는 무시함.
            printf("잘못된 형식의 줄: %s\n", line);
        }
    }

    fclose(file);

    char sql[80];

    while (1) {
        printf("SQL 구문을 입력하세요 [종료 하려면 exit입력] : ");
        fgets(sql, sizeof(sql), stdin);
        sql[strlen(sql) - 1] = '\0'; // 개행문자 제거

        if (strcmp(sql, "exit") == 0) {
            // 파일을 쓰기 모드로 다시 열기
            file = fopen("pokemonList.txt", "w");
            if (file == NULL) {
                perror("파일 쓰기 모드로 열기 실패");
                // 여기서 리스트의 메모리를 해제하고 종료해야 합니다.
                return 1;
            }

            // 리스트의 모든 노드를 파일에 쓰기
            Node *current = list.head;
            while (current != NULL) {
                fprintf(file, "%hu %s %hu %hu %hu %hu %hu %hu\n", 
                    current->data.number, current->data.name, 
                    current->data.hp, current->data.atk, current->data.def, 
                    current->data.spa, current->data.spd, current->data.speed);
                current = current->next;
            }

            fclose(file);
            break;
        }

        runSQL(sql, &list);
    }

    freeLinkedList(&list);

    return 0;
}