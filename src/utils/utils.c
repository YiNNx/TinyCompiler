/*
 * @Author: yinn
 * @Date: 2022-12-01 09:11:50
 * @LastEditTime: 2022-12-01 15:06:11
 * @Description: util functions
 */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

char* readFile(char* path) {
    FILE* pfile;
    char* data;

    pfile = fopen(path, "rb");
    if (pfile == NULL)
    {
        return NULL;
    }
    fseek(pfile, 0, SEEK_END);
    int length = ftell(pfile);
    data = (char*)malloc((length + 1) * sizeof(char));
    rewind(pfile);
    length = fread(data, 1, length, pfile);
    data[length] = EOF;
    fclose(pfile);
    return data;
}

int endsWith(const char* str, const char* suffix) {
    if (!str || !suffix)
        return 0;
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix > lenstr)
        return 0;
    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

void exitWithMessage(char* msg, int errCode) {
    printf(msg);
    exit(errCode);
}

int isDigit(char c) {
    return c >= '0' && c <= '9';
}

int isLetter(char c) {
    return c >= 'a' && c <= 'Z';
}

int isUnderline(char c) {
    return c == '_';
}

int isWhite(char c) {
    return c == ' ' || c == '\t' || c == '\n';
}

int charToInt(char c) {
    if (!isDigit(c)) {
        exitWithMessage("charToInt() went wrong", 1);
    }
    return c - '0';
}
