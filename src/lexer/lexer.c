/*
 * @Author: yinn
 * @Date: 2022-12-01 10:05:13
 * @LastEditTime: 2022-12-04 18:15:00
 * @Description: Core lexer functions
 */

#include "lexer.h"
#include "utils.h"

 // Build the lexer using the DFA
void lexer(char* codeStr, Token** head) {
    initStr(codeStr);
    char c = skipWhite();
    Token* p = (Token*)malloc(sizeof(Token));
    (*head) = p;
    while (c != -1) {
        Token* t = match(c);
        c = skipWhite();
        if (t->token == TOKEN_COMMENT) continue;
        p->next = t;
        p = p->next;
    }
    p->next = NULL;
    free(codeStr);
}

// Process the current char
Token* match(char c) {
    Token* t = (Token*)malloc(sizeof(Token));
    switch (c)
    {
    case '+':
        t->token = TOKEN_PLUS;
        break;
    case '-':
        t->token = TOKEN_MINUS;
        break;
    case '*':
        t->token = TOKEN_STAR;
        break;
    case '/':
        if (check() == '*') {
            next();
            while (next() != '*' || check() != '/');
            t->token = TOKEN_COMMENT;
            next();
        }
        else {
            t->token = TOKEN_DIV;
        }
        break;
    case '=':
        if (check() == '=') {
            t->token = TOKEN_EQL;
            next();
        }
        else {
            t->token = TOKEN_ASSIGN;
        }
        break;
    case '>':
        if (check() == '=') {
            t->token = TOKEN_GREATER_OR_EQL;
            next();
        }
        else {
            t->token = TOKEN_GREATER;
        }
        break;
    case '<':
        if (check() == '=') {
            t->token = TOKEN_LESS_OR_EQL;
            next();
        }
        else {
            t->token = TOKEN_LESS;
        }
        break;
    case '!':
        if (check() == '=') {
            t->token = TOKEN_NOT_EQL;
            next();
        }
        else {
            exitWithErr("invalid token: single !", 1);
        }
        break;
    case ',':
        t->token = TOKEN_COMMA;
        break;
    case ';':
        t->token = TOKEN_SEMI;
        break;
    case '(':
        t->token = TOKEN_LP;
        break;
    case ')':
        t->token = TOKEN_RP;
        break;
    case '{':
        t->token = TOKEN_LC;
        break;
    case '}':
        t->token = TOKEN_RC;
        break;
    default:
        if (isdigit(c) && c != -1) {
            int num = getDigitInt(c);
            t->token = TOKEN_DIGIT_INT;
            t->intVal = num;
        }
        else if (isalpha(c) || isUnderline(c)) {
            int token;
            char word[MAX_VAR_NAME];

            getWord(c, word);
            if (compareWithKeywords(word, &token)) {
                t->token = token;
            }
            else {
                t->wordVal = (char*)malloc(sizeof(char) * MAX_VAR_NAME);
                strcpy(t->wordVal, word);
                if (checkSkipWhite() == '(') {
                    t->token = TOKEN_FUNC;
                }
                else {
                    t->token = TOKEN_VAR;
                }
            }
        }
        else if (isWhite(c)) {
        }
        else {
            exitWithErr("invalid char", 1);
        }
        break;
    }
    return t;
}

