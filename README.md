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

<var-declaration> ::= <type-specifier> ID

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
                   | if (<expression>) <compound-stmt>
                   | if (<expression>) <statement> else <compound-stmt>  
                   
<iteration-stmt> ::= while (<expression>) <statement>
                   | while (<expression>) <compound-stmt>

<return-stmt> ::= return;
                | return <expression>;  
                  
<expression> ::= <var> = <expression>
               | <simple-expression>
               
<var> ::= ID

<simple-expression> ::= <additive-expression> <relop> <additive-expression>
                      | <additive-expression>
                      
<relop> ::= <= 
          | < 
          | > 
          | >= 
          | == 
          | != 
          | && 
          | ||  
        
<additive-expression> ::= <additive-expression> <addop> <term> 
                        | <term>
                        
<addop> ::= + 
          | -  

<term> ::= <term> <mulopfactor> 
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
    int a = 1, b = 1, res = 0, i = 2;
    if (n <= 0) return 0;
    else if (n <= 2) return 1;

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
INT,
VAR: a,
ASSIGN,
DIGIT_INT: 1,
COMMA,
VAR: b,
ASSIGN,
DIGIT_INT: 1,
COMMA,
VAR: res,
ASSIGN,
DIGIT_INT: 0,
COMMA,
VAR: i,
ASSIGN,
DIGIT_INT: 2,
SEMI,
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

