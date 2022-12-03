# TinyCompiler

## Keywords

```
int void if else while return
```

## Operators

```
+ - * / = > < != <= >= ==
```

## Others

```
digit
varible
function()
/* comments */
, ;
{} ()
main() input() output()
```

## BNF Defination

```
<program> ::= <declaration-list>

<declaration-list> ::= <declaration-list> <declaration> 
                     | <declaration>

<declaration> ::= <var-declaration> 
                | <func-declaration>

<var-declaration> ::= <type-specifier> ID; 

<type-specifier> ::= int 
                   | void

<func-declaration> ::= <type-specifier> ID(<params>) <compound-stmt> 

<params> ::= <params-list>
           | void  
           
<param-list> ::= <param-list>,<param>
               | <param>
               
<param> ::= <type-specifier> ID

<compound-stmt> ::= { <local-declarations> <statement-list> }

<local-declarations> ::= <local-declarations> <var-declaration>
                       | empty
                       
<statement-list> ::= <statement-list> <statement> 
                   | empty  
                   
<statement> ::= <expression-stmt>
              | <compound-stmt>
              | <selection-stmt>
              | <iteration-stmt>
              | <return-stmt>
              
<expression-stmt> ::= <expression>;
                    |;  
                    
<selection-stmt> ::= if (<expression>) <statement>
                   | if (<expression>) <statement> else <statement>  
                   
<iteration-stmt> ::= while (<expression>) <statement>

<return-stmt> ::= return;
                | return <expression>;  
                  
<expression> ::= <var> = <expression>
               | <simple-expression>
               
<var> ::= ID

<simple-expression> ::= <expr> <relop> <expr>
                      | <expr>
                      
<relop> ::= <= 
          | < 
          | > 
          | >= 
          | == 
          | != 
          | && 
          | ||  
        
<expr> ::= <expr> <addop> <term> 
               | <term>
                        
<addop> ::= + 
          | -  

<term> ::= <term> <mulop> <factor> 
         | <factor>
         
<mulop> ::= * 
          | /  
          
<factor> ::= (<expression>) 
           | <var> 
           | <call> 
           | NUM  
           
<call> ::= ID(<args>)  

<args> ::= <arg-list>
         | empty  
         
<arg-list> ::= <arg-list>, <expression>
             | <expression> 
```

## Example Code

```
/* for the nth fibonacci num */
int fibonacci(int n) {
    if (n <= 0) return 0;
    else if (n <= 2) return 1;

    int a, b, res, i;
    a = b = 1;
    res = 0;
    i = 2;
    while (i < n) {
        res = a + b;
        a = b;
        b = res;
        i = i + 1;
    }
    return res;
}

void main(void) {
    int n, res;
    n = input();
    res = fibonacci(n);
    output(res);
}
```

## Lexer

```
COMMENT,
INT,
FUNC: fibonacci,
LC,
INT,
VAR: n,
RC,
LP,
IF,
LC,
VAR: n,
LESS_OR_EQL,
DIGIT_INT: 0,
RC,
RETURN,
DIGIT_INT: 0,
SEMI,
ELSE,
IF,
LC,
VAR: n,
LESS_OR_EQL,
DIGIT_INT: 2,
RC,
RETURN,
DIGIT_INT: 1,
SEMI,
INT,
VAR: a,
COMMA,
VAR: b,
COMMA,
VAR: res,
COMMA,
VAR: i,
SEMI,
VAR: a,
ASSIGN,
VAR: b,
ASSIGN,
DIGIT_INT: 1,
SEMI,
VAR: res,
ASSIGN,
DIGIT_INT: 0,
SEMI,
VAR: i,
ASSIGN,
DIGIT_INT: 2,
SEMI,
WHILE,
LC,
VAR: i,
LESS,
VAR: n,
RC,
LP,
VAR: res,
ASSIGN,
VAR: a,
PLUS,
VAR: b,
SEMI,
VAR: a,
ASSIGN,
VAR: b,
SEMI,
VAR: b,
ASSIGN,
VAR: res,
SEMI,
VAR: i,
ASSIGN,
VAR: i,
PLUS,
DIGIT_INT: 1,
SEMI,
RP,
RETURN,
VAR: res,
SEMI,
RP,
VOID,
MAIN,
LC,
VOID,
RC,
LP,
INT,
VAR: n,
COMMA,
VAR: res,
SEMI,
VAR: n,
ASSIGN,
INPUT,
LC,
RC,
SEMI,
VAR: res,
ASSIGN,
FUNC: fibonacci,
LC,
VAR: n,
RC,
SEMI,
OUTPUT,
LC,
VAR: res,
RC,
SEMI,
RP
```

## AST

```
FUNCTION fibonacci
  ASSIGN
    ASSIGN
      INTLIT 1
      IDENT b
    IDENT a
  ASSIGN
    INTLIT 0
    IDENT res
  ASSIGN
    INTLIT 2
    IDENT i
  IF, end L2
    LE
      IDENT rval n
      INTLIT 0
    RETURN
      WIDEN
        INTLIT 0
    IF
      LE
        IDENT rval n
        INTLIT 2
      RETURN
        WIDEN
          INTLIT 1
  WHILE, start L4
    LT
      IDENT rval i
      IDENT rval n
    ASSIGN
      ADD
        IDENT rval a
        IDENT rval b
      IDENT res
    ASSIGN
      IDENT rval b
      IDENT a
    ASSIGN
      IDENT rval res
      IDENT b
    ASSIGN
      ADD
        IDENT rval i
        INTLIT 1
      IDENT i
  RETURN
    IDENT rval res

FUNCTION main
  ASSIGN
    FUNCCALL input
    IDENT n
  ASSIGN
    FUNCCALL fibonacci
      IDENT rval n
    IDENT res
  FUNCCALL output
    IDENT rval res

```

