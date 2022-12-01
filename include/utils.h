/*
 * @Author: yinn
 * @Date: 2022-12-01 09:13:39
 * @LastEditTime: 2022-12-01 18:56:14
 * @Description: Header file for utils
 */

#pragma once

#include "config.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

char* readFile(char* path);

int endsWith(const char* str, const char* suffix);

void exitWithErr(char* msg, int errCode);

int isWhite(char c);

int isUnderline(char c);

int charToInt(char c);
