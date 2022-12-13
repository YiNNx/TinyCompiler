/*
 * @Author: yinn
 * @Date: 2022-12-07 20:04:45
 * @LastEditTime: 2022-12-08 20:54:05
 * @Description:
 */

#include"ast.h"

extern bool dumpSym;

void checker(ASTNode* ast, bool dump);

void checkNode(ASTNode* node);

int getVarSymbolType(int declareType);

int getParamsList(ASTNode* funcDeclNode, int** paramsList);


void printGlobal();

void printPopScope();

void printPushScope();

void printVarSymbol(char* id);

void printFuncSymbol(char* id, int returnType, int len, int* params);