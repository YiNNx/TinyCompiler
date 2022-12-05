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

<var-declaration> ::= <non-void-type-specifier> ID; 

<non-void-type-specifier> ::= int

<func-declaration> ::= <type-specifier> ID(<params>) <compound-stmt> 

<type-specifier> ::= int 
                   | void

<params> ::= <params-list>
           | void  

<param-list> ::= <param-list>,<param>
               | <param>
              
<param> ::= <non-void-type-specifier> ID

<statement-list> ::= <statement> <statement-list> 
                   | empty  

<compound-stmt> ::= { <statement-list> }

<statement> ::= <expression-stmt>
              | <compound-stmt>
              | <selection-stmt>
              | <iteration-stmt>
              | <return-stmt>
              | <var-declaration>

<expression-stmt> ::= <expression>;
                    |;  

<selection-stmt> ::= if (<expression>) <statement>
                   | if (<expression>) <statement> else <statement>  

<iteration-stmt> ::= while (<expression>) <statement>

<return-stmt> ::= return;
                | return <expression>;  

<expression> ::= <var> = <expression>
                | <simple-expr>

<var> ::= ID

<simple-expr> ::= <add-expr> <relop> <add-expr>
                | <add-expr>

<relop> ::= >
          | <
          | >=
          | <=
          | ==
          | !=

<add-expr> ::= <add-expr> <addop> <term> 
               | <term>
      
<addop> ::= +
           | -

<term> ::= <term> <mulop> <factor> 
         | <factor>
       
<mulop> ::= *
           | /

<factor> :: = (<add-expr>)
            | Num
            | <var>
            | <call>

<var> ::= ID

<call> ::= ID(<args>)

 <args> ::= <arg-list>
          | void

<arg-list> ::= <arg-list>, <expression>
             | <expression> 
```

## After Elimination of Left Recursion

```
<program> ::= <declaration-list>

<declaration-list> ::= <declaration> <declaration-list-tail>

<declaration-list-tail> ::= <declaration> <declaration-list-tail>
                          | empty

<declaration> ::= <var-declaration> 
                | <func-declaration>

<var-declaration> ::= <non-void-type-specifier> ID; 

<non-void-type-specifier> ::= int

<func-declaration> ::= <type-specifier> ID(<params>) <compound-stmt> 

<type-specifier> ::= int 
                   | void

<params> ::= <params-list>
           | void  

<param-list> ::= <param> <param-list-tail>

<param-list-tail> ::= ,<param> <param-list-tail>
                    | empty

<param> ::= <non-void-type-specifier> ID

<statement-list> ::= <statement> <statement-list> 
                   | empty  

<compound-stmt> ::= { <statement-list> }

<statement> ::= <expression-stmt>
              | <compound-stmt>
              | <selection-stmt>
              | <iteration-stmt>
              | <return-stmt>
              | <var-declaration>

<expression-stmt> ::= <expression>;
                    |;  

<selection-stmt> ::= if (<expression>) <statement>
                   | if (<expression>) <statement> else <statement>  

<iteration-stmt> ::= while (<expression>) <statement>

<return-stmt> ::= return;
                | return <expression>;  

<expression> ::= <var> = <expression>
                | <simple-expr>

<var> ::= ID

<simple-expr> ::= <add-expr> <simple-expr-tail>

<simple-expr-tail> ::= <relop> <add-expr>
                     | empty   

<relop> ::= >
          | <
          | >=
          | <=
          | ==
          | !=

<add-expr> ::= <term> <add-expr-tail>

<add-expr-tail> ::= <addop> <term> <add-expr-tail>
                  | <empty>

<addop> ::= +
          | -

<term> :: = <factor> <term-tail>
 
<term-tail> ::= <mulop> <factor> <term-tail>
               | <empty>
 
<mulop> ::= *
          | /

<factor> :: = (<add-expr>)
            | Num
            | <var>
            | <call>

<var> ::= ID

<call> ::= ID(<args>)

 <args> ::= <arg-list>
          | void

 <arg-list> ::= <expression> <arg-list-tail>

 <arg-list-tail> ::= ,<expression> <arg-list-tail>
                   | empty
```

## Example Code

```
int fibonacci(int n) {
    if (n <= 0) return 0;
    else if (n <= 2) return 1;
    
    int a;
    int b;
    int res;
    int i;
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
```

## Lexer

```
INT,
FUNC: fibonacci,
LP,
INT,
VAR: n,
RP,
LC,
IF,
LP,
VAR: n,
LESS_OR_EQL,
DIGIT_INT: 0,
RP,
RETURN,
DIGIT_INT: 0,
SEMI,
ELSE,
IF,
LP,
VAR: n,
LESS_OR_EQL,
DIGIT_INT: 2,
RP,
RETURN,
DIGIT_INT: 1,
SEMI,
INT,
VAR: a,
SEMI,
INT,
VAR: b,
SEMI,
INT,
VAR: res,
SEMI,
INT,
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
LP,
VAR: i,
LESS,
VAR: n,
RP,
LC,
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
RC,
RETURN,
VAR: res,
SEMI,
RC
```

## AST

```
func: fibonacci, ret int 
    └── int var: n
    └── {}
        └── if
        │   └── <=
        │   │   └── n
        │   │   └── 0
        │   └── return
        │   │   └── 0
        │   └── if
        │       └── <=
        │       │   └── n
        │       │   └── 2
        │       └── return
        │           └── 1
        └── int var: a
        └── int var: b
        └── int var: res
        └── int var: i
        └── =
        │   └── a
        │   └── =
        │       └── b
        │       └── 1
        └── =
        │   └── res
        │   └── 0
        └── =
        │   └── i
        │   └── 2
        └── while
        │   └── <
        │   │   └── i
        │   │   └── n
        │   └── {}
        │       └── =
        │       │   └── res
        │       │   └── +
        │       │       └── a
        │       │       └── b
        │       └── =
        │       │   └── a
        │       │   └── b
        │       └── =
        │       │   └── b
        │       │   └── res
        │       └── =
        │           └── i
        │           └── +
        │               └── i
        │               └── 1
        └── return
            └── res
```

