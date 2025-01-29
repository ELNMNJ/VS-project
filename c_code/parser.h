#ifndef PARSER_H
#define PARSER_H
#include "linkedList.h"

#define MAX_INPUT_SIZE 256

// 演算子の種類
typedef enum {
    OP_BT, OP_EBT, OP_EQ, OP_LT, OP_ELT, OP_UNKNOWN
} Operator;

// SQL構文の種類
typedef enum {
    SQL_SELECT, SQL_INSERT, SQL_UPDATE, SQL_DELETE, SQL_UNKNOWN
} SQLType;

typedef struct {
    SQLType type;
    unsigned short number; // ポケモンの番号
    char name[22];
    char para1[7];
    char para2[7];
    Operator op1;
    Operator op2;
    int val1;
    int val2;
    int val3;
    int val4;
    int val5;
    int val6;
    int update_val;
} SQLParsed;

//関数宣言部
Operator stringToOperator(const char *str);
SQLParsed parseSQL(const char *sql);
void runSQL(char *sql, LinkedList *list);
void testSQLParser();

#endif