/*
 * @Author: yinn
 * @Date: 2022-12-05 22:38:47
 * @LastEditTime: 2022-12-13 21:33:06
 * @Description:
 */

#include "parser.h"
#include "utils.h"
#include "lexer.h"

 // <program> ::= <declaration-list>

 // <declaration-list> ::= <declaration> <declaration-list-tail>
 // 
 // <declaration-list-tail> ::= <declaration> <declaration-list-tail>
 //                           | empty

 // <declaration> ::= <var-declaration> 
 //                 | <func-declaration>

ASTNode* program(Token** t) {
    return declarationList(t);
}

ASTNode* declarationList(Token** t) {
    Token* p = (*t);
    if (p == NULL) return NULL;

    ASTNode* n, * rootNode;
    if ((n = declaration(&p)) != NULL) {
        rootNode = n;
        printASTree(rootNode);
        while ((n = declaration(&p)) != NULL) {
            ASTNode* glueNode = createGlueNode();
            glueNode->left = rootNode;
            glueNode->right = n;
            rootNode = glueNode;
            printASTree(rootNode);
        }
        return rootNode;
    }
    return NULL;
}

ASTNode* declaration(Token** t) {
    Token* p = (*t);
    if (p == NULL) return NULL;

    ASTNode* n;
    if ((n = varDeclaration(&p)) != NULL) {
        *t = p;
        return n;
    }
    else if ((n = funcDeclaration(&p)) != NULL) {
        *t = p;
        return n;
    }
    return NULL;
}