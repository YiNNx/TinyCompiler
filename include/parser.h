/*
 * @Author: yinn
 * @Date: 2022-12-02 15:46:36
 * @LastEditTime: 2022-12-03 19:15:23
 * @Description:
 */

#pragma once

#include "token.h"
#include "ast.h"
#include"utils.h"

bool expr(Token** t, ASTNode** n);

bool exprTail(Token** t, ASTNode** n);

bool addop(Token** t, ASTNode** n);

bool term(Token** t, ASTNode** n);

bool termTail(Token** t, ASTNode** n);

bool mulop(Token** t, ASTNode** n);

bool factor(Token** t, ASTNode** n);

void parser(Token* tokenList);