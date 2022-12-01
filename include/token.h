/*
 * @Author: yinn
 * @Date: 2022-12-01 09:49:59
 * @LastEditTime: 2022-12-01 18:50:40
 * @Description: Statemant for struct Token & Enum for Token types
 */

#pragma once

typedef struct Token {
	int token;
	int intVal;
	char* wordVal;
} Token;

enum TokenType {
	// keywords
	INT,
	VOID,
	IF,
	ELSE,
	WHILE,
	RETURN,

	// white operator
	WHITE,

	//operators
	PLUS,
	MINUS,
	STAR,
	DIV,
	ASSIGN,

	GREATER, // >
	LESS, // <
	NOT_EQL, // !=
	EQL, // ==
	GREATER_OR_EQL, // >=
	LESS_OR_EQL, // <=

	// others
	DIGIT_INT,
	VAR,
	FUNC,

	COMMA,
	SEMI,
	LP, // (
	RP, // )
	LC, // {
	RC, // }
	COMMENT, // /* comment */

	// functions
	MAIN,
	INPUT,
	OUTPUT,
};

void printToken(Token* t);
