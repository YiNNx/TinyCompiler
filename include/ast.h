/*
 * @Author: yinn
 * @Date: 2022-12-02 16:29:59
 * @LastEditTime: 2022-12-05 21:13:01
 * @Description:
 */

#pragma once

#include "token.h"
#include"utils.h"

enum ASTNodeType {
    NODE_DIGIT_INT,
    NODE_VAR,

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
    NODE_VAR_DECLARE, // id type
    NODE_FUNC_DECLARE, // id returnType l: params 
    NODE_FUNC_CALL,
    NODE_COMPOUND,

    NODE_GLUE,
    NODE_EMPTY,
};

enum declarationType {
    DECL_INT,
    DECL_VOID,
};

typedef struct ASTNode {
    int op;                           // "Operation" to be performed on this tree
    struct ASTNode* left;             // Left, middle and right child trees
    struct ASTNode* mid;
    struct ASTNode* right;
    union {
        int intvalue;                 // For NODE_INTLIT, the integer value
        char* id;                     // For NODE_VAR, the identity name
        struct {                      // For NODE_VAR_DECL, the var name & type
            char* id;                 // For NODE_FUNC_DECL, the func name & return type
            int type;
        } var;
    } v;
}ASTNode;

void makeTree(ASTNode* root, ASTNode* l, ASTNode* mid, ASTNode* r);

void printASTree(const ASTNode* root);

ASTNode* createEmptyNode();

ASTNode* createGlueNode();

void printNode(const ASTNode* n);

void printSubTree(const char* prefix, const ASTNode* node, bool isLeft, const ASTNode* parent);