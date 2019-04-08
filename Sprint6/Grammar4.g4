grammar Grammar4;

// ------------- prog
prog: funcdef* main;

// ------------- functions
main: 'int' 'main' '(' ')' '{' declaration* stat* rstat'}'
    ;
funcdef: rtype ID '(' dparams? ')' '{' declaration* stat* rstat?'}';

fncall: ID '(' cparams? ')';

// ------------- block
block:  '{' stat* rstat? '}';

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
variable: ID # decl
      | ID '=' expr # init
      ;

// ------------- statements
rstat: 'return' expr ';';
stat: ID '=' expr ';'   # asgn
    | fncall ';'        # callnr
    | ifelse # statifelse
    ;

// ------------- If else
ifelse : 'if' '(' expr ')' block elserule? ;

elserule : 'else' block # elseonly
      | 'else' ifelse # elseif ;

// ------------- expressions
expr: expr MULT expr # mult
    | expr PLUSMINUS expr # plusminus
    | INT           # const
    | ID            # var
    | '(' expr ')'  # par
    | fncall        # callr
    | expr COMPOP expr # compexpr
    | expr LOGOP expr # logexpr
    | UNOP expr # unopexpr
    ;

// ------------- types
rtype: type # rtypeTYPE
    | 'void' # rtypeVOID
    ;
type: 'int' # typeINT
    ;

// ------------- Comp operators
COMPOP: '==' 
      | '!=' 
      | '<' 
      | '>' 
      ;

// ------------- Logic operators
LOGOP: '&&' 
      | '||' 
      | '^' 
      ;

// ------------- terminals
MULT: [*];
PLUSMINUS: [+-];
UNOP: [-!]; 
INT: [0-9]+;
ID: [a-zA-Z][a-zA-Z0-9]*;
WS : [ \n\t\r] -> skip;