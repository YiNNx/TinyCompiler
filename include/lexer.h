/*
 * @Author: yinn
 * @Date: 2022-12-01 16:00:18
 * @LastEditTime: 2022-12-03 14:21:01
 * @Description: Header file for lexer
 */

#pragma once

#include "token.h"
#include "utils.h"

 /* lexer functions */

void lexer(char* codeStr, Token* head);

Token* match(char c);

/* helper functions */

bool compareWithKeywords(char* word, int* token);

int getDigitInt(char c);

void getWord(char c, char* word);

/* str functions */

void initStr(char* s);

char check();

char next();

char skipWhite();

void back();