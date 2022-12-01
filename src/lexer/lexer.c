/*
 * @Author: yinn
 * @Date: 2022-12-01 10:05:13
 * @LastEditTime: 2022-12-01 15:04:37
 * @Description: lexer
 */

#include "lexer.h"
#include "stdio.h"
#include "stdlib.h"
#include "utils.h"
#include "config.h"
#include "string.h"

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

char skip() {
    char c = next();
    while (isWhite(c)) {
        c = next();
    }
    return c;
}

void lexer(char* str) {
    content = str;

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
        if (isDigit(check())) {
            int num = getDigitInt(check());
            t->token = DIGIT_INT;
            t->intVal = -num;
        }
        else {
            t->token = MINUS;
            break;
        }
    case '*':
        if (check() == '/') {
            t->token = RNOTE;
            next();
        }
        else {
            t->token = STAR;
            break;
        }
    case '/':
        if (check() == '*') {
            t->token = LNOTE;
            next();
        }
        else {
            t->token = DIV;
            break;
        }
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
    default:
        if (isDigit(c)) {
            int num = getDigitInt(c);
            t->token = DIGIT_INT;
            t->intVal = num;
        }
        else if (isLetter(c)) {
            char word[MAX_VAR_NAME];
            int j = 0;
            while (isLetter(c) || isDigit(c)) {
                word[j++] = c;
                if (j >= MAX_VAR_NAME - 1) {
                    exitWithMessage("variable name or function name too long", 1);
                }
            }
            word[j + 1] = '\0';
        }

    }
    return t;
}

int getDigitInt(char c) {
    int num = 0;
    while (isDigit(c)) {
        int d = charToInt(c);
        c = next();
        num = num * 10 + d;
    }
    if (isLetter(c)) {
        exitWithMessage("variable name or function name can't begin with digit", 1);
    }
    back();
    return num;
}


// int scan(struct token* t) {
//     int c;

//     // Skip whitespace
//     c = skip();

//     // Determine the token based on
//     // the input character
//     switch (c) {
//     case EOF:
//         return (0);
//     case '+':
//         t->token = PLUS;
//         break;
//     case '-':
//         t->token = MINUS;
//         break;
//     case '*':
//         t->token = STAR;
//         break;
//     case '/':
//         t->token = DIV;
//         break;
//     default:
//         // More here soon
//     }

//     // We found a token
//     return (1);
// }

// static int skip(void) {
//     char c;

//     c = next();
//     while (' ' == c || '\t' == c || '\n' == c || '\r' == c || '\f' == c) {
//         c = next();
//     }
//     return (c);
// }

// static char next() {

// }