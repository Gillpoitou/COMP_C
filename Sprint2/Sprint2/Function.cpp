#include "Function.h"

Function::Function(vector<Declaration *> *declarations, vector<Statement *> *stats){
 this->declarations = declarations;
 this->statements = stats;  

}

void Function::buildASM(ostream &o){

    int N;
    N = declarations->size()*4 +16;

      o << "pushq %rbp" << endl;
      o << "movq    %rsp, %rbp" << endl;

      for(Declaration* decl : *declarations){
        decl->buildASM(o,&SymbolIndex, &lastOffset);
      }

      for(Statement* statm : *statements){
          statm->buildASM(o,&SymbolIndex);
      }

      o << "popq    %rbp" << endl;
      o << "ret" << endl;
}