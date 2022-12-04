/*
 * @Author: yinn
 * @Date: 2022-12-02 15:46:36
 * @LastEditTime: 2022-12-04 11:51:09
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