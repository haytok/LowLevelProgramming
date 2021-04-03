#ifndef INSTRUCTION_H_
#define INSTRUCTION_H_

#include "emulator.h"

/* 命令セットの初期化関数 */
void init_instructions(void);

typedef void instruction_func_t(Emulator*);

/* x86命令の配列、opecode番目の関数がx86の
   opcodeに対応した命令となっている */
extern instruction_func_t* instructions[256];

#endif
