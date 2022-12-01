/*
 * @Author: yinn
 * @Date: 2022-12-01 15:51:11
 * @LastEditTime: 2022-12-01 18:56:04
 * @Description: Helper functions for lexer
 */

#include "lexer.h"
#include "utils.h"
#include "token.h"

 // Compare the word with keywords, and return the corresponding enum value
int compareWithKeywords(char* word, int* token) {
    if (strcmp(word, "int") == 0) {
        *token = INT;
    }
    else if (strcmp(word, "void") == 0) {
        *token = VOID;
    }
    else if (strcmp(word, "if") == 0) {
        *token = IF;
    }
    else if (strcmp(word, "else") == 0) {
        *token = ELSE;
    }
    else if (strcmp(word, "while") == 0) {
        *token = WHILE;
    }
    else if (strcmp(word, "return") == 0) {
        *token = RETURN;
    }
    else if (strcmp(word, "main") == 0) {
        *token = MAIN;
    }
    else if (strcmp(word, "input") == 0) {
        *token = INPUT;
    }
    else if (strcmp(word, "output") == 0) {
        *token = OUTPUT;
    }
    else {
        return 0;
    }
    return 1;
}

// Get a single contiguous int number
int getDigitInt(char c) {
    int num = 0;
    while (isdigit(c)) {
        int d = charToInt(c);
        c = next();
        num = num * 10 + d;
    }
    if (isalpha(c)) {
        exitWithErr("variable name or function name can't begin with digit", 1);
    }
    back();
    return num;
}

// Get a single contiguous string
void getWord(char c, char* word) {
    int j = 0;
    while (isalpha(c) || isdigit(c) || isUnderline(c)) {
        word[j++] = c;
        c = next();
        if (j >= MAX_VAR_NAME) {
            exitWithErr("variable name or function name too long", 1);
        }
    }
    word[j] = '\0';
    back();
}