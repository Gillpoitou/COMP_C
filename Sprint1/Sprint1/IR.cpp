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
            o << "movq $" + params[1] + ",      -" + reg + "(%rpb)" << endl;
            break;
            }
        case Operation::add:
        {
            string destination = params[0].substr(4);
            string source1 = "";
            string source2 = "";
            if (params[1].substr(0,1).compare("!") == 0){
                  string source1 = params[1].substr(4);
                  o << "movq -" + source1 + "(%rbp),    %rax" << endl;
            }else{
                  //get from ST
                  string index = to_string(bb->cfg->get_var_index(params[1]));
                  
                  o << "movq -" + index + "(%rbp),    %rax       #offset of " + params[1] + " is -" + index << endl;
            }

            if (params[2].substr(0,1).compare("!") == 0){
                  string source2 = params[2].substr(4);
                  o << "addq -" + source2 + "(%rbp),    %rax" << endl;
            }else{
                  //get from ST
                  string index = to_string(bb->cfg->get_var_index(params[2]));
                  o << "addq -" + index + "(%rbp),    %rax       #offset of " + params[2] + " is -" + index << endl;
            }

            o << "movq %rax,        -" + destination + "(%rbp)" << endl;
            
            break;
            }
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
      string regNb = reg.substr(4);
      return "-"+ regNb + "(%rbp)";
}

void CFG::gen_asm_prologue(ostream& o){
      int N;
      for(map<string,Type>::iterator itr = SymbolType.begin(), itr_end = SymbolType.end(); itr != itr_end ; itr++){
            N += itr->second.size;
      }

      o << "enter " << N << ", 0" << endl;
}

void CFG::gen_asm_epilogue(ostream& o){
      o << "leave" << endl;
      o << "ret" << endl;
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