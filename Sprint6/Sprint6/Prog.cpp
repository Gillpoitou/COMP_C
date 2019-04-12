#include "Prog.h"

void Prog::build_ASM(ostream &o)
{
      o << ".global main" << endl;
      for (map<string, Function *>::iterator it = functions->begin(); it != functions->end(); ++it)
      {
            CFG *ir_cfg = new CFG(it->second);
            it->second->build_IR(ir_cfg);
            ir_cfg->gen_asm(o);
      }
}
