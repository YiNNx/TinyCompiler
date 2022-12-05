/*
 * @Author: yinn
 * @Date: 2022-12-02 16:15:52
 * @LastEditTime: 2022-12-05 21:49:32
 * @Description: AST
 */

#include "ast.h"
#include "utils.h"

char* nodeTypes[] = {
    "num",
    "var",
    "if",
    "while",
    "return",
    "+",
    "-",
    "*",
    "/",
    "=",
    ">",
    "<",
    "!=",
    "==",
    ">=",
    "<=",
    "var",
    "func",
    "CALL",
    "{}",
    "GLUE",
    "EMPTY",
};


char* varTypes[] = {
    "int",
    "void",
};

bool isRoot = true;

void makeTree(ASTNode* root, ASTNode* l, ASTNode* mid, ASTNode* r) {
    root->left = l;
    root->mid = mid;
    root->right = r;
}

void printSubTree(const char* prefix, const ASTNode* node, bool isLeft, const ASTNode* parent)
{
    if (node != NULL)
    {
        char p[100];

        if (node->op != NODE_GLUE) {
            if (!isRoot) {
                printf(prefix);
                printf("└── ");
            }
            else {
                isRoot = false;
            }
            // print the value of the node
            printNode(node);

            sprintf(p, "%s%s", prefix, (isLeft ? "│   " : "    "));
        }
        else {
            sprintf(p, "%s", prefix);
        }

        // enter the next tree level - left and right branch
        printSubTree(p, node->left, true, node);
        if (node->right != NULL)printSubTree(p, node->mid, true, node);
        else printSubTree(p, node->mid, false, node);
        if (node->op == NODE_GLUE && parent != NULL && parent->op == NODE_GLUE)printSubTree(p, node->right, true, node);
        else printSubTree(p, node->right, false, node);
    }
}

void printNode(const ASTNode* n) {
    if (n->op == NODE_DIGIT_INT) {
        printf("%d\n", n->v.intvalue);
    }
    else if (n->op == NODE_FUNC_DECLARE) {
        printf("%s: %s, ret %s \n",  nodeTypes[n->op], n->v.var.id,varTypes[n->v.var.type]);
    }
    else if (n->op == NODE_VAR_DECLARE) {
        printf("%s %s: %s\n", varTypes[n->v.var.type], nodeTypes[n->op], n->v.var.id);
    }
    else if (n->op == NODE_FUNC_CALL) {
        printf("%s: %s\n", nodeTypes[n->op], n->v.id);
    }
    else if (n->op == NODE_VAR) {
        printf("%s\n", n->v.id);
    }
    else {
        printf("%s\n", nodeTypes[n->op]);
    }
}

void printASTree(const ASTNode* root)
{
    printSubTree("", root, false, NULL);
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

