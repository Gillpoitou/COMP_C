grammar Sprint1;
prog: main;
main: tname 'main' '(' ')' '{' body ')';
tname: 'int';
body: 'return' INT ';';
INT: [0-9]+;