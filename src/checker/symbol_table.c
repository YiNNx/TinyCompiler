/*
 * @Author: yinn
 * @Date: 2022-12-03 16:08:34
 * @LastEditTime: 2022-12-13 22:07:35
 * @Description: Symbol Table
 */

#include "checker.h"
#include "table.h"
#include"utils.h"
#include"ast.h"

SymbolStack* symbolTable;

void initTable() {
    symbolTable = (SymbolStack*)malloc(sizeof(SymbolStack));
    symbolTable->table[0].type = SYMBOL_SCOPE;
    symbolTable->pointer = 0;
    if (dumpSym) printGlobal();
}

void addInternalFuction() {
    int outputParams[1] = { DECL_INT };
    insertFuncSymbol("input", SYMBOL_FUNC, DECL_INT, NULL, 0);
    insertFuncSymbol("output", SYMBOL_FUNC, DECL_VOID, outputParams, 1);
}

// Push scope: Enter a new scope.
void pushScope() {
    if (symbolTable->pointer >= MAX_SYMBOL - 1) {
        exitWithErr("symbols num out of range", 1);
    }
    symbolTable->pointer++;
    symbolTable->table[symbolTable->pointer].type = SYMBOL_SCOPE;
    if (dumpSym) printPushScope();
}

// Pop scope: Leave a scope, discarding all declarations in it.
void popScope() {
    for (int i = symbolTable->pointer;i >= 0;i--) {
        if (symbolTable->table[i].type == SYMBOL_SCOPE) {
            symbolTable->pointer = i - 1;
            break;
        }
    }
    if (dumpSym) printPopScope();
}

// Insert symbol: Add a new entry to the current scope.
void insertSymbol(char* id, int type) {
    if (symbolTable->pointer >= MAX_SYMBOL - 1) {
        exitWithErr("symbols num out of range", 1);
    }
    symbolTable->pointer++;
    symbolTable->table[symbolTable->pointer].identity = id;
    symbolTable->table[symbolTable->pointer].type = type;
    if (dumpSym) printVarSymbol(id);
}

void insertFuncSymbol(char* id, int type, int returnType, int* params, int len) {
    if (symbolTable->pointer >= MAX_SYMBOL - 1) {
        exitWithErr("symbols num out of range", 1);
    }
    symbolTable->pointer++;
    symbolTable->table[symbolTable->pointer].identity = id;
    symbolTable->table[symbolTable->pointer].type = type;
    symbolTable->table[symbolTable->pointer].funcProperty.returnType = returnType;
    symbolTable->table[symbolTable->pointer].funcProperty.paramType = params;
    if (dumpSym) printFuncSymbol(id, returnType, len, params);
}

// Lookup symbol: Find what a name corresponds to.
Symbol* lookupSymbol(char* id) {
    for (int i = symbolTable->pointer;i >= 0;i--) {
        if (symbolTable->table[i].identity != NULL && strcmp(symbolTable->table[i].identity, id) == 0) {
            return &symbolTable->table[i];
        }
    }
    return NULL;
}

Symbol* lookupFuncSymbol(char* id) {
    for (int i = 1;symbolTable->table[i].type != SYMBOL_SCOPE;i++) {
        if (symbolTable->table[i].identity != NULL && strcmp(symbolTable->table[i].identity, id) == 0 && symbolTable->table[i].type == SYMBOL_FUNC) {
            return &symbolTable->table[i];
        }
    }
    return NULL;
}

// Lookup symbol: Find what a name corresponds to.
Symbol* lookupSymbolAtCurrentScope(char* id) {
    for (int i = symbolTable->pointer;i >= 0;i--) {
        if (symbolTable->table[i].type == SYMBOL_SCOPE) return NULL;
        if (symbolTable->table[i].identity != NULL && strcmp(symbolTable->table[i].identity, id) == 0) {
            return &symbolTable->table[i];
        }
    }
    return NULL;
}


void printGlobal() {
    printf("------------ global --------------\n");
}

void printPopScope() {
    printf("---------- pop scope ------------\n");
}

void printPushScope() {
    printf("---------- push scope ------------\n");
}

void printVarSymbol(char* id) {
    printf("[var] %s\n", id);
}

void printFuncSymbol(char* id, int returnType, int len, int* params) {
    printf("[func] %s [ret] %s [params] ", id, varTypes[returnType]);
    for (int i = 0;i < len;i++) {
        printf("%s ", varTypes[params[i]]);
    }
    printf("\n");
}