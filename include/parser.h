/*
 * @Author: yinn
 * @Date: 2022-12-02 15:46:36
 * @LastEditTime: 2022-12-04 21:33:34
 * @Description:
 */

#pragma once

#include "token.h"
#include "ast.h"
#include"utils.h"

ASTNode* expression(Token** t);

ASTNode* simpleExpr(Token** t);

ASTNode* simpleExprTail(Token** t);

ASTNode* relop(Token** t);

ASTNode* addExpr(Token** t);

ASTNode* addExprTail(Token** t);

ASTNode* addop(Token** t);

ASTNode* term(Token** t);

ASTNode* termTail(Token** t);

ASTNode* mulop(Token** t);

ASTNode* factor(Token** t);

ASTNode* parser(Token* tokenList);

ASTNode* call(Token** t);

ASTNode* args(Token** t);

ASTNode* argList(Token** t);

ASTNode* argListTail(Token** t);

ASTNode* var(Token** t);

ASTNode* statementList(Token** t);

ASTNode* statement(Token** t);

ASTNode* expressionStmt(Token** t);

ASTNode* compoundStmt(Token** t);

ASTNode* selectionStmt(Token** t);

ASTNode* iterationStmt(Token** t);

ASTNode* returnStmt(Token** t);