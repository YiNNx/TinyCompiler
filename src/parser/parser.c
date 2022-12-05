/*
 * @Author: yinn
 * @Date: 2022-12-04 13:51:34
 * @LastEditTime: 2022-12-05 21:19:39
 * @Description:
 */

#include"parser.h"

ASTNode* parser(Token* tokenList) {
    return funcDeclaration(&tokenList->next);
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


// <local-declarations> ::= <local-declarations> <var-declaration>
//                        | empty

// <compound-stmt> ::= { <local-declarations> <statement-list> }

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

// --------

 // <expression> ::= <var> = <expression>
 //                | <simple-expr>

 // <var> ::= ID

 // <simple-expr> ::= <add-expr> <relop> <add-expr>
 //                       | <add-expr>

 // <relop> ::= <= 
 //           | < 
 //           | > 
 //           | >= 
 //           | == 
 //           | != 
 //           | && 
 //           | ||  

// ------------------------------------------

 // <add-expr> ::= <add-expr> <addop> <term> 
 //          | <term>

 // <addop> ::= + 
 //           | -  

 // <term> ::= <term> <mulop> <factor> 
 //          | <factor>

 // <mulop> ::= * 
 //           | /  

 // <factor> ::= (<expression>) 
 //            | <var> 
 //            | <call> 
 //            | NUM  

 // <call> ::= ID(<args>)  

 // <args> ::= <arg-list>
 //          | empty  

 // <arg-list> ::= <arg-list>, <expression>
 //              | <expression> 