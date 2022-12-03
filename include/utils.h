/*
 * @Author: yinn
 * @Date: 2022-12-01 09:13:39
 * @LastEditTime: 2022-12-03 12:22:30
 * @Description: Header file for utils
 */

#pragma once

#include "config.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"
#include "stdbool.h"

char* readFile(char* path);

bool endsWith(const char* str, const char* suffix);

void exitWithErr(char* msg, int errCode);

bool isWhite(char c);

bool isUnderline(char c);

int charToInt(char c);
