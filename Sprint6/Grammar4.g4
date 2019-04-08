grammar Grammar4;

// ------------- prog
prog: funcdef* main;

// ------------- functions
main: 'int' 'main' '(' ')' bloc;

funcdef: rtype ID '(' dparams? ')' bloc;

fncall: ID '(' cparams? ')';

// ------------- bloc
bloc: '{' declaration* stat* rstat '}';

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
    | ifelse ';' # statifelse
    ;

// ------------- If else
ifelse : 'if' '(' expr ')' bloc elserule? ;

elserule : 'else' bloc # elseonly
      | 'else' ifelse # elseif ;

// ------------- expressions
expr: expr MULT expr # mult
    | expr PLUSMINUS expr # plusminus
    | INT           # const
    | ID            # var
    | '(' expr ')'  # par
    | fncall        # callr
    | expr compop expr # comp
    | expr logop expr # log
    | UNOP expr # unopexpr
    ;

// ------------- types
rtype: type # rtypeTYPE
    | 'void' # rtypeVOID
    ;
type: 'int' # typeINT
    ;

// ------------- Comp operators
compop: '==' # eqcomp
      | '!=' # difcomp
      | '<' # infcomp
      | '>' # supcomp
      ;

// ------------- Logic operators
logop: '&&' # and
      | '||' # or
      | '^' # xor
      ;

// ------------- terminals
MULT: [*];
PLUSMINUS: [+-];
UNOP: [-!]; 
INT: [0-9]+;
ID: [a-zA-Z][a-zA-Z0-9]*;
WS : [ \n\t\r] -> skip;