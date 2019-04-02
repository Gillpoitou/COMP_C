#include "IR.h"
#include "Function.h"
#include <iostream>

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
            o << "movl $" << params[1] << ", -" << this->bb->cfg->get_var_index(params[0]) << "(%rbp)" << endl;
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
           o << "movl -" << this->bb->cfg->get_var_index(params[1]) << "(%rbp), %eax" << endl;
           o << "movl %eax, -" << this->bb->cfg->get_var_index(params[0]) << "(%rbp)" << endl;
            break;
	case call:

            break;
	case cmp_eq:

            break; 
	case cmp_lt:

            break;
	case cmp_le:

            break;
	case decl:
	    break;
	case ret:
	  o << "movl -" << this->bb->cfg->get_var_index(params[0]) << "(%rbp), %eax" << endl;
      default:
            break;
    }
}

BasicBlock::BasicBlock(CFG* cfg, string entry_label){
      this->cfg = cfg;
      this->label = entry_label;
      this->exit_true = nullptr;
      this->exit_false = nullptr;
}

void BasicBlock::gen_asm(ostream &o){
      //o << "." << label << endl;

      for(IRInstr* i : instrs){
            i->gen_asm(o);
      }
      if(exit_true == nullptr){
            return;
      }
      if(exit_false != nullptr){
            o << "." << exit_false->label << endl;
            exit_false->gen_asm(o);
      }

      exit_true->gen_asm(o);
}

void BasicBlock::add_IRInstr(IRInstr::Operation op, Type t, vector<string> params){
      instrs.push_back(new IRInstr(this,op,t,params));
}

CFG::CFG(Function* ast){
      this->ast = ast;

}

void CFG::add_bb(BasicBlock* bb){
      bbs.push_back(bb);
}

void CFG::gen_asm(ostream& o){
      gen_asm_prologue(o);
      for(BasicBlock* cbb : bbs){
            cbb->gen_asm(o);
      }
      gen_asm_epilogue(o);
}

string CFG::IR_reg_to_asm(string reg){
      string regNb = reg.substr(4);
      return "-"+ regNb + "(%rbp)";
}

void CFG::gen_asm_prologue(ostream& o){
      o << ".text" << endl;
      o << ".global main" << endl;
      o << "main:" << endl;
      o << "pushq %rbp" << endl;
      o << "movq    %rsp, %rbp" << endl;
}

void CFG::gen_asm_epilogue(ostream& o){
      o << "popq    %rbp" << endl;
      o << "ret" << endl;
}

void CFG::add_to_symbol_table(string name, Type t){
      SymbolType.insert(pair<string,Type>(name,t));
      nextFreeSymbolIndex = nextFreeSymbolIndex + 4;
      SymbolIndex.insert(pair<string,int>(name,nextFreeSymbolIndex));
}

string CFG::create_new_tempvar(Type t){
      string name = "temp"+ to_string(nextFreeSymbolIndex);
      add_to_symbol_table(name, t);
      return name;
}

int CFG::get_var_index(string name){
      return SymbolIndex.at(name);
}

Type CFG::get_var_type(string name){
      return SymbolType.at(name);
}
