/*
 * @Author: yinn
 * @Date: 2022-12-05 11:29:31
 * @LastEditTime: 2022-12-05 16:11:28
 * @Description:
 */

#include"utils.h"

enum symbolType {
    SYMBOL_INT,
    SYMBOL_FUNC,
};

enum scope {
    SCOPE_GLOBAL,
    SCOPE_INNER,
};

typedef struct Symbol {
    char* identity;
    int type;
}Symbol;

typedef struct SymbolTable {
    int scope;
    char* function;
    struct Symbol table[MAX_SYMBOL];
    int size;

    bool isGlue;
    struct SymbolTable* parent;
    struct SymbolTable* left;
    struct SymbolTable* right;
}SymbolTable;


void initSymbolTable();

void setSymbol(char* identity, int type, int scope, char* function);

int getSymbol(char* varName);