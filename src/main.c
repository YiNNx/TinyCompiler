/*
 * @Author: yinn
 * @Date: 2022-12-01 08:19:36
 * @LastEditTime: 2022-12-07 23:35:12
 * @Description: The entry of the program, parse the arguements and read the corresponding .cmm file
 */
#include"generator.h"
#include "utils.h"
#include "lexer.h"
#include "parser.h"
#include "checker.h"

FILE* initOutfile(char* codeFilepath) {
    int dot = '.';
    int div = '/';
    char* path = (char*)malloc(sizeof(codeFilepath));
    strcpy(path, codeFilepath);
    char* res = strrchr(path, dot);
    strcpy(res, ".s");
    char* f = strrchr(path, div);
    FILE* outfile = fopen(++f, "w+");
    free(path);
    return outfile;
}

// Usage: ./g-- <.cmm file>
int main(int argc, char* argv[]) {
    if (argc != 2) {
        exitWithErr("invalid command.\nusage: ./g-- <.cmm file>", 1);
    }

    char* codeFilepath = argv[1];
    if (!endsWith(codeFilepath, ".c")) {
        exitWithErr("not a .c file", 1);
    }

    char* codeStr = readFile(codeFilepath);
    printf("%s\n------\n", codeStr);

    Token* tokenList;
    lexer(codeStr, &tokenList);
    printTokenList(tokenList);
    printf("------\n");

    ASTNode* ast = parser(tokenList);
    printASTree(ast);

    checker(ast);

    FILE* outfile = initOutfile(codeFilepath);
    generator(ast, outfile);

    fclose(outfile);
    free(codeStr);
    return 0;
}
