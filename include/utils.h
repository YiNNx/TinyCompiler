/*
 * @Author: yinn
 * @Date: 2022-12-01 09:13:39
 * @LastEditTime: 2022-12-01 15:06:38
 * @Description:
 */

#pragma once

char* readFile(char* path);

int endsWith(const char* str, const char* suffix);

void exitWithMessage(char* msg, int errCode);

int isDigit(char c);

int isLetter(char c);

int isWhite(char c);

int isUnderline(char c);

int charToInt(char c);
