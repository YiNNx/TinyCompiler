/*
 * @Author: yinn
 * @Date: 2022-12-01 10:00:30
 * @LastEditTime: 2022-12-04 21:56:49
 * @Description: Core parser functions
 */

#include "parser.h"
#include "utils.h"
#include "lexer.h"

 //  <expression> ::= <var> = <expression>
 //                 | <simple-expr>
 // 
 //  <var> ::= ID
 // 
 //  <simple-expr> ::= <add-expr> <simple-expr-tail>
 // 
 //  <simple-expr-tail> ::= <relop> <add-expr>
 //                       | empty   

 //  <relop> ::= >
 //            | <
 //            | >=
 //            | <=
 //            | ==
 //            | !=

ASTNode* expression(Token** t) {
    Token* p = (*t);
    if (p == NULL) return NULL;

    ASTNode* varNode, * expressionNode, * simpleExprNode;
    if ((varNode = var(&p)) != NULL &&
        p != NULL && p->token == TOKEN_ASSIGN &&
        (p = p->next, (expressionNode = expression(&p)) != NULL))
    {
        ASTNode* assignNode = createEmptyNode();
        assignNode->op = NODE_ASSIGN;
        assignNode->left = varNode;
        assignNode->right = expressionNode;
        *t = p;
        return assignNode;
    }
    else if (p = *t, (simpleExprNode = simpleExpr(&p)) != NULL) {
        *t = p;
        return simpleExprNode;
    }
    return NULL;
}

ASTNode* simpleExpr(Token** t) {
    Token* p = (*t);
    if (p == NULL) return NULL;

    ASTNode* n;
    if ((n = addExpr(&p)) != NULL) {
        ASTNode* rootNode = n;
        while ((n = simpleExprTail(&p)) != NULL) {
            n->left = rootNode;
            rootNode = n;
        }
        *t = p;
        return rootNode;
    }
    return NULL;
}

ASTNode* simpleExprTail(Token** t) {
    Token* p = (*t);
    if (p == NULL) return NULL;

    ASTNode* relopNode, * addExprNode;
    if ((relopNode = relop(&p)) != NULL && (addExprNode = addExpr(&p)) != NULL) {
        relopNode->right = addExprNode;
        *t = p;
        return relopNode;
    }
    return NULL;
}

ASTNode* relop(Token** t) {
    Token* p = (*t);
    if (p == NULL) return NULL;

    ASTNode* n = createEmptyNode();
    switch (p->token)
    {
    case TOKEN_GREATER:
        n->op = NODE_GREATER;
        break;
    case TOKEN_LESS:
        n->op = NODE_LESS;
        break;
    case TOKEN_GREATER_OR_EQL:
        n->op = NODE_GREATER_OR_EQL;
        break;
    case TOKEN_LESS_OR_EQL:
        n->op = NODE_LESS_OR_EQL;
        break;
    case TOKEN_EQL:
        n->op = NODE_EQL;
        break;
    case TOKEN_NOT_EQL:
        n->op = NODE_NOT_EQL;
        break;
    default:
        free(n);
        return NULL;
    }
    *t = p->next;
    return n;
}

//  <add-expr> ::= <term> <add-expr-tail>
// 
//  <add-expr-tail> ::= <addop> <term> <add-expr-tail>
//                    | <empty>
// 
//  <addop> ::= +
//            | -

//  <term> :: = <factor> <term-tail>
//  
//  <term-tail> ::= <mulop> <factor> <term-tail>
//                | <empty>
//  
//  <mulop> ::= *
//            | /

//  <factor> :: = (<add-expr>)
//             | Num
//             | <var>
//             | <call>

//  <var> ::= ID
// 
//  <call> ::= ID(<args>)

//  <args> ::= <arg-list>
//           | void
// 
//  <arg-list> ::= <expression> <arg-list-tail>
// 
//  <arg-list-tail> ::= ,<expression> <arg-list-tail>
//                   | empty

ASTNode* addExpr(Token** t) {
    ASTNode* termNode, * exprTailNode;
    if ((termNode = term(t)) != NULL) {
        ASTNode* subRoot = termNode;
        while ((exprTailNode = addExprTail(t)) != NULL) {
            exprTailNode->left = subRoot;
            subRoot = exprTailNode;
        }
        return subRoot;
    }
    return NULL;
}

ASTNode* addExprTail(Token** t) {
    Token* p = (*t);
    if (p == NULL) return NULL;

    ASTNode* addopNode, * termNode;
    if ((addopNode = addop(&p)) != NULL && (termNode = term(&p)) != NULL) {
        addopNode->right = termNode;
        *t = p;
        return addopNode;
    }
    return NULL;
}

ASTNode* addop(Token** t) {
    Token* p = (*t);
    if (p == NULL) return NULL;

    switch (p->token)
    {
    case TOKEN_PLUS:
        ASTNode* plusNode = createEmptyNode();
        plusNode->op = NODE_PLUS;
        *t = p->next;
        return plusNode;
    case TOKEN_MINUS:
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
    Token* p = (*t);
    if (p == NULL) return NULL;

    ASTNode* mulopNode, * factorNode;
    if ((mulopNode = mulop(&p)) != NULL && (factorNode = factor(&p)) != NULL) {
        mulopNode->right = factorNode;
        *t = p;
        return mulopNode;
    }
    return NULL;
}

ASTNode* mulop(Token** t) {
    Token* p = (*t);
    if (p == NULL) return NULL;

    switch (p->token)
    {
    case TOKEN_STAR:
        ASTNode* starNode = createEmptyNode();
        starNode->op = NODE_STAR;
        *t = p->next;
        return starNode;
    case TOKEN_DIV:
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
    if (p->token == TOKEN_LP) {
        p = p->next;
        if ((n = addExpr(&p)) != NULL && p != NULL && p->token == TOKEN_RP) {
            *t = p->next;
            return n;
        }
    }
    else if (p->token == TOKEN_DIGIT_INT) {
        n = createEmptyNode();
        n->op = NODE_DIGIT_INT;
        n->v.intvalue = p->intVal;
        *t = p->next;
        return  n;
    }
    else if ((n = call(t)) != NULL) {
        return n;
    }
    else if ((n = var(t)) != NULL) {
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
    if (p->token == TOKEN_FUNC && p->next != NULL && p->next->token == TOKEN_LP) {
        ASTNode* funcNode = createEmptyNode();
        funcNode->op = NODE_FUNC_CALL;
        funcNode->v.id = p->wordVal;
        p = p->next->next;
        if (p != NULL && p->token == TOKEN_RP) {
            (*t) = p->next;
            return funcNode;
        }
        if ((n = args(&p)) != NULL && p != NULL && p->token == TOKEN_RP) {
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
    if (p->token == TOKEN_VOID) {
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
    if (p->token == TOKEN_VOID) {
        ASTNode* n = createEmptyNode();
        *t = p->next;
        return n;
    }
    else if ((n = addExpr(&p)) != NULL) {
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
    if (p->token == TOKEN_COMMA) {
        p = p->next;
        if ((n = addExpr(&p)) != NULL) {
            (*t) = p;
            return n;
        }
    }
    return NULL;
}

ASTNode* var(Token** t) {
    Token* p = (*t);
    if (p == NULL) return NULL;

    if (p->token == TOKEN_VAR) {
        ASTNode* n = createEmptyNode();
        n->op = NODE_VAR;
        n->v.id = p->wordVal;
        *t = p->next;
        return n;
    }
    else {
        return NULL;
    }
}