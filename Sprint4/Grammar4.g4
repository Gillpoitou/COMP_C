grammar Grammar4;
prog: funcdef* main;
funcdef: rtype ID '(' dparamlist ')' '{' declaration* stats+ '}'
    ;
main: 'int' 'main' '(' ')' '{' declaration* stat* rstat '}'
    ;
stats: stat
    | rstat
    ;
declaration: type ID ';' #decl
    | type ID '=' expr ';' #init
    ;
rstat: 'return' expr ';';
stat: ID '=' expr ';'   #asgn
    | fncall ';'        #callnr
    ;
expr: expr MULTDIV expr # multdiv
    | expr PLUSMINUS expr # plusminus
    | INT           # const
    | CHAR          #constchar
    | ID            # var
    | '(' expr ')'  # par
    | fncall        #callr
    ;
fncall: ID '.' ID '(' cparamlist ')'
    ;
dparamlist: dparams
    |
    ;
dparams: dparam ',' dparams
    | dparam
    ;
dparam: type ID
    ;
cparamlist: cparams
    | 
    ;
cparams: expr ',' cparams
    | expr
    ;

rtype: type
    | 'void'
    ;
type: 'int'
    | 'char'
    ;

MULTDIV: [*/];
PLUSMINUS: [+-];
INT: [0-9]+;
CHAR: '\'' . '\'';

ID: [a-zA-Z][a-zA-Z0-9]+;
WS : [ \n\t\r] -> skip;