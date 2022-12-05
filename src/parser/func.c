/*
 * @Author: yinn
 * @Date: 2022-12-04 23:49:40
 * @LastEditTime: 2022-12-05 21:33:42
 * @Description:
 */

#include "parser.h"
#include "utils.h"
#include "lexer.h"

 // <func-declaration> ::= <type-specifier> ID(<params>) <compound-stmt> 

 // <type-specifier> ::= int 
 //                    | void

 // <params> ::= <params-list>
 //            | void  

 // <param-list> ::= <param> <param-list-tail>

 // <param-list-tail> ::= ,<param> <param-list-tail>
 //                     | empty

 // <param> ::= <non-void-type-specifier> ID

ASTNode* funcDeclaration(Token** t) {
    Token* p = (*t);
    if (p == NULL) return NULL;

    int type;
    char* identity;
    ASTNode* paramsNode, * compoundNode;
    if ((type = typeSpec(&p)) != -1 &&
        p != NULL && p->token == TOKEN_FUNC &&
        p->next != NULL && p->next->token == TOKEN_LP)
    {
        identity = p->wordVal;
        p = p->next->next;
        if ((paramsNode = params(&p)) != NULL &&
            p != NULL && p->token == TOKEN_RP &&
            (p = p->next, (compoundNode = compoundStmt(&p)) != NULL))
        {
            ASTNode* funcDeclNode = createEmptyNode();
            funcDeclNode->op = NODE_FUNC_DECLARE;
            funcDeclNode->left = (paramsNode->op == NODE_EMPTY) ? NULL : paramsNode;
            funcDeclNode->right = compoundNode;
            funcDeclNode->v.var.id = identity;
            funcDeclNode->v.var.type = type;
            (*t) = p;
            return funcDeclNode;
        }
    }
    return NULL;
}

int typeSpec(Token** t) {
    Token* p = (*t);
    if (p == NULL) return -1;

    switch (p->token)
    {
    case TOKEN_INT:
        *t = p->next;
        return DECL_INT;
    case TOKEN_VOID:
        *t = p->next;
        return DECL_VOID;
    default:
        return -1;
    }
}

ASTNode* params(Token** t) {
    Token* p = (*t);
    if (p == NULL) return NULL;

    ASTNode* n;
    if ((n = paramList(t)) != NULL) {
        return n;
    }
    else if (p->token == TOKEN_VOID) {
        *t = p->next;
        return createEmptyNode();
    }
    return NULL;
}

ASTNode* paramList(Token** t) {
    ASTNode* n;
    if ((n = param(t)) != NULL) {
        ASTNode* subRoot = n;
        while ((n = paramListTail(t)) != NULL) {
            ASTNode* glueNode = createGlueNode();
            glueNode->left = subRoot;
            glueNode->right = n;
            subRoot = glueNode;
        }
        return subRoot;
    }
    return NULL;
}

ASTNode* paramListTail(Token** t) {
    Token* p = (*t);
    if (p == NULL) return NULL;

    ASTNode* n;
    if (p->token == TOKEN_COMMA &&
        (p = p->next, (n = param(&p)) != NULL)) {
        *t = p;
        return n;
    }
    return NULL;
}

ASTNode* param(Token** t) {
    Token* p = (*t);
    if (p == NULL) return NULL;

    int type;
    if ((type = nonVoidTypeSpec(&p)) != -1 &&
        p != NULL && p->token == TOKEN_VAR) {
        ASTNode* declareNode = createEmptyNode();
        declareNode->op = NODE_VAR_DECLARE;
        declareNode->v.var.id = p->wordVal;
        declareNode->v.var.type = type;
        (*t) = p->next;
        return declareNode;
    }
    return NULL;
}
