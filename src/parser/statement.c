/*
 * @Author: yinn
 * @Date: 2022-12-04 18:56:40
 * @LastEditTime: 2022-12-13 21:35:29
 * @Description:
 */

#include "parser.h"
#include "utils.h"
#include "lexer.h"

 // <statement-list> ::= <statement-list> <statement> 
 //                    | empty  

 // <statement> ::= <expression-stmt>
 //               | <compound-stmt>
 //               | <selection-stmt>
 //               | <iteration-stmt>
 //               | <return-stmt>
 //               | <var-declaration>

 // <expression-stmt> ::= <expression>;
 //                     |;  

 // <compound-stmt> ::= { <statement-list> }

 // <selection-stmt> ::= if (<expression>) <statement>
 //                    | if (<expression>) <statement> else <statement>  

 // <iteration-stmt> ::= while (<expression>) <statement>

 // <return-stmt> ::= return;
 //                 | return <expression>;  

 // <var-declaration> ::= <non-void-type-specifier> ID; 

 // <non-void-type-specifier> ::= int

ASTNode* statementList(Token** t) {
    bool isEmpty = true;
    ASTNode* rootNode = NULL, * n;
    while ((n = statement(t)) != NULL) {
        isEmpty = false;
        ASTNode* glueNode = createGlueNode();
        glueNode->left = rootNode;
        glueNode->right = n;
        rootNode = glueNode;
        printASTree(rootNode);
    }
    return isEmpty ? createEmptyNode() : rootNode;
}

ASTNode* statement(Token** t) {
    ASTNode* n;
    if ((n = expressionStmt(t)) != NULL) {
        return n;
    }
    else if ((n = compoundStmt(t)) != NULL) {
        return n;
    }
    else if ((n = selectionStmt(t)) != NULL) {
        return n;
    }
    else if ((n = iterationStmt(t)) != NULL) {
        return n;
    }
    else if ((n = returnStmt(t)) != NULL) {
        return n;
    }
    else if ((n = varDeclaration(t)) != NULL) {
        return n;
    }
    return NULL;
}

ASTNode* expressionStmt(Token** t) {
    Token* p = (*t);
    if (p == NULL) return NULL;

    ASTNode* n;
    if (p->token == TOKEN_SEMI) {
        *t = p->next;
        return createEmptyNode();
    }
    else if ((n = expression(&p)) != NULL && p != NULL && p->token == TOKEN_SEMI) {
        *t = p->next;
        return n;
    }
}

ASTNode* selectionStmt(Token** t) {
    Token* p = (*t);
    if (p == NULL) return NULL;

    ASTNode* conditionNode, * ifBodyNode, * elseBodyNode;
    if (p->token == TOKEN_IF &&
        (p = p->next, p != NULL) && (p->token == TOKEN_LP) &&
        (p = p->next, (conditionNode = expression(&p)) != NULL) &&
        p != NULL && p->token == TOKEN_RP &&
        (p = p->next, (ifBodyNode = statement(&p)) != NULL))
    {
        ASTNode* ifNode = createEmptyNode();
        ifNode->op = NODE_IF;
        ifNode->left = conditionNode;
        ifNode->mid = ifBodyNode;
        if (p != NULL && p->token == TOKEN_ELSE &&
            (p = p->next, (elseBodyNode = statement(&p)) != NULL))
        {
            ifNode->right = elseBodyNode;
        }
        *t = p;
        return ifNode;
    }
    return NULL;
}

ASTNode* iterationStmt(Token** t) {
    Token* p = (*t);
    if (p == NULL) return NULL;

    ASTNode* conditionNode, * whileBodyNode;
    if (p->token == TOKEN_WHILE &&
        (p = p->next, p != NULL) && (p->token == TOKEN_LP) &&
        (p = p->next, (conditionNode = expression(&p)) != NULL) &&
        p != NULL && p->token == TOKEN_RP &&
        (p = p->next, (whileBodyNode = statement(&p)) != NULL))
    {
        ASTNode* whileNode = createEmptyNode();
        whileNode->op = NODE_WHILE;
        whileNode->left = conditionNode;
        whileNode->mid = whileBodyNode;
        *t = p;
        return whileNode;
    }
    return NULL;
}

ASTNode* returnStmt(Token** t) {
    Token* p = (*t);
    if (p == NULL) return NULL;

    ASTNode* n;
    if (p->token == TOKEN_RETURN) {
        p = p->next;
        n = expression(&p);
        if (p != NULL && p->token == TOKEN_SEMI) {
            ASTNode* returnNode = createEmptyNode();
            returnNode->op = NODE_RETURN;
            returnNode->left = n;
            *t = p->next;
            return returnNode;
        }
        else {
            return NULL;
        }
    }
    return NULL;
}


ASTNode* compoundStmt(Token** t) {
    Token* p = (*t);
    if (p == NULL) return NULL;

    ASTNode* n;
    if (p->token == TOKEN_LC &&
        (p = p->next, (n = statementList(&p)) != NULL) &&
        p != NULL && p->token == TOKEN_RC)
    {
        ASTNode* compoundNode = createEmptyNode();
        compoundNode->op = NODE_COMPOUND;
        compoundNode->left = n->op == NODE_EMPTY ? NULL : n;
        *t = p->next;
        return compoundNode;
    }
    return NULL;
}

ASTNode* varDeclaration(Token** t) {
    Token* p = (*t);
    if (p == NULL) return NULL;

    int type;
    if ((type = nonVoidTypeSpec(&p)) != -1 &&
        p != NULL && p->token == TOKEN_VAR) {
        ASTNode* declareNode = createEmptyNode();
        declareNode->op = NODE_VAR_DECLARE;
        declareNode->v.var.id = p->wordVal;
        declareNode->v.var.type = type;
        p = p->next;

        ASTNode* n, * subRoot;
        subRoot = declareNode;
        while ((n = varDeclTail(&p, type)) != NULL) {
            ASTNode* glueNode = createGlueNode();
            glueNode->left = subRoot;
            glueNode->right = n;
            subRoot = glueNode;
        }
        if (p != NULL && p->token == TOKEN_SEMI) {
            *t = p->next;
            return subRoot;
        }
    }
    return NULL;
}

ASTNode* varDeclTail(Token** t, int type) {
    Token* p = (*t);
    if (p == NULL) return NULL;

    ASTNode* n;
    if (p->token == TOKEN_COMMA && p->next != NULL && p->next->token == TOKEN_VAR) {
        ASTNode* declareNode = createEmptyNode();
        declareNode->op = NODE_VAR_DECLARE;
        declareNode->v.var.id = p->next->wordVal;
        declareNode->v.var.type = type;
        (*t) = p->next->next;
        return declareNode;
    }
    return NULL;
}


int nonVoidTypeSpec(Token** t) {
    Token* p = (*t);
    if (p == NULL) return -1;

    if (p->token == TOKEN_INT) {
        *t = p->next;
        return TOKEN_INT;
    }
    return -1;
}