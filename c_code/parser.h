#ifndef PARSER_H
#define PARSER_H
#include "linkedList.h"

#define MAX_INPUT_SIZE 256

// 연산자 목록
typedef enum {
    OP_BT, OP_EBT, OP_EQ, OP_LT, OP_ELT, OP_UNKNOWN
} Operator;

// SQL 구문의 종류
typedef enum {
    SQL_SELECT, SQL_INSERT, SQL_UPDATE, SQL_DELETE, SQL_UNKNOWN
} SQLType;

typedef struct {
    SQLType type;
    unsigned short number; // 포켓몬 번호
    char name[22];
    char para1[5]; // 최대 4자리 문자열로 가정
    char para2[5];
    Operator op1;
    Operator op2;
    int val1;
    int val2;
    int update_val;
} SQLParsed;

//함수 선언부
Operator stringToOperator(const char *str);
SQLParsed parseSQL(const char *sql);
void runSQL(char *sql, LinkedList *list);
void testSQLParser();

#endif