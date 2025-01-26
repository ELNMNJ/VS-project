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
        // 여기서 다른 능력치 값들을 파싱합니다. 간단히 예시로 두 가지 능력치만 파싱.
        result.val1 = atoi(token);
        token = strtok(NULL, " ");
        result.val2 = atoi(token);
        // 나머지 능력치는 필요에 따라 추가 파싱 가능
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
            printf("SELECT: para1=%s, op1=%d, val1=%d, para2=%s, op2=%d, val2=%d\n",
                   parsed.para1, parsed.op1, parsed.val1, parsed.para2, parsed.op2, parsed.val2);
            if(parsed.op1 == OP_UNKNOWN || parsed.op2 == OP_UNKNOWN){
                printf("Unknown operator\n");
                return;
            }
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