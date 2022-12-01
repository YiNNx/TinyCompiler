/*
 * @Author: yinn
 * @Date: 2022-12-01 09:49:59
 * @LastEditTime: 2022-12-01 14:35:40
 * @Description:
 */

#pragma once

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
  VAR_NAME,
  FUNC_NAME,

  SEMI,
  LP, // (
  RP, // )
  LC, // {
  RC, // }
  LNOTE, // /*
  RNOTE, // */

  // functions
  MAIN,
  INPUT,
  OUTPUT,
};

typedef struct Token {
  int token;
  int intVal;
  char* wordVal;
} Token;

void lexer(char* content);