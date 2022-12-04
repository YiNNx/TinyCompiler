/*
 * @Author: yinn
 * @Date: 2022-12-02 16:29:59
 * @LastEditTime: 2022-12-04 22:16:50
 * @Description:
 */

#pragma once

#include "token.h"
#include"utils.h"

enum ASTNodeType {
    NODE_INT_NUM,
    NODE_IDENT,

    NODE_IF,    // l: condition, mid: if-body,r: else-body
    NODE_WHILE, // l: condition, r: body
    NODE_RETURN,// l: return content

    //op
    NODE_PLUS,
    NODE_MINUS,
    NODE_STAR,
    NODE_DIV,
    NODE_ASSIGN,

    // compare
    NODE_GREATER, // >
    NODE_LESS, // <
    NODE_NOT_EQL, // !=
    NODE_EQL, // ==
    NODE_GREATER_OR_EQL, // >=
    NODE_LESS_OR_EQL, // <=

    // others
    NODE_FUNCTION,
    NODE_FUNCCALL,

    NODE_GLUE,
    NODE_EMPTY,
};

typedef struct ASTNode {
    int op;                       // "Operation" to be performed on this tree
    struct ASTNode* left;                // Left, middle and right child trees
    struct ASTNode* mid;
    struct ASTNode* right;
    union {
        int intvalue;               // For NODE_INTLIT, the integer value
        char* id;                     // For NODE_IDENT, the symbol slot number
    } v;
}ASTNode;

void makeTree(ASTNode* root, ASTNode* l, ASTNode* mid, ASTNode* r);

void printASTree(const ASTNode* root);

ASTNode* createEmptyNode();

ASTNode* createGlueNode();

void printNode(const ASTNode* n);

void printGlueTree(const char* l, const char* r, const ASTNode* node);

void printSubTree(const char* prefix, const ASTNode* node, bool isLeft);