/*
 * @Author: yinn
 * @Date: 2022-12-01 10:00:30
 * @LastEditTime: 2022-12-03 23:24:54
 * @Description: Core parser functions
 */

#include "parser.h"
#include "utils.h"
#include "lexer.h"


 /* <expr> ::= <term> <expr_tail>
  *
  * <expr_tail> ::= <addop> <term> <expr_tail>
  *               | <empty>
  *
  * <addop> ::= +
  *           | -
  *
  * <term> ::= <factor> <term_tail>
  *
  * <term_tail> ::= <mulop> <factor> <term_tail>
  *               | <empty>
  *
  * <mulop> ::= *
  *           | /
  *
  * <factor> ::= ( <expr> )
  *            | Num
  */


  // ASTNode* getGlue() {
  //     ASTNode glue = {
  //         .op = NODE_GLUE,
  //     };
  //     return &glue;
  // }

bool expr(Token** t, ASTNode** n) {

    ASTNode* termNode, * exprTailNode;
    if (term(t, &termNode)) {
        ASTNode* subRoot = termNode;
        while (exprTail(t, &exprTailNode)) {
            exprTailNode->left = subRoot;
            subRoot = exprTailNode;
        }
        (*n) = subRoot;
        return true;
    }

    return false;
}

bool exprTail(Token** t, ASTNode** n) {
    ASTNode* addopNode, * termNode;
    if (addop(t, &addopNode) && term(t, &termNode)) {
        addopNode->right = termNode;
        (*n) = addopNode;
        return true;
    }
    return false;
}

bool addop(Token** t, ASTNode** n) {
    Token* p = (*t);
    switch (p->token)
    {
    case PLUS:
        ASTNode plusNode = {
            .op = NODE_PLUS,
            .left = NULL,
            .mid = NULL,
            .right = NULL,
        };
        *n = &plusNode;
        *t = p->next;
        return true;
    case MINUS:
        ASTNode minusNode = {
            .op = NODE_MINUS,
            .left = NULL,
            .mid = NULL,
            .right = NULL,
        };
        *n = &minusNode;
        *t = p->next;
        return true;
    default:
        return false;
    }
}

bool term(Token** t, ASTNode** n) {
    ASTNode* factorNode;
    if (factor(t, &factorNode)) {
        ASTNode* termTailNode;
        ASTNode* subRoot = factorNode;
        printf("-------%d------\n", subRoot->op);
        while (termTail(t, &termTailNode)) {
            termTailNode->left = subRoot;
            subRoot = termTailNode;
        }
        (*n) = subRoot;
        printf("=======%d=======\n", subRoot->op);
        
        return true;
    }
    return false;
}

bool termTail(Token** t, ASTNode** n) {
    ASTNode* mulopNode, * factorNode;
    if (mulop(t, &mulopNode) && factor(t, &factorNode)) {
        mulopNode->right = factorNode;
        (*n) = mulopNode;
        return true;
    }
    return false;
}

bool mulop(Token** t, ASTNode** n) {
    Token* p = (*t);
    switch (p->token)
    {
    case STAR:
        ASTNode starNode = {
            .op = NODE_STAR,
            .left = NULL,
            .mid = NULL,
            .right = NULL,
        };
        *n = &starNode;
        *t = p->next;
        return true;
    case DIV:
        ASTNode divNode = {
            .op = NODE_DIV,
            .left = NULL,
            .mid = NULL,
            .right = NULL,
        };
        *n = &divNode;
        *t = p->next;
        return true;
    default:
        return false;
    }
}

// Determine if the tokens start from t can form a factor.
// If it can, return true and t points at the next token after the factor tokens,
// else, return false and t points at the origin t.
bool factor(Token** t, ASTNode** n) {
    Token* p = (*t);
    if (p->token == LP) {
        if (expr(&p, n) && p->token == RP) {
            *t = p->next;
            return true;
        }
    }
    else if (p->token == DIGIT_INT) {
        ASTNode digitNode = {
            .op = DIGIT_INT,
            .v.intvalue = p->intVal,
            .left = NULL,
            .mid = NULL,
            .right = NULL,
        };
        *n = &digitNode;
        *t = p->next;
        return true;
    }
    else {
        return false;
    }
}

void parser(Token* tokenList) {
    ASTNode* root;
    expr(&tokenList->next, &root);
    // printASTree(root);
    return;
}


