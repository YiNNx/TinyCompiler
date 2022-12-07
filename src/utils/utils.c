/*
 * @Author: yinn
 * @Date: 2022-12-01 09:11:50
 * @LastEditTime: 2022-12-07 14:44:51
 * @Description: Util functions
 */

#include "utils.h"

 // Dynamically read the file with variable length
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
    data[length] = '\0';
    fclose(pfile);
    return data;
}

// Compare the suffix
bool endsWith(const char* str, const char* suffix) {
    if (!str || !suffix)
        return false;
    size_t lenstr = strlen(str);
    size_t lensuffix = strlen(suffix);
    if (lensuffix > lenstr)
        return false;
    return strncmp(str + lenstr - lensuffix, suffix, lensuffix) == 0;
}

void exitWithErr(char* msg, int errCode) {
    fprintf(stderr, msg);
    exit(errCode);
}

bool isUnderline(char c) {
    return c == '_';
}

bool isWhite(char c) {
    return c == ' ' || c == '\t' || c == '\n';
}

int charToInt(char c) {
    if (!isdigit(c)) {
        exitWithErr("charToInt() went wrong", 1);
    }
    return c - '0';
}