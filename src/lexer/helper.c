/*
 * @Author: yinn
 * @Date: 2022-12-01 15:51:11
 * @LastEditTime: 2022-12-06 00:07:00
 * @Description: Helper functions for lexer
 */

#include "lexer.h"
#include "utils.h"
#include "token.h"

 // Compare the word with keywords, and return the corresponding enum value
bool compareWithKeywords(char* word, int* token) {
    if (strcmp(word, "int") == 0) {
        *token = TOKEN_INT;
    }
    else if (strcmp(word, "void") == 0) {
        *token = TOKEN_VOID;
    }
    else if (strcmp(word, "if") == 0) {
        *token = TOKEN_IF;
    }
    else if (strcmp(word, "else") == 0) {
        *token = TOKEN_ELSE;
    }
    else if (strcmp(word, "while") == 0) {
        *token = TOKEN_WHILE;
    }
    else if (strcmp(word, "return") == 0) {
        *token = TOKEN_RETURN;
    }
    // else if (strcmp(word, "main") == 0) {
    //     *token = TOKEN_MAIN;
    // }
    // else if (strcmp(word, "input") == 0) {
    //     *token = TOKEN_INPUT;
    // }
    // else if (strcmp(word, "output") == 0) {
    //     *token = TOKEN_OUTPUT;
    // }
    else {
        return false;
    }
    return true;
}

// Get a single contiguous number
int getDigitInt(char c) {
    int num = 0;
    back();
    while (isdigit(c) && c != -1) {
        next();
        int d = charToInt(c);
        c = check();
        num = num * 10 + d;
    }
    if (isalpha(c)) {
        exitWithErr("variable name or function name can't begin with digit", 1);
    }
    return num;
}

// Get a single contiguous word
void getWord(char c, char* word) {
    int j = 0;
    back();
    while (isalpha(c) || (isdigit(c) && c != -1) || isUnderline(c)) {
        next();
        word[j++] = c;
        c = check();
        if (j >= MAX_VAR_NAME) {
            exitWithErr("variable name or function name too long", 1);
        }
    }
    word[j] = '\0';
}