#include "stdio.h"
#include "config.h"
#include "utils.h"
#include "lexer.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        exitWithMessage("invalid command.\nplease enter be like: g-- <.cmm file>", 1);
    }

    char* filename = argv[1];
    if (!endsWith(filename, ".cmm")) {
        exitWithMessage("not a .cmm file", 1);
    }

    int length;
    char filepath[MAX_FILENAME];
    sprintf(filepath, filename);
    char* content = readFile(filepath, &length);

    lexer(content, length);
}

