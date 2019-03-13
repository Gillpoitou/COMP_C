grammar Grammar2;
prog: main;
main: tname 'main' '(' ')' '{' body '}';
tname: 'int';
body: stats rstat;
rstat: 'return' INT ';' # retInt
    | 'return' ID ';'   # retVar;
stats: stat stats
    | ;
stat: declaration;
declaration: tname ID '=' INT ';';

INT: [0-9]+;
ID: [a-zA-Z][a-zA-Z0-9]+;
