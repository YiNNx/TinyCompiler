/*
 * @Author: yinn
 * @Date: 2022-12-04 18:56:40
 * @LastEditTime: 2022-12-04 22:01:51
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

  // <expression-stmt> ::= <expression>;
  //                     |;  

  // <compound-stmt> ::= { <local-declarations> <statement-list> }

  // <selection-stmt> ::= if (<expression>) <statement>
  //                    | if (<expression>) <statement> else <statement>  

  // <iteration-stmt> ::= while (<expression>) <statement>

  // <return-stmt> ::= return;
  //                 | return <expression>;  

ASTNode* statementList(Token** t) {
    ASTNode* rootNode = NULL, * n;
    while ((n = statement(t)) != NULL) {
        ASTNode* glueNode = createGlueNode();
        glueNode->left = rootNode;
        glueNode->right = n;
        rootNode = glueNode;
    }
    return rootNode;
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
    return NULL;
}

ASTNode* expressionStmt(Token** t) {
    Token* p = (*t);
    if (p == NULL) return NULL;

    ASTNode* n;
    if (p->token == SEMI) {
        *t = p->next;
        return createEmptyNode();
    }
    else if ((n = expression(&p)) != NULL && p != NULL && p->token == SEMI) {
        *t = p->next;
        return n;
    }
}

ASTNode* compoundStmt(Token** t) {
    return NULL;
}

ASTNode* selectionStmt(Token** t) {
    Token* p = (*t);
    if (p == NULL) return NULL;

    ASTNode* conditionNode, * ifBodyNode, * elseBodyNode;
    if (p->token == IF &&
        (p = p->next, p != NULL) && (p->token == LP) &&
        (p = p->next, (conditionNode = expression(&p)) != NULL) &&
        p != NULL && p->token == RP &&
        (p = p->next, (ifBodyNode = statement(&p)) != NULL))
    {
        ASTNode* ifNode = createEmptyNode();
        ifNode->op = NODE_IF;
        ifNode->left = conditionNode;
        ifNode->mid = ifBodyNode;
        if (p != NULL && p->token == ELSE &&
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
    if (p->token == WHILE &&
        (p = p->next, p != NULL) && (p->token == LP) &&
        (p = p->next, (conditionNode = expression(&p)) != NULL) &&
        p != NULL && p->token == RP &&
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
    if (p->token == RETURN) {
        p = p->next;
        n = expression(&p);
        if (p != NULL && p->token == SEMI) {
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
