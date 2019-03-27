#include "Function.h"

void Function::buildASM(ostream &o){

    int N;
    N = declarations->size()*16;
      o << "enter " << N  << ", 0" << endl;

      for(Declaration* decl : *declarations){
        //generate ASM
      }

      for(Statement* expr : *statements){
          //generate ASM
      }

      o << "leave" << endl;
      o << "ret" << endl;
}