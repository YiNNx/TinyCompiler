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
/*the maximum of three numbers*/
int max(int x, int y, int z)
{
    int biggest;
    biggest = x;
    if(y>biggest) /*comment example*/
    biggest = y;
    if(z>biggest) biggest = z; return biggest;
}

void main(void)
{
    int x,y,z;
    int biggest; x = input();
    y = input(); z = input();
    biggest = max(x, y, z); output(biggest);
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

