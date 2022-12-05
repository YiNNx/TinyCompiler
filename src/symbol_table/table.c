/*
 * @Author: yinn
 * @Date: 2022-12-03 16:08:34
 * @LastEditTime: 2022-12-05 16:11:15
 * @Description: Symbol Table
 */

#include "table.h"
#include"utils.h"

SymbolTable* tableTree;

void initSymbolTable() {
    SymbolTable* globalTable = (SymbolTable*)malloc(sizeof(SymbolTable));
    globalTable->scope = SCOPE_GLOBAL;
    globalTable->size = 0;
    globalTable->function = NULL;
    globalTable->parent = NULL;
    globalTable->left = NULL;
    globalTable->right = NULL;
    tableTree = globalTable;
}

void setSymbol(char* identity, int type, int scope, char* function) {
    if (scope == SCOPE_GLOBAL) {
        SymbolTable* table = tableTree;
        if (table->size >= MAX_SYMBOL) {
            exitWithErr("the number of symbols exceeds MAX_SYMBOL", 1);
        }

        table->table[table->size].identity = identity;
        table->table[table->size].type = type;
        table->size += 1;
    }
    else {
        // SymbolTable* table = getFuncTable(function);
        // if (table == NULL) {
        //     table = createFuncTable(function);
        // }
        // if (table->size >= MAX_SYMBOL) {
        //     exitWithErr("the number of symbols exceeds MAX_SYMBOL", 1);
        // }

        // table->table[table->size].identity = identity;
        // table->table[table->size].type = type;
        // table->size += 1;
    }
}

int getSymbol(char* varName) {
    return 0;
}