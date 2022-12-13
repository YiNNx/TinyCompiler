/*
 * @Author: yinn
 * @Date: 2022-12-05 11:29:31
 * @LastEditTime: 2022-12-13 22:08:37
 * @Description:
 */

#pragma once

#include "utils.h"

enum symbolType {
    SYMBOL_INT,
    SYMBOL_FUNC,
    SYMBOL_SCOPE,
};

typedef struct Symbol {
    char* identity;       // identity of Symbol
    int type;             // symbol type
    struct {
        int returnType;   // DECL_INT or DECL_VOID
        int* paramType;
        int paramsLen;
    } funcProperty;
}Symbol;

typedef struct SymbolStack {
    struct Symbol table[MAX_SYMBOL];
    int pointer;
}SymbolStack;

void initTable();

void addInternalFuction();

// Push scope: Enter a new scope.
void pushScope();

// Pop scope: Leave a scope, discarding all declarations in it.
void popScope();

// Insert symbol: Add a new entry to the current scope.
void insertSymbol(char* id, int type);

void insertFuncSymbol(char* id, int type, int returnType, int*, int len);

// Lookup symbol: Find what a name corresponds to.
Symbol* lookupSymbol(char* id);

Symbol* lookupFuncSymbol(char* id);

Symbol* lookupSymbolAtCurrentScope(char* id);

