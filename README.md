# TinyCompiler

## Keywords

```
int
void
if
else
while
return
```

## Operators

```
+
-
*
/

=
>
<
!=
<=
>=
==
```

## Others

```
{digit} // int only
{varible name}
{function name}

/* */
,
;
{}
()
main
input
output
```

## Example Code

```
/* program for the nth fibonacci num */
int fibonacci(int n) {
    int a = 1, b = 1, res = 0;
    if (n <= 0)return 0;
    else if (n <= 2)return 1;

    int i = 2;
    while (i < n) {
        res = a + b;
        a = b;
        b = res;
        i = i + 1;
    }
    return res;
}

void main(void) {
    int n = input();
    int res = fibonacci(n);
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
INT,
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
ASSIGN,
INPUT,
LC,
RC,
SEMI,
INT,
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

