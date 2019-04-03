grammar Grammar4;

// ------------- prog
prog: funcdef* main;

// ------------- functions
main: 'int' 'main' '(' ')' '{' declaration* stat* rstat'}'
    ;
funcdef: rtype ID '(' dparams? ')' '{' declaration* stat* rstat?'}'
    ;
fncall: ID '(' cparams? ')'
    ;

// ------------- functions params
dparams: dparam ',' dparams
    | dparam
    ;
dparam: type ID
    ;
cparams: expr ',' cparams
    | expr
    ;

// ------------- variables
declaration: type variables ';' ;
variables: variable ',' variables 
      | variable
      ;
variable: ID #decl
      | ID '=' expr #init
      ;

// ------------- statements
rstat: 'return' expr ';';
stat: ID '=' expr ';'   #asgn
    | fncall ';'        #callnr
    ;

// ------------- expressions
expr: expr MULT expr # mult
    | expr PLUSMINUS expr # plusminus
    | INT           # const
    | ID            # var
    | '(' expr ')'  # par
    | fncall        #callr
    ;

// ------------- types
rtype: type
    | 'void'
    ;
type: 'int'
    ;

// ------------- terminals
MULT: [*];
PLUSMINUS: [+-];
INT: [0-9]+;
ID: [a-zA-Z][a-zA-Z0-9]+;
WS : [ \n\t\r] -> skip;