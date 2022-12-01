/*
 * @Author: yinn
 * @Date: 2022-12-01 15:55:43
 * @LastEditTime: 2022-12-01 16:55:23
 * @Description:
 */

#include "token.h"
#include"stdio.h"

char* types[] = {
   "INT",
    "VOID",
    "IF",
    "ELSE",
    "WHILE",
    "RETURN",
    "WHITE",
    "PLUS",
    "MINUS",
    "STAR",
    "DIV",
    "ASSIGN",
    "GREATER", // >
    "LESS", // <
    "NOT_EQL", // !=
    "EQL", // ==
    "GREATER_OR_EQL", // >=
    "LESS_OR_EQL", // <=
    "DIGIT_INT",
    "VAR",
    "FUNC",
    "COMMA",
    "SEMI",
    "LP", // (
    "RP", // )
    "LC", // {
    "RC", // }
    "COMMENT", // /* note */
    "MAIN",
    "INPUT",
    "OUTPUT",
};

void printToken(Token* t) {
    if (t->token == DIGIT_INT) {
        printf("%s: %d,\n", types[t->token], t->intVal);
    }
    else if (t->token == VAR || t->token == FUNC) {
        printf("%s: %s,\n", types[t->token], t->wordVal);
    }
    else {
        printf("%s,\n", types[t->token]);
    }
}