/*
 * @Author: yinn
 * @Date: 2022-12-01 08:19:36
 * @LastEditTime: 2022-12-01 19:02:11
 * @Description: The entry of the program, parse the arguements and read the corresponding .cmm file
 */

#include "utils.h"
#include "lexer.h"

// Usage: ./g-- <.cmm file>
int main(int argc, char* argv[]) {
    if (argc != 2) {
        exitWithErr("invalid command.\nusage: ./g-- <.cmm file>", 1);
    }

    char* filename = argv[1];
    if (!endsWith(filename, ".cmm")) {
        exitWithErr("not a .cmm file", 1);
    }

    char* codeStr = readFile(filename);

    Token tokens[MAX_TOKEN];
    int len;
    lexer(codeStr, tokens, &len);

    return 0;
}