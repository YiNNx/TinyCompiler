
/*
 * @Author: yinn
 * @Date: 2022-12-01 09:49:59
 * @LastEditTime: 2022-12-05 15:33:39
 * @Description: Statemant for struct Token & Enum for Token types
 */

#pragma once

typedef struct Token {
	int token;
	int intVal;
	char* wordVal;
	struct Token* next;
} Token;

enum TokenType {
	// keywords
	TOKEN_INT,
	TOKEN_VOID,
	TOKEN_IF,
	TOKEN_ELSE,
	TOKEN_WHILE,
	TOKEN_RETURN,

	// white operator
	TOKEN_WHITE,

	//operators
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_STAR,
	TOKEN_DIV,
	TOKEN_ASSIGN,

	TOKEN_GREATER, // >
	TOKEN_LESS, // <
	TOKEN_NOT_EQL, // !=
	TOKEN_EQL, // ==
	TOKEN_GREATER_OR_EQL, // >=
	TOKEN_LESS_OR_EQL, // <=

	// others
	TOKEN_DIGIT_INT,
	TOKEN_VAR,
	TOKEN_FUNC,

	TOKEN_COMMA,
	TOKEN_SEMI,
	TOKEN_LP, // (
	TOKEN_RP, // )
	TOKEN_LC, // {
	TOKEN_RC, // }
	TOKEN_COMMENT, // /* comment */

	// functions
	TOKEN_MAIN,
	TOKEN_INPUT,
	TOKEN_OUTPUT,
};

void printToken(Token* t);

void printTokenList(Token* head);
