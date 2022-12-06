/*
 * @Author: yinn
 * @Date: 2022-12-04 13:51:34
 * @LastEditTime: 2022-12-06 00:03:44
 * @Description:
 */

#include"parser.h"

ASTNode* parser(Token* tokenList) {
    return program(&tokenList->next);
}


// <program> ::= <declaration-list>

// <declaration-list> ::= <declaration> <declaration-list-tail>

// <declaration-list-tail> ::= <declaration> <declaration-list-tail>
//                           | empty

// <declaration> ::= <var-declaration> 
//                 | <func-declaration>

// <var-declaration> ::= <non-void-type-specifier> ID; 

// <non-void-type-specifier> ::= int

// <func-declaration> ::= <type-specifier> ID(<params>) <compound-stmt> 

// <type-specifier> ::= int 
//                    | void

// <params> ::= <params-list>
//            | void  

// <param-list> ::= <param> <param-list-tail>

// <param-list-tail> ::= ,<param> <param-list-tail>
//                     | empty

// <param> ::= <non-void-type-specifier> ID

// <statement-list> ::= <statement> <statement-list> 
//                    | empty  

// <compound-stmt> ::= { <statement-list> }

// <statement> ::= <expression-stmt>
//               | <compound-stmt>
//               | <selection-stmt>
//               | <iteration-stmt>
//               | <return-stmt>
//               | <var-declaration>

// <expression-stmt> ::= <expression>;
//                     |;  

// <selection-stmt> ::= if (<expression>) <statement>
//                    | if (<expression>) <statement> else <statement>  

// <iteration-stmt> ::= while (<expression>) <statement>

// <return-stmt> ::= return;
//                 | return <expression>;  

//  <expression> ::= <var> = <expression>
//                 | <simple-expr>
// 
//  <var> ::= ID
// 
//  <simple-expr> ::= <add-expr> <simple-expr-tail>
// 
//  <simple-expr-tail> ::= <relop> <add-expr>
//                       | empty   

//  <relop> ::= >
//            | <
//            | >=
//            | <=
//            | ==
//            | !=

//  <add-expr> ::= <term> <add-expr-tail>
// 
//  <add-expr-tail> ::= <addop> <term> <add-expr-tail>
//                    | <empty>
// 
//  <addop> ::= +
//            | -

//  <term> :: = <factor> <term-tail>
//  
//  <term-tail> ::= <mulop> <factor> <term-tail>
//                | <empty>
//  
//  <mulop> ::= *
//            | /

//  <factor> :: = (<add-expr>)
//             | Num
//             | <var>
//             | <call>

//  <var> ::= ID
// 
//  <call> ::= ID(<args>)

//  <args> ::= <arg-list>
//           | void
// 
//  <arg-list> ::= <expression> <arg-list-tail>
// 
//  <arg-list-tail> ::= ,<expression> <arg-list-tail>
//                   | empty
