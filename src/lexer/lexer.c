/*
 * @Author: yinn
 * @Date: 2022-12-01 10:05:13
 * @LastEditTime: 2022-12-01 17:00:09
 * @Description: lexer
 */

#include "token.h"
#include "stdio.h"
#include "stdlib.h"
#include "utils.h"
#include "config.h"
#include "string.h"
#include "lexer.h"
#include "ctype.h"

char* content;
int i = 0;

/**
 * @description: get the pointed char in str, and pointer ++
 * @return {*}
 */
char next() {
    if (content[i] != EOF) {
        return content[i++];
    }
    else {
        return -1;
    }
}

/**
 * @description: get the pointed char in str
 * @return {*}
 */
char check() {
    if (content[i] != EOF) {
        return content[i];
    }
    else {
        return -1;
    }
}

void back() {
    i--;
}

char skipWhite() {
    char c = next();
    while (isWhite(c)) {
        c = next();
    }
    return c;
}

void lexer(char* str) {
    content = str;
    char c = skipWhite();
    while (c != -1) {
        Token* t = evalue(c);
        printToken(t);
        c = skipWhite();
    }
}

/**
 * @description:
 * @param {char} c
 * @return {*}
 */
Token* evalue(char c) {
    Token* t = (Token*)malloc(sizeof(Token));
    switch (c)
    {
    case '+':
        t->token = PLUS;
        break;
    case '-':
        if (isdigit(check())) {
            int num = getDigitInt(check());
            t->token = DIGIT_INT;
            t->intVal = -num;
        }
        else {
            t->token = MINUS;
        }
        break;
    case '*':
        t->token = STAR;
        break;
    case '/':
        if (check() == '*') {
            next();
            while (next() != '*' && check() != '/');
            t->token = COMMENT;
            next();
        }
        else {
            t->token = DIV;
        }
        break;
    case '=':
        if (check() == '=') {
            t->token = EQL;
            next();
        }
        else {
            t->token = ASSIGN;
        }
        break;
    case '>':
        if (check() == '=') {
            t->token = GREATER_OR_EQL;
            next();
        }
        else {
            t->token = GREATER;
        }
        break;
    case '<':
        if (check() == '=') {
            t->token = LESS_OR_EQL;
            next();
        }
        else {
            t->token = LESS;
        }
        break;
    case '!':
        if (check() == '=') {
            t->token = NOT_EQL;
            next();
        }
        else {
            exitWithMessage("invalid token: single !", 1);
        }
        break;
    case ',':
        t->token = COMMA;
        break;
    case ';':
        t->token = SEMI;
        break;
    case '(':
        t->token = LC;
        break;
    case ')':
        t->token = RC;
        break;
    case '{':
        t->token = LP;
        break;
    case '}':
        t->token = RP;
        break;
    default:
        if (isdigit(c)) {
            int num = getDigitInt(c);
            t->token = DIGIT_INT;
            t->intVal = num;
        }
        else if (isalpha(c) || c == '_') {
            char word[MAX_VAR_NAME];
            getWord(c, word);
            if (strcmp(word, "int") == 0) {
                t->token = INT;
            }
            else if (strcmp(word, "void") == 0) {
                t->token = VOID;
            }
            else if (strcmp(word, "if") == 0) {
                t->token = IF;
            }
            else if (strcmp(word, "else") == 0) {
                t->token = ELSE;
            }
            else if (strcmp(word, "while") == 0) {
                t->token = WHILE;
            }
            else if (strcmp(word, "return") == 0) {
                t->token = RETURN;
            }
            else if (strcmp(word, "main") == 0) {
                t->token = MAIN;
            }
            else if (strcmp(word, "input") == 0) {
                t->token = INPUT;
            }
            else if (strcmp(word, "output") == 0) {
                t->token = OUTPUT;
            }
            else {
                t->wordVal = word;
                if (skipWhite() == '(') {
                    t->token = FUNC;
                }
                else {
                    t->token = VAR;
                }
                back();
            }
        }
        else if (isWhite(c)) {
        }
        else {
            exitWithMessage("invalid char", 1);
        }
        break;
    }
    return t;
}


int getDigitInt(char c) {
    int num = 0;
    while (isdigit(c)) {
        int d = charToInt(c);
        c = next();
        num = num * 10 + d;
    }
    if (isalpha(c)) {
        exitWithMessage("variable name or function name can't begin with digit", 1);
    }
    back();
    return num;
}

void getWord(char c, char* word) {
    int j = 0;
    while (isalpha(c) || isdigit(c) || c == '_') {
        word[j++] = c;
        c = next();
        if (j >= MAX_VAR_NAME) {
            exitWithMessage("variable name or function name too long", 1);
        }
    }
    word[j] = '\0';
    back();
}