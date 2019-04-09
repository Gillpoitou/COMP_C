#include "IR.h"
#include "Function.h"
#include "Expression.h"
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
	    o << "movl -" << this->bb->cfg->get_var_index(params[1]) << "(%rbp), %edx" << endl;
      	    o << "movl -" << this->bb->cfg->get_var_index(params[2]) << "(%rbp), %eax" << endl;
            o << "addl %edx, %eax" << endl;
	    o << "movl %eax, -" << this->bb->cfg->get_var_index(params[0]) << "(%rbp)" << endl;
            
            break;
            }
        case sub:
	    o << "movl -" << this->bb->cfg->get_var_index(params[1]) << "(%rbp), %eax" << endl;
      	    o << "subl -" << this->bb->cfg->get_var_index(params[2]) << "(%rbp), %eax" << endl;
	    o << "movl %eax, -" << this->bb->cfg->get_var_index(params[0]) << "(%rbp)" << endl;
            break;
      case neg:
            o << "movl -" << this->bb->cfg->get_var_index(params[1]) << "(%rbp), %eax" << endl;
            o << "negl %eax" << endl;
            o << "movl %eax, -" << this->bb->cfg->get_var_index(params[0]) << "(%rbp)" << endl;
            break;
	case mul:
            o << "movl -" << this->bb->cfg->get_var_index(params[1]) << "(%rbp), %eax" << endl;
            o << "imull -" << this->bb->cfg->get_var_index(params[2]) << "(%rbp), %eax" << endl;
            o << "movl %eax, -" << this->bb->cfg->get_var_index(params[0]) << "(%rbp)" << endl;
            break;
	case rmem:

            break;
	case wmem:
           o << "movl -" << this->bb->cfg->get_var_index(params[1]) << "(%rbp), %eax" << endl;
           o << "movl %eax, -" << this->bb->cfg->get_var_index(params[0]) << "(%rbp)" << endl;
            break;
	case call:
            for(int i = 2 ; i < params.size() ; i ++){
                  if(i > 7) break;
                 o << "movl   -" << this->bb->cfg->get_var_index(params[i]) << "(%rbp),%" << this->bb->cfg->registers[i-2] << endl;
            }
            o << "call  " << params[0] << endl;
            o << "movl  %eax,-" << this->bb->cfg->get_var_index(params[1]) << "(%rbp)" << endl;
            break;
	case cmp_eq:
            o << "movl -" << this->bb->cfg->get_var_index(params[0]) << "(%rbp), %eax" << endl;
            o << "cmpl -" << this->bb->cfg->get_var_index(params[1]) << "(%rbp), %eax" << endl;
            o << "jne ." << bb->exit_false->label << endl;
            break;
  	case cmp_neq:
            o << "movl -" << this->bb->cfg->get_var_index(params[0]) << "(%rbp), %eax" << endl;
            o << "cmpl -" << this->bb->cfg->get_var_index(params[1]) << "(%rbp), %eax" << endl;
            o << "je ." << bb->exit_false->label << endl;
            break; 
	case cmp_lt:
            o << "movl -" << this->bb->cfg->get_var_index(params[0]) << "(%rbp), %eax" << endl;
            o << "cmpl -" << this->bb->cfg->get_var_index(params[1]) << "(%rbp), %eax" << endl;
            o << "jl ." << bb->exit_false->label << endl;
            break;
	case cmp_gt:
            o << "movl -" << this->bb->cfg->get_var_index(params[0]) << "(%rbp), %eax" << endl;
            o << "cmpl -" << this->bb->cfg->get_var_index(params[1]) << "(%rbp), %eax" << endl;
            o << "jg ." << bb->exit_false->label << endl;
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
      generated = true;

      for(IRInstr* i : instrs){
            i->gen_asm(o);
      }
      if(exit_true == nullptr){
			this->cfg->gen_asm_epilogue(o);
			o << endl;
            return;
      }

      o << "jmp ." << exit_true->label << endl;
      o << endl;
      if(!exit_true->generated){
            o << "." << exit_true->label <<":" << endl;
            exit_true->gen_asm(o);
      }

      if(exit_false != nullptr && !exit_false->generated){
            o << "." << exit_false->label <<":" << endl;
            exit_false->gen_asm(o);
      } 
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
      bbs[0]->gen_asm(o);
      o << endl;
}

string CFG::IR_reg_to_asm(string reg){
      string regNb = reg.substr(4);
      return "-"+ regNb + "(%rbp)";
}

void CFG::gen_asm_prologue(ostream& o){
      int size = 0;
      for (const auto& symbol_pair : SymbolIndex) {
          size += 4;
      }

      size += 16 - (size % 16); // align to 16 bytes.

      o << this->ast->name << ":" << endl;
      o << "pushq %rbp" << endl;
      o << "movq    %rsp, %rbp" << endl;
      o << "subq $" << size+8 << ", %rsp" << endl;
      for(int i = 0 ; i < this->ast->params->size() ; i++){

            string name = ast->params->at(i)->name;
             o << "movl   %"<< registers[i] << ",-" << get_var_index(name) << "(%rbp)" << endl;
      }
}

void CFG::gen_asm_epilogue(ostream& o){
      o << "leave" << endl;
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

string CFG::new_BB_name(){
      return "L" + to_string(bbs.size());
}
