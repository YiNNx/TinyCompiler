/*
 * @Author: yinn
 * @Date: 2022-12-01 16:00:18
 * @LastEditTime: 2022-12-01 16:29:43
 * @Description:
 */

#pragma once

#include "token.h"

void lexer(char* content);

Token* evalue(char c);

int getDigitInt(char c);

void getWord(char c,char* word);