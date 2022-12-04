/*
 * @Author: yinn
 * @Date: 2022-12-02 16:15:52
 * @LastEditTime: 2022-12-04 15:44:34
 * @Description: AST
 */

#include "ast.h"
#include "utils.h"

char* nodeTypes[] = {
    "int",
    "IDENT",
    "IF",
    "WHILE",
    "RETURN",
    "+",
    "-",
    "*",
    "/",
    "=",
    "GREATER",
    "LESS",
    "NOT_EQL",
    "EQL",
    "GREATER_OR_EQL",
    "LESS_OR_EQL",
    "FUNCTION",
    "CALL",
    "GLUE",
    "EMPTY",
};


void makeTree(ASTNode* root, ASTNode* l, ASTNode* mid, ASTNode* r) {
    root->left = l;
    root->mid = mid;
    root->right = r;
}

void printSubTree(const char* prefix, const ASTNode* node, bool isLeft)
{
    if (node != NULL)
    {
        printf(prefix);
        printf(isLeft ? "├── " : "└── ");

        // print the value of the node
        printNode(node);

        char l[100];
        sprintf(l, "%s%s", prefix, (isLeft ? "│   " : "    "));
        char r[100];
        sprintf(r, "%s%s", prefix, (isLeft ? "│   " : "    "));

        // enter the next tree level - left and right branch
        printSubTree(l, node->left, true);
        printSubTree(r, node->right, false);
    }
}

void printNode(const ASTNode* n) {
    if (n->op == NODE_INT_NUM) {
        printf("%s: %d\n", nodeTypes[n->op], n->v.intvalue);
    }
    else if (n->op == NODE_FUNCCALL) {
        printf("%s: %s\n", nodeTypes[n->op], n->v.id);
    }
    else {
        printf("%s\n", nodeTypes[n->op]);
    }
}

void printASTree(const ASTNode* root)
{
    printSubTree("", root, false);
}

ASTNode* createEmptyNode() {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->left = NULL;
    node->mid = NULL;
    node->right = NULL;
    node->op = NODE_EMPTY;
}

ASTNode* createGlueNode() {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->left = NULL;
    node->mid = NULL;
    node->right = NULL;
    node->op = NODE_GLUE;
}