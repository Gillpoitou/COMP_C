grammar Grammar2;
prog: main;
main: 'int' 'main' '(' ')' '{' declaration* rstat '}';
rstat: 'return' INT ';' # retInt
    | 'return' ID ';'   # retVar;
declaration: 'int' ID '=' INT ';' # initCst
    | 'int' ID '=' ID ';' # initVar
    | 'int' ID ';' # decl
    ;
INT: [0-9]+;
ID: [a-zA-Z][a-zA-Z0-9]+;