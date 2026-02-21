#ifndef _VM_H
#define _VM_H

#include <stdint.h>
#define MEMORY_MAX (1 << 16)

enum {
  REG_R0,
  REG_R1,
  REG_R2,
  REG_R3,
  REG_R4,
  REG_R5,
  REG_R6,
  REG_R7,
  REG_PC,   /* Program counter */
  REG_CND,  /* Condition */
  REG_COUNT /* Total number of registers */
};

enum { OP_HALT, OP_LD, OP_ST };

typedef struct {
  uint16_t memory[MEMORY_MAX];
  uint16_t reg[REG_COUNT];
} nrx_vm;

#endif
