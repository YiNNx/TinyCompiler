/*
 * @Author: yinn
 * @Date: 2022-12-04 13:51:34
 * @LastEditTime: 2022-12-04 15:46:42
 * @Description:
 */

#include"parser.h"

ASTNode* parser(Token* tokenList) {
    return expr(&tokenList->next);
}

// <program> ::= <declaration-list>

// <declaration-list> ::= <declaration-list> <declaration> 
//                      | <declaration>

// <declaration> ::= <var-declaration> 
//                 | <func-declaration>

// <var-declaration> ::= <type-specifier> ID; 

// <type-specifier> ::= int 
//                    | void

// <func-declaration> ::= <type-specifier> ID(<params>) <compound-stmt> 

// <params> ::= <params-list>
//            | void  

// <param-list> ::= <param-list>,<param>
//                | <param>

// <param> ::= <type-specifier> ID

// <compound-stmt> ::= { <local-declarations> <statement-list> }

// <local-declarations> ::= <local-declarations> <var-declaration>
//                        | empty

// <statement-list> ::= <statement-list> <statement> 
//                    | empty  

// <statement> ::= <expression-stmt>
//               | <compound-stmt>
//               | <selection-stmt>
//               | <iteration-stmt>
//               | <return-stmt>

// <expression-stmt> ::= <expression>;
//                     |;  

// <selection-stmt> ::= if (<expression>) <statement>
//                    | if (<expression>) <statement> else <statement>  

// <iteration-stmt> ::= while (<expression>) <statement>

// <return-stmt> ::= return;
//                 | return <expression>;  



// <expression> ::= <var> = <expression>
//                | <simple-expression>

// <var> ::= ID

// <simple-expression> ::= <expr> <relop> <expr>
//                       | <expr>

// <relop> ::= <= 
//           | < 
//           | > 
//           | >= 
//           | == 
//           | != 
//           | && 
//           | ||  
