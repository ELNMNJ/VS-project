#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parser.h"
#include "linkedList.h"


// 문자열을 연산자로 변환
Operator stringToOperator(const char *str) {
    if (strcmp(str, "bt") == 0) return OP_BT;
    if (strcmp(str, "ebt") == 0) return OP_EBT;
    if (strcmp(str, "eq") == 0) return OP_EQ;
    if (strcmp(str, "lt") == 0) return OP_LT;
    if (strcmp(str, "elt") == 0) return OP_ELT;
    return OP_UNKNOWN;
}

// SQL 문을 파싱하는 함수
SQLParsed parseSQL(const char *sql) {
    SQLParsed result = {SQL_UNKNOWN};
    char *token;
    char temp[MAX_INPUT_SIZE];
    strcpy(temp, sql);

    token = strtok(temp, " ");
    if (token == NULL) return result;

    if (strcmp(token, "select") == 0) {
        result.type = SQL_SELECT;
        token = strtok(NULL, " ");
        strncpy(result.para1, token, sizeof(result.para1) - 1);
        token = strtok(NULL, " ");
        result.op1 = stringToOperator(token);
        token = strtok(NULL, " ");
        result.val1 = atoi(token);
        token = strtok(NULL, " ");
        if (token != NULL && strcmp(token, "and") == 0) {
            token = strtok(NULL, " ");
            strncpy(result.para2, token, sizeof(result.para2) - 1);
            token = strtok(NULL, " ");
            result.op2 = stringToOperator(token);
            token = strtok(NULL, " ");
            result.val2 = atoi(token);
        }else{
            strncpy(result.para2, "none", sizeof(result.para2) - 1);
        }
    } else if (strcmp(token, "insert") == 0) {
        result.type = SQL_INSERT;
        token = strtok(NULL, " ");
        result.number = (unsigned short)atoi(token);
        token = strtok(NULL, " ");
        strncpy(result.name, token, sizeof(result.name) - 1);
        token = strtok(NULL, " ");
        // 여기서 다른 능력치 값들을 파싱합니다.
        result.val1 = atoi(token);
        token = strtok(NULL, " ");
        result.val2 = atoi(token);
        token = strtok(NULL, " ");
        result.val3 = atoi(token);
        token = strtok(NULL, " ");
        result.val4 = atoi(token);
        token = strtok(NULL, " ");
        result.val5 = atoi(token);
        token = strtok(NULL, " ");
        result.val6 = atoi(token);
    } else if (strcmp(token, "update") == 0) {
        result.type = SQL_UPDATE;
        token = strtok(NULL, " ");
        result.number = (unsigned short)atoi(token);
        token = strtok(NULL, " ");
        strncpy(result.para1, token, sizeof(result.para1) - 1);
        token = strtok(NULL, " ");
        result.update_val = atoi(token);
    } else if (strcmp(token, "delete") == 0) {
        result.type = SQL_DELETE;
        token = strtok(NULL, " ");
        result.number = (unsigned short)atoi(token);
    }

    return result;
}

void runSQL(char *sql, LinkedList *list) {
    SQLParsed parsed = parseSQL(sql);
    switch (parsed.type) {
        case SQL_SELECT:
            //printf("SELECT: para1=%s, op1=%d, val1=%d, para2=%s, op2=%d, val2=%d\n",
            //       parsed.para1, parsed.op1, parsed.val1, parsed.para2, parsed.op2, parsed.val2);
            //operator가 unknown이면 에러 메시지 출력
            if(parsed.op1 == OP_UNKNOWN || parsed.op2 == OP_UNKNOWN){
                printf("間違った演算子\n");
                return;
            }
            
            //parameter가 unknown이면 에러 메시지 출력
            if(!(strcmp(parsed.para1, "number") == 0 || strcmp(parsed.para1, "hp") == 0 || strcmp(parsed.para1, "atk") == 0 || strcmp(parsed.para1, "def") == 0 || strcmp(parsed.para1, "spa") == 0 || strcmp(parsed.para1, "spd") == 0 || strcmp(parsed.para1, "speed") == 0)){
                printf("間違ったパラメータ : パラメータ１\n");
                break;
            }
            if(!(strcmp(parsed.para2, "number") == 0 || strcmp(parsed.para2, "hp") == 0 || strcmp(parsed.para2, "atk") == 0 || strcmp(parsed.para2, "def") == 0 || strcmp(parsed.para2, "spa") == 0 || strcmp(parsed.para2, "spd") == 0 || strcmp(parsed.para2, "speed") == 0 || strcmp(parsed.para2, "none") == 0)){
                printf("間違ったパラメータ : パラメータ２\n");
                break;
            }

            //case para1 only
            if(strcmp(parsed.para2, "none") == 0){
                printListByOperator(list, parsed.para1, parsed.val1, parsed.op1);
            }else{//case para1 and para2
                printListByTwoOperator(list, parsed.para1, parsed.val1, parsed.op1, parsed.para2, parsed.val2, parsed.op2);
            }

            break;
        case SQL_INSERT:
            //printf("INSERT: number=%d, name=%s, val1=%d, val2=%d\n", 
            //       parsed.number, parsed.name, parsed.val1, parsed.val2);
            Pokemon pokemon;
            pokemon.number = parsed.number;
            strncpy(pokemon.name, parsed.name, sizeof(pokemon.name) - 1);
            pokemon.name[sizeof(pokemon.name) - 1] = '\0';
            pokemon.hp = parsed.val1;
            pokemon.atk = parsed.val2;
            pokemon.def = parsed.val3;
            pokemon.spa = parsed.val4;
            pokemon.spd = parsed.val5;
            pokemon.speed = parsed.val6;
            insertSorted(list, pokemon, 1);
            break;
        case SQL_UPDATE:
            //printf("UPDATE: number=%d, para1=%s, update_val=%d\n", 
            //       parsed.number, parsed.para1, parsed.update_val);
            updateNode(list, parsed.number, parsed.para1, parsed.update_val);
            break;
        case SQL_DELETE:
            //printf("DELETE: number=%d\n", parsed.number);
            deleteNode(list, parsed.number);
            break;
        case SQL_UNKNOWN:
            printf("間違ったSQL文\n");
            break;
    }

}

// 테스트 함수
void testSQLParser() {
    const char *sql_commands[] = {
        //"select hp bt 50 and atk ebt 60",
        "select hp bt 50",
        "insert 1 Bulbasaur 45 49 49 65 65 45",
        "update 1 hp 50",
        "delete 1"
    };

    for (int i = 0; i < 4; i++) {
        SQLParsed parsed = parseSQL(sql_commands[i]);
        switch (parsed.type) {
            case SQL_SELECT:
                printf("SELECT: para1=%s, op1=%d, val1=%d, para2=%s, op2=%d, val2=%d\n",
                       parsed.para1, parsed.op1, parsed.val1, parsed.para2, parsed.op2, parsed.val2);
                break;
            case SQL_INSERT:
                printf("INSERT: number=%d, name=%s, val1=%d, val2=%d\n", 
                       parsed.number, parsed.name, parsed.val1, parsed.val2);
                break;
            case SQL_UPDATE:
                printf("UPDATE: number=%d, para1=%s, update_val=%d\n", 
                       parsed.number, parsed.para1, parsed.update_val);
                break;
            case SQL_DELETE:
                printf("DELETE: number=%d\n", parsed.number);
                break;
            case SQL_UNKNOWN:
                printf("Unknown SQL command\n");
                break;
        }
    }
}