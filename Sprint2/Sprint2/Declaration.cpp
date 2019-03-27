#include "Declaration.h"

void Declaration::buildASM(ostream &o, map<string,int>* symbolTable, int* lastOffset){
    *lastOffset = *lastOffset + 4;
    pair<string,int> var(left->name,*lastOffset);
    symbolTable->insert(var);
}