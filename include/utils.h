/*
 * @Author: yinn
 * @Date: 2022-12-01 09:13:39
 * @LastEditTime: 2022-12-01 16:41:37
 * @Description:
 */

#pragma once

char* readFile(char* path);

int endsWith(const char* str, const char* suffix);

void exitWithMessage(char* msg, int errCode);

int isWhite(char c);

int isUnderline(char c);

int charToInt(char c);
