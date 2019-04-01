grammar Grammar3;
prog: main;
main: 'int' 'main' '(' ')' '{' declaration* stat* rstat '}';
declaration: 'int' ID ';' #decl
    | 'int' ID '=' expr ';' #init
    ;
rstat: 'return' expr ';';
stat: ID '=' expr ';';
expr: expr MULTDIV expr # multdiv
    | expr PLUSMINUS expr # plusminus
    | INT           # const
    | ID            # var
    | '(' expr ')'  # par
    ;

MULTDIV: [*/];
PLUSMINUS: [+-];
INT: [0-9]+;
ID: [a-zA-Z][a-zA-Z0-9]+;
WS : [ \n\t\r] -> skip;