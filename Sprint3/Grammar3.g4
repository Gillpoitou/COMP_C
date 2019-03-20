grammar Grammar3;
prog: main;
main: tname 'main' '(' ')' '{' body '}';
tname: 'int';
body: declaration stat* rstat;
declaration: tname ID ';'
    | tname ID '=' expr ';';
rstat: 'return' INT ';' # retInt
    | 'return' ID ';'   # retVar;
stat: ID '=' expr ';';
expr: expr MULTDIV expr # multdiv
    | expr PLUSMINUS expr # plusminus
    | INT           # const
    | ID            # var
    | ’(’ expr ’)’  # par
    ;

MULTDIV: [*/];
PLUSMINUS: [+-];
INT: [0-9]+;
ID: [a-zA-Z][a-zA-Z0-9]+;
