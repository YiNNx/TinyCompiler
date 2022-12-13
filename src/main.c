/*
 * @Author: yinn
 * @Date: 2022-12-01 08:19:36
 * @LastEditTime: 2022-12-08 20:48:05
 * @Description: The entry of the program, parse the arguements and read the corresponding .cmm file
 */
#include"generator.h"
#include "utils.h"
#include "lexer.h"
#include "parser.h"
#include "checker.h"

static void usage(char* prog) {
    fprintf(stderr, "Usage: %s [-SLTM] file\n", prog);
    fprintf(stderr, "       -L dump the lexer\n");
    fprintf(stderr, "       -T dump the AST tree\n");
    fprintf(stderr, "       -M dump the symbol table\n");
    fprintf(stderr, "       -S generate assembly files\n");
    exit(1);
}

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

int main(int argc, char* argv[]) {
    if (argc == 1) usage(argv[0]);

    char* codeFilepath = "";
    bool dumpLexer = false, dumpCode = false, dumpAST = false, dumpSym = false, assemble = false;

    // Scan for command-line options
    for (int i = 1; i < argc; i++) {
        if (*argv[i] != '-') codeFilepath = argv[i];

        // For each option in this argument
        for (int j = 1; (*argv[i] == '-') && argv[i][j]; j++) {
            switch (argv[i][j]) {
            case 'L':
                dumpLexer = true;
                break;
            case 'C':
                dumpCode = true;
                break;
            case 'T':
                dumpAST = true;
                break;
            case 'M':
                dumpSym = true;
                break;
            case 'S':
                assemble = true;
                break;
            default:
                usage(argv[0]);
            }
        }
    }

    if (!endsWith(codeFilepath, ".c")) {
        exitWithErr(".c file needed", 1);
    }

    char* codeStr = readFile(codeFilepath);
    if (dumpCode) printf("%s\n\n", codeStr);

    Token* tokenList;
    lexer(codeStr, &tokenList);
    if (dumpLexer) {
        printTokenList(tokenList);
        printf("\n\n");
    }

    ASTNode* ast = parser(tokenList);
    if (dumpAST) {
        printASTree(ast);
        printf("\n\n");
    }

    checker(ast, dumpSym);

    FILE* outfile = initOutfile(codeFilepath);
    generator(ast, outfile);

    fclose(outfile);
    free(codeStr);
    return 0;
}
