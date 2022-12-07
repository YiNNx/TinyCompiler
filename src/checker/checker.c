/*
 * @Author: yinn
 * @Date: 2022-12-03 16:08:34
 * @LastEditTime: 2022-12-07 23:30:26
 * @Description: Symbol Table
 */
#include"checker.h"
#include "table.h"
#include"utils.h"

void checker(ASTNode* ast) {
    initTable();
    checkNode(ast);
}

void checkNode(ASTNode* node) {
    if (node == NULL) return;

    if (node->op == NODE_COMPOUND || node->op == NODE_FUNC_DECLARE) {
        pushScope();
        checkNode(node->left);
        checkNode(node->right);
        popScope();
    }
    else {
        checkNode(node->left);
        checkNode(node->right);
    }

    if (node->op == NODE_VAR_DECLARE) {
        insertSymbol(node->v.var.id, getVarSymbolType(node->v.var.type));
    }
    else if (node->op == NODE_FUNC_DECLARE) {
        int* params;
        getParamsList(node, &params);
        insertFuncSymbol(node->v.var.id, SYMBOL_FUNC, node->v.var.type, params);
    }

}

int getVarSymbolType(int declareType) {
    switch (declareType)
    {
    case DECL_INT:
        return SYMBOL_INT;
    default:
        exitWithErr("invalid var type", 1);
    }
}

void getParamsList(ASTNode* funcDeclNode, int** paramsList) {
    ASTNode* n = funcDeclNode;
    int len = 0;
    while (n != NULL) {
        if (n->left != NULL && n->left->op != NODE_GLUE) len++;
        if (n->right != NULL) len++;
        n = n->left;
    }
    int* list = (int*)malloc(sizeof(int) * len);
    n = funcDeclNode;
    int i = len - 1;
    while (n != NULL) {
        if (n->right != NULL) {
            list[i] = n->right->v.var.type;
            i--;
        }
        if (n->left != NULL && n->left->op != NODE_GLUE) {
            list[i] = n->right->v.var.type;
            i--;
        }
        n = n->left;
    }
    *paramsList = list;
}