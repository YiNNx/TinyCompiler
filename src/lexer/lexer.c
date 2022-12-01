/*
 * @Author: yinn
 * @Date: 2022-12-01 10:05:13
 * @LastEditTime: 2022-12-01 18:48:31
 * @Description: Core lexer functions
 */

#include "lexer.h"
#include "utils.h"

 /**
  * @description: Build the lexer using the DFA
  * @param codeContent Code content
  * @param tokens The result Token list after building
  * @param len The length of the result list
  */
void lexer(char* codeContent, Token* tokens, int* len) {
    initStr(codeContent);
    char c = skipWhite();
    int j = 0;
    while (c != -1) {
        Token* t = evalue(c);
        tokens[j] = *t;
        printToken(t);
        c = skipWhite();
        j++;
    }
    *len = j;
}

/**
 * @description: Process the current char
 * @param c The current char
 * @return Token formed by the current char (and backward)
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
        else if (isalpha(c) || isUnderline(c)) {
            int token;
            char word[MAX_VAR_NAME];

            getWord(c, word);
            if (compareWithKeywords(word, &token)) {
                t->token = token;
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
            exitWithErr("invalid char", 1);
        }
        break;
    }
    return t;
}

