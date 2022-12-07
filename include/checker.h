/*
 * @Author: yinn
 * @Date: 2022-12-07 20:04:45
 * @LastEditTime: 2022-12-07 23:26:07
 * @Description:
 */

#include"ast.h"

void checker(ASTNode* ast);

void checkNode(ASTNode* node);

int getVarSymbolType(int declareType);

void getParamsList(ASTNode* funcDeclNode, int** paramsList);

void checkNode(ASTNode* node);

int getVarSymbolType(int declareType);

void getParamsList(ASTNode* funcDeclNode, int** paramsList);