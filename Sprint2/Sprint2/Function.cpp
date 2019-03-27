#include "Function.h"

void Function::buildASM(ostream &o){

    int N;
    N = declarations->size()*16;
      o << "enter " << N  << ", 0" << endl;

      for(Declaration* decl : *declarations){
        decl->buildASM(o);
      }

      for(Statement* statm : *statements){
          statm->buildASM(o);
      }

      o << "leave" << endl;
      o << "ret" << endl;
}