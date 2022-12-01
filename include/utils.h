#pragma once

char* readFile(char* path, int* length);

int endsWith(const char* str, const char* suffix);

void exitWithMessage(char* msg, int errCode);