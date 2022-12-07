/*
 * @Author: yinn
 * @Date: 2022-12-03 16:08:34
 * @LastEditTime: 2022-12-07 23:36:22
 * @Description: Symbol Table
 */

#include "table.h"
#include"utils.h"

SymbolStack* symbolTable;

void initTable() {
    symbolTable = (SymbolStack*)malloc(sizeof(SymbolStack));
    symbolTable->table[0].type = SYMBOL_SCOPE;
    symbolTable->pointer = 1;
    printf("---------- global table ----------\n");
}

// Push scope: Enter a new scope.
void pushScope() {
    if (symbolTable->pointer >= MAX_SYMBOL - 1) {
        exitWithErr("symbols num out of range", 1);
    }
    symbolTable->pointer++;
    symbolTable->table[symbolTable->pointer].type = SYMBOL_SCOPE;
    printf("---------- push scope ------------\n");
}

// Pop scope: Leave a scope, discarding all declarations in it.
void popScope() {
    for (int i = symbolTable->pointer;i >= 0;i--) {
        if (symbolTable->table[i].type == SYMBOL_SCOPE) {
            symbolTable->pointer = i - 1;
        }
    }
    printf("---------- pop scope ------------\n");

}

// Insert symbol: Add a new entry to the current scope.
void insertSymbol(char* id, int type) {
    if (symbolTable->pointer >= MAX_SYMBOL - 1) {
        exitWithErr("symbols num out of range", 1);
    }
    symbolTable->pointer++;
    symbolTable->table[symbolTable->pointer].identity = id;
    symbolTable->table[symbolTable->pointer].type = type;
    printf("var %s\n", id);

}

void insertFuncSymbol(char* id, int type, int returnType, int* params) {
    if (symbolTable->pointer >= MAX_SYMBOL - 1) {
        exitWithErr("symbols num out of range", 1);
    }
    symbolTable->pointer++;
    symbolTable->table[symbolTable->pointer].identity = id;
    symbolTable->table[symbolTable->pointer].type = type;
    symbolTable->table[symbolTable->pointer].funcProperty.returnType = returnType;
    symbolTable->table[symbolTable->pointer].funcProperty.paramType = params;
    printf("func %s\n", id);
}

// Lookup symbol: Find what a name corresponds to.
Symbol* lookupSymbol(char* id) {
    for (int i = symbolTable->pointer;i >= 0;i--) {
        if (strcmp(symbolTable->table[i].identity, id) == 0) {
            return &symbolTable->table[i];
        }
    }
    return NULL;
}

