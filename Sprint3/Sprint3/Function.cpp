#include "Function.h"
#include <iostream>

Function::Function(vector<Declaration *> *declarations, vector<Statement *> *stats, StatementReturn *rstat){
 this->declarations = declarations;
 this->statements = stats;  
 this->rstat = rstat;

}

void Function::buildASM(ostream &o){

    int N;
    N = declarations->size()*4 +16;

      o << "pushq %rbp" << endl;
      o << "movq    %rsp, %rbp" << endl;

      for(Declaration* decl : *declarations){
        decl->buildASM(o,&SymbolIndex, &lastOffset);
      }
      for(Statement* stat : *statements){
        stat->buildASM(o,&SymbolIndex);
      }
      rstat->buildASM(o,&SymbolIndex);

      o << "popq    %rbp" << endl;
      o << "ret" << endl;
}