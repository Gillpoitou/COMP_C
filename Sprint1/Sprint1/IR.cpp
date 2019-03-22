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

CFG::CFG(DefFonction* ast){
      this->ast = ast;
}

void CFG::add_bb(BasicBlock* bb){
      bbs.push_back(bb);
}

void CFG::gen_asm(ostream& o){
      for(BasicBlock* cbb : bbs){
            cbb->gen_asm(o);
      }
}

string CFG::IR_reg_to_asm(string reg){
      //TODO
      return "";
}

void CFG::gen_asm_prologue(ostream& o){
      //TODO
}

void CFG::gen_asm_epilogue(ostream& o){
      //TODO
}

void CFG::add_to_symbol_table(string name, Type t){
      SymbolType.insert(pair<string,Type>(name,t));
}

string CFG::create_new_tempvar(Type t){
      //TODO
      return "";
}

int CFG::get_var_index(string name){
      return SymbolIndex.at(name);
}

Type CFG::get_var_type(string name){
      return SymbolType.at(name);
}