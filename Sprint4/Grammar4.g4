grammar Grammar4;

// ------------- prog
prog: funcdef* main;

// ------------- functions
main: 'int' 'main' '(' ')' '{' declaration* stats* rstat '}'
    ;
funcdef: rtype ID '(' dparamlist ')' '{' declaration* stats+ '}'
    ;
fncall: ID '.' ID '(' cparamlist ')'
    ;

// ------------- functions params
dparamlist: dparams?
    ;
dparams: dparam ',' dparams
    | dparam
    ;
dparam: type ID
    ;
cparamlist: cparams?
    ;
cparams: expr ',' cparams
    | expr
    ;

// ------------- variables
declaration: type variableList ';' ;
variableList: variables ;
variables: variable ',' variables 
      | variable
      ;
variable: ID #decl
      | ID '=' expr #init
      ;

// ------------- statements
stats: stat
    | rstat
    ;
rstat: 'return' expr ';';
stat: ID '=' expr ';'   #asgn
    | fncall ';'        #callnr
    ;

// ------------- expressions
expr: expr MULTDIV expr # multdiv
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
MULTDIV: [*/];
PLUSMINUS: [+-];
INT: [0-9]+;
ID: [a-zA-Z][a-zA-Z0-9]+;
WS : [ \n\t\r] -> skip;