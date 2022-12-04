/*
 * @Author: yinn
 * @Date: 2022-12-01 10:00:30
 * @LastEditTime: 2022-12-04 15:41:20
 * @Description: Core parser functions
 */

#include "parser.h"
#include "utils.h"
#include "lexer.h"

 /* <expr> ::= <term> <expr-tail>
  *
  * <expr-tail> ::= <addop> <term> <expr-tail>
  *               | <empty>
  *
  * <addop> ::= +
  *           | -
  *
  * <term> ::= <factor> <term-tail>
  *
  * <term-tail> ::= <mulop> <factor> <term-tail>
  *               | <empty>
  *
  * <mulop> ::= *
  *           | /
  *
  * <factor> ::= ( <expr> )
  *            | Num
  *            | <var>
  *            | <call>
  *
  * <var> ::= ID
  *
  * <call> ::= ID(<args>)
  *
  * <args> ::= <arg-list>
  *          | void
  *
  * <arg-list> ::= <expression> <arg-list-tail>
  *
  * <arg-list-tail> ::= ,<expression> <arg-list-tail>
  *                   | empty
  *
  *
  */

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
        ASTNode* plusNode = createEmptyNode();
        plusNode->op = NODE_PLUS;
        *t = p->next;
        return plusNode;
    case MINUS:
        ASTNode* minusNode = createEmptyNode();
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
        ASTNode* starNode = createEmptyNode();
        starNode->op = NODE_STAR;
        *t = p->next;
        return starNode;
    case DIV:
        ASTNode* divNode = createEmptyNode();
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

    ASTNode* n;
    if (p->token == LP) {
        p = p->next;
        if ((n = expr(&p)) != NULL && p->token == RP) {
            *t = p->next;
            return n;
        }
    }
    else if (p->token == DIGIT_INT) {
        n = createEmptyNode();
        n->op = NODE_INT_NUM;
        n->v.intvalue = p->intVal;
        *t = p->next;
        return  n;
    }
    else if ((n = var(t)) != NULL) {
        return n;
    }
    else if ((n = call(t)) != NULL) {
        return n;
    }
    else {
        return false;
    }
}

ASTNode* call(Token** t) {
    Token* p = (*t);
    if (p == NULL) return NULL;

    ASTNode* n;
    if (p->token == FUNC && p->next != NULL && p->next->token == LP) {
        ASTNode* funcNode = createEmptyNode();
        funcNode->op = NODE_FUNCCALL;
        funcNode->v.id = p->wordVal;
        p = p->next->next;
        if (p->token == RP) {
            (*t) = p->next;
            return funcNode;
        }
        if ((n = args(&p)) != NULL && p->token == RP) {
            funcNode->left = n->op == NODE_EMPTY ? NULL : n;
            (*t) = p->next;
            return funcNode;
        }
    }
    return NULL;
}

ASTNode* args(Token** t) {
    Token* p = (*t);
    if (p == NULL) return NULL;

    ASTNode* n;
    if (p->token == VOID) {
        n = createEmptyNode();
        *t = p->next;
        return n;
    }
    else if ((n = argList(t)) != NULL) {
        return n;
    }
    else {
        return NULL;
    }
}

ASTNode* argList(Token** t) {
    Token* p = (*t);
    if (p == NULL) return NULL;

    ASTNode* n;
    if (p->token == VOID) {
        ASTNode* n = createEmptyNode();
        *t = p->next;
        return n;
    }
    else if ((n = expr(&p)) != NULL) {
        ASTNode* rootNode = n;
        while ((n = argListTail(&p)) != NULL) {
            ASTNode* glue = createGlueNode();
            glue->left = rootNode;
            glue->right = n;
            rootNode = glue;
        }
        *t = p;
        return rootNode;
    }
    else {
        return NULL;
    }
}

ASTNode* argListTail(Token** t) {
    Token* p = (*t);
    if (p == NULL) return NULL;

    ASTNode* n;
    if (p->token == COMMA) {
        p = p->next;
        if ((n = expr(&p)) != NULL) {
            (*t) = p;
            return n;
        }
    }
    return NULL;
}

ASTNode* var(Token** t) {
    Token* p = (*t);
    if (p == NULL) return NULL;

    if (p->token == VAR) {
        ASTNode* n = createEmptyNode();
        n->op = NODE_IDENT;
        n->v.id = p->wordVal;
        *t = p->next;
        return n;
    }
    else {
        return NULL;
    }
}