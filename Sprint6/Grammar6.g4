grammar Grammar6;
prog: main;
main: 'int' 'main' '(' ')' '{' body '}';
body: declaration* stat* rstat;
declaration: 'int' ID ';'
    | 'int' ID '=' expr ';';
rstat: 'return' INT ';' # retInt
    | 'return' ID ';'   # retVar;
stat: ID '=' expr ';' # affectation
    | ifelse # ifelse;
expr: expr MULTDIV expr # multdiv
    | expr PLUSMINUS expr # plusminus
    | INT           # const
    | ID            # var
    | ’(’ expr ’)’  # par
    ;
ifelse : 'if' '(' cond ')' '{' body else? '}' ;
cond : expr '==' expr;
else : '}' 'else' '{' body # else
    |'}' 'else' ifelse # elseif ;

MULTDIV: [*/];
PLUSMINUS: [+-];
INT: [0-9]+;
ID: [a-zA-Z][a-zA-Z0-9]+;
