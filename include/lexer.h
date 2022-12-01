/*
 * @Author: yinn
 * @Date: 2022-12-01 16:00:18
 * @LastEditTime: 2022-12-01 18:13:03
 * @Description: Header file for lexer
 */

#pragma once

#include "token.h"

 /* lexer functions */

void lexer(char* codeStr, Token* tokens, int* len);

Token* evalue(char c);

/* helper functions */

int compareWithKeywords(char* word, int* token);

int getDigitInt(char c);

void getWord(char c, char* word);

/* str functions */

void initStr(char* s);

char check();

char next();

char skipWhite();

void back();