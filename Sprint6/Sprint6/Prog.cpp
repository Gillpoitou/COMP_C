#include "Prog.h"

void Prog::build_ASM(ostream &o)
{
      o << ".global main" << endl;
      for (map<string, Function *>::iterator it = functions->begin(); it != functions->end(); ++it)
      {
            //cout << "1" << endl;
            CFG *ir_cfg = new CFG(it->second);
            //cout << "2" << endl;
            it->second->build_IR(ir_cfg);
            //cout << "3" << endl;
            ir_cfg->gen_asm(o);
            //cout << "4" << endl;
      }
}
