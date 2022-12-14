/*
 * @Author: yinn
 * @Date: 2022-12-01 18:00:01
 * @LastEditTime: 2022-12-04 18:09:17
 * @Description: Helper functions to get each char of the code content
 */

#include "lexer.h"
#include "utils.h"

 // The content string read from the code file, init by initStr()
char* codeStr;

// The pointer of codeStr
int pointer = 0;

// Init codeStr
void initStr(char* s) {
    codeStr = s;
}

// Get the pointed char in str
char check() {
    if (codeStr[pointer] != '\0') {
        return codeStr[pointer];
    }
    else {
        return -1;
    }
}

// Get the pointed char in str
// And the pointer turns to the next char
char next() {
    if (codeStr[pointer] != '\0') {
        return codeStr[pointer++];
    }
    else {
        return -1;
    }
}

// Skip white char, get the first non-white char and go next
char skipWhite() {
    char c = next();
    while (isWhite(c)) {
        c = next();
    }
    return c;
}

char checkSkipWhite() {
    int i = pointer;
    while (isWhite(codeStr[i])) {
        i++;
    }
    return codeStr[i];
}

// Turn the pointer back
void back() {
    pointer--;
}
