/*
 * @Author: yinn
 * @Date: 2022-12-01 10:05:13
 * @LastEditTime: 2022-12-04 12:35:48
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
        printToken(t);
        p->next = t;
        p = p->next;
        c = skipWhite();
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
        t->token = PLUS;
        break;
    case '-':
        // if (isdigit(check())) {
        //     int num = getDigitInt(check());
        //     t->token = DIGIT_INT;
        //     t->intVal = -num;
        // }
        // else {
        t->token = MINUS;
        // }
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
            exitWithErr("invalid token: single !", 1);
        }
        break;
    case ',':
        t->token = COMMA;
        break;
    case ';':
        t->token = SEMI;
        break;
    case '(':
        t->token = LP;
        break;
    case ')':
        t->token = RP;
        break;
    case '{':
        t->token = LC;
        break;
    case '}':
        t->token = RC;
        break;
    default:
        if (isdigit(c) && c != -1) {
            int num = getDigitInt(c);
            t->token = DIGIT_INT;
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
            exitWithErr("invalid char", 1);
        }
        break;
    }
    return t;
}

