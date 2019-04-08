#include "Block.h"

string Block::build_IR(CFG* ir_cfg){
    
    for (Statement *statm : *statements)
      {
            statm->build_IR(ir_cfg);
      }

      if (rstat)
      {
            rstat->build_IR(ir_cfg);
      }
}