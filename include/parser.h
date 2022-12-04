/*
 * @Author: yinn
 * @Date: 2022-12-02 15:46:36
 * @LastEditTime: 2022-12-04 15:14:36
 * @Description:
 */

#pragma once

#include "token.h"
#include "ast.h"
#include"utils.h"

ASTNode* expr(Token** t);

ASTNode* exprTail(Token** t);

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