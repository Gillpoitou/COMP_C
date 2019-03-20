#include "IR.h"

using namespace antlr4;
using namespace std;


//------------IRInstr
IRInstr::IRInstr(BasicBlock* bb_, Operation op, Type t, vector<string> params){
    this.bb = bb_;
    this.op = op;
    this.t = t;
    this.params = params;
}

void gen_asm(ostream &o){
    switch (this.op)
    {
        case ldconst:
		
            /* code */
            break;
        case add:

            break;
        case sub:

            break;
		case mul:

            break;
		case rmem:

            break;
		case wmem:

            break;
		case call:

            break;
		case cmp_eq:

            break; 
		case cmp_lt:

            break;
		case cmp_le:

            break;
        default:
            break;
    }
}

