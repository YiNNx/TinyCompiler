/*
 * @Author: yinn
 * @Date: 2022-12-02 16:15:52
 * @LastEditTime: 2022-12-03 19:40:48
 * @Description: AST
 */

#include "ast.h"
#include "utils.h"

char* nodeTypes[] = {
    "NODE_INT_NUM",
    "NODE_IDENT",
    "NODE_IF",
    "NODE_WHILE",
    "NODE_RETURN",
    "NODE_PLUS",
    "NODE_MINUS",
    "NODE_STAR",
    "NODE_DIV",
    "NODE_ASSIGN",
    "NODE_GREATER",
    "NODE_LESS",
    "NODE_NOT_EQL",
    "NODE_EQL",
    "NODE_GREATER_OR_EQL",
    "NODE_LESS_OR_EQL",
    "NODE_FUNCTION",
    "NODE_FUNCCALL",
    "NODE_GLUE",
    "NODE_EMPTY",
};


void makeTree(ASTNode* root, ASTNode* l, ASTNode* mid, ASTNode* r) {
    root->left = l;
    root->mid = mid;
    root->right = r;
}

void printNode(const char* prefix, const ASTNode* node, bool isLeft)
{
    if (node != NULL)
    {
        printf(prefix);
        printf(isLeft ? "├──" : "└──");

        // print the value of the node
        printf("%s\n", nodeTypes[node->op]);

        char l[100];
        sprintf(l, "%s%s", prefix, (isLeft ? "│   " : "    "));
        char r[100];
        sprintf(r, "%s%s", prefix, (isLeft ? "│   " : "    "));

        // enter the next tree level - left and right branch
        printNode(l, node->left, true);
        printNode(r, node->right, false);
    }
}

void printASTree(const ASTNode* root)
{
    printf("%s\n", nodeTypes[root->op]);
    
    // printNode("", root, false);
}