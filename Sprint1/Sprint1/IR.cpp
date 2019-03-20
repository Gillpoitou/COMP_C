#include "IR.h"


//------------IRInstr
IRInstr::IRInstr(BasicBlock* bb_, Operation op, Type t, vector<string> params){
    this->bb = bb_;
    this->op = op;
    this->t = t;
    this->params = params;
}

void IRInstr::gen_asm(ostream &o){
      
    switch (this->op)
    {
        case Operation::ldconst:
        {
		string reg = params[0].substr(4);
            o << "movq $" + params[1] + ",      -" + reg + "(%rpb)";
            break;
            }
        case Operation::add:
           
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

BasicBlock::BasicBlock(CFG* cfg, string entry_label){
      this->cfg = cfg;
      this->label = entry_label;
}

void BasicBlock::gen_asm(ostream &o){
      for(IRInstr* i : instrs){
            i->gen_asm(o);
      }
}

void BasicBlock::add_IRInstr(IRInstr::Operation op, Type t, vector<string> params){
      instrs.push_back(new IRInstr(this,op,t,params));
}


