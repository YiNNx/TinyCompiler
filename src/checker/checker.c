/*
 * @Author: yinn
 * @Date: 2022-12-03 16:08:34
 * @LastEditTime: 2022-12-13 22:08:55
 * @Description: Symbol Table
 */
#include"checker.h"
#include "table.h"
#include"utils.h"

 // TODO: 
 // 1. 赋值号两边的表达式类型不匹配。
 // 2. 赋值号左边出现一个只有右值的表达式。
 // 3. return语句的返回类型与函数定义的返回类型不匹配。
 // 4. 函数调用时实参与形参的数目或类型不匹配。

bool dumpSym = false;

void checker(ASTNode* ast, bool dump) {
    dumpSym = dump;
    initTable();
    addInternalFuction();
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
        if (lookupSymbolAtCurrentScope(node->v.var.id) != NULL) {
            char err[30];
            sprintf(err, "\033[31mERROR: duplicated definition of identity %s\033[0m\n", node->v.var.id);
            exitWithErr(err, 1);
        }
        insertSymbol(node->v.var.id, getVarSymbolType(node->v.var.type));
    }
    else if (node->op == NODE_FUNC_DECLARE) {
        if (lookupSymbolAtCurrentScope(node->v.var.id) != NULL) {
            char err[30];
            sprintf(err, "\033[31mERROR: duplicated definition of identity %s\033[0m\n", node->v.var.id);
            exitWithErr(err, 1);
        }
        int* params;
        int len = getParamsList(node, &params);
        insertFuncSymbol(node->v.var.id, SYMBOL_FUNC, node->v.var.type, params, len);
    }
    else if (node->op == NODE_FUNC_CALL) {
        if (lookupFuncSymbol(node->v.var.id) == NULL) {
            char err[30];
            sprintf(err, "\033[31mERROR: function '%s' undeclared\033[0m\n", node->v.var.id);
            exitWithErr(err, 1);
        }
    }
    else if (node->op == NODE_VAR) {
        Symbol* s;
        if ((s = lookupSymbol(node->v.var.id)) == NULL) {
            char err[30];
            sprintf(err, "\033[31mERROR: variable '%s' undeclared\033[0m\n", node->v.var.id);
            exitWithErr(err, 1);
        }
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

int getParamsList(ASTNode* funcDeclNode, int** paramsList) {
    ASTNode* n = funcDeclNode->left;
    int len = 0;
    if (n != NULL) {
        len++;
    }
    while (n != NULL) {
        if (n->left != NULL && n->left->op != NODE_GLUE) len++;
        if (n->right != NULL) len++;
        n = n->left;
    }
    int* list = (int*)malloc(sizeof(int) * len);
    n = funcDeclNode->left;
    int i = len - 1;
    if (n != NULL && n->op != NODE_GLUE) {
        list[i] = n->v.var.type;
        i--;
    }
    while (n != NULL) {
        if (n->right != NULL) {
            list[i] = n->right->v.var.type;
            i--;
        }
        if (n->left != NULL && n->left->op != NODE_GLUE) {
            list[i] = n->left->v.var.type;
            i--;
        }
        n = n->left;
    }
    *paramsList = list;
    return len;
}