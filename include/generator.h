/*
 * @Author: yinn
 * @Date: 2022-12-07 14:24:17
 * @LastEditTime: 2022-12-07 15:57:32
 * @Description:
 */

#pragma once
#include "stdio.h"
#include"ast.h"

void generator(ASTNode* ast, FILE* outfile);
