/*
 * @Author: yinn
 * @Date: 2022-12-01 15:55:43
 * @LastEditTime: 2022-12-01 18:31:56
 * @Description: Helper functions for token
 */

#include "token.h"
#include"stdio.h"

 /**
  * @description: To get the emun name of TokenType
  */
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
    "GREATER",
    "LESS",
    "NOT_EQL",
    "EQL",
    "GREATER_OR_EQL",
    "LESS_OR_EQL",
    "DIGIT_INT",
    "VAR",
    "FUNC",
    "COMMA",
    "SEMI",
    "LP",
    "RP",
    "LC",
    "RC",
    "COMMENT",
    "MAIN",
    "INPUT",
    "OUTPUT",
};

/**
 * @description: Print property of single Token
 * @param t The Token
 */
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