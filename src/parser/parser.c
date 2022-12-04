/*
 * @Author: yinn
 * @Date: 2022-12-01 10:00:30
 * @LastEditTime: 2022-12-04 11:50:03
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

ASTNode* expr(Token** t) {
    ASTNode* termNode, * exprTailNode;
    if ((termNode = term(t)) != NULL) {
        ASTNode* subRoot = termNode;
        while ((exprTailNode = exprTail(t)) != NULL) {
            exprTailNode->left = subRoot;
            subRoot = exprTailNode;
        }
        return subRoot;
    }
    return NULL;
}

ASTNode* exprTail(Token** t) {
    ASTNode* addopNode, * termNode;
    if ((addopNode = addop(t)) != NULL && (termNode = term(t)) != NULL) {
        addopNode->right = termNode;
        return addopNode;
    }
    return NULL;
}

ASTNode* addop(Token** t) {
    Token* p = (*t);
    if (p == NULL) return NULL;

    switch (p->token)
    {
    case PLUS:
        ASTNode* plusNode = getEmptyNode();
        plusNode->op = NODE_PLUS;
        *t = p->next;
        return plusNode;
    case MINUS:
        ASTNode* minusNode = getEmptyNode();
        minusNode->op = NODE_MINUS;
        *t = p->next;
        return minusNode;
    default:
        return NULL;
    }
}

ASTNode* term(Token** t) {
    ASTNode* factorNode;
    if ((factorNode = factor(t)) != NULL) {
        ASTNode* termTailNode;
        ASTNode* subRoot = factorNode;
        while ((termTailNode = termTail(t)) != NULL) {
            termTailNode->left = subRoot;
            subRoot = termTailNode;
        }
        return subRoot;
    }
    return NULL;
}

ASTNode* termTail(Token** t) {
    ASTNode* mulopNode, * factorNode;
    if ((mulopNode = mulop(t)) != NULL && (factorNode = factor(t)) != NULL) {
        mulopNode->right = factorNode;
        return mulopNode;
    }
    return NULL;
}

ASTNode* mulop(Token** t) {
    Token* p = (*t);
    if (p == NULL) return NULL;

    switch (p->token)
    {
    case STAR:
        ASTNode* starNode = getEmptyNode();
        starNode->op = NODE_STAR;
        *t = p->next;
        return starNode;
    case DIV:
        ASTNode* divNode = getEmptyNode();
        divNode->op = NODE_DIV;
        *t = p->next;
        return divNode;
    default:
        return false;
    }
}

// Determine if the tokens start from t can form a factor.
// If it can, return true and t points at the next token after the factor tokens,
// else, return false and t points at the origin t.
ASTNode* factor(Token** t) {
    Token* p = (*t);
    if (p == NULL) return NULL;

    if (p->token == LP) {
        p = p->next;
        ASTNode* exprNode;
        if ((exprNode = expr(&p)) != NULL && p->token == RP) {
            *t = p->next;
            return exprNode;
        }
    }
    else if (p->token == DIGIT_INT) {
        ASTNode* digitNode = getEmptyNode();
        digitNode->op = NODE_INT_NUM;
        digitNode->v.intvalue = p->intVal;
        *t = p->next;
        return  digitNode;
    }
    else {
        return false;
    }
}

ASTNode* parser(Token* tokenList) {
    return expr(&tokenList->next);
}


