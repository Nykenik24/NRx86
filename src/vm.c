#include "mvm/vm.h"
#include "mvm/error.h"
#include "mvm/util/logger.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

const char *regstr[] = {[REG_R0] = "R0",
                        [REG_R1] = "R1",
                        [REG_R2] = "R2",
                        [REG_R3] = "R3",
                        [REG_R4] = "R4",
                        [REG_R5] = "R5",
                        [REG_R6] = "R6",
                        [REG_R7] = "R7",
                        [REG_PC] = "PC",
                        [REG_CND] = "CND",
                        [REG_COUNT] = "Register count"};

mvm_vm *new_vm() {
  mvm_vm *vm = malloc(sizeof(mvm_vm));
  vm->reg[REG_PC] = CODE_START;
  return vm;
}

void free_vm(mvm_vm *vm) {
  if (vm) {
    free(vm);
  }
}

uint16_t vm_read_mem(mvm_vm *vm, int idx) {
  if (idx > USEMEM_MAX) {
    mvm_errno = MVM_OUT_OF_USEMEM_BOUNDS;
    errprint("got index %d", idx);
    exit(1);
  }

  return vm->memory[idx];
}

void vm_write_mem(mvm_vm *vm, uint16_t data) {
  if (vm->usemem_counter != USEMEM_MAX) {
    vm->usemem_counter++;
  } else {
    mvm_log(LOG_WARN,
            "Out of usable memory (in VM), overwriting last value (%d at %d).",
            vm->memory[vm->usemem_counter], vm->usemem_counter);
  }

  vm->memory[vm->usemem_counter] = data;
}

void vm_load_code(mvm_vm *vm, uint16_t code[], const size_t len) {
  if (len >= CODE_MAX) {
    mvm_errno = MVM_CODE_LEN_OUT_OF_BOUNDS;
    errprint("length is %lu", len);
    exit(1);
  }

  for (size_t i = 0; i < len; i++) {
    vm->memory[CODE_START + i] = code[i];
  }
  vm->memory[CODE_START + len] = OP_HALT;
}

int run_curr_op(mvm_vm *vm) {
  int op = vm->memory[vm->reg[REG_PC]];
  mvm_log(LOG_INFO, "Found OP %d, running...", op);

  switch ((MVM_OP)op) {
  case OP_LD: {
    vm->reg[REG_PC]++;
    int reg = vm->memory[vm->reg[REG_PC]];
    vm->reg[REG_PC]++;
    int offset = vm->memory[vm->reg[REG_PC]];
    mvm_log(LOG_INFO, "Loading. Register '%d', offset '%d'", reg, offset);

    if (reg >= REG_R7) {
      mvm_errno = MVM_REGISTER_OUT_OF_BOUNDS;
      errprint("got register %d", reg);
      exit(1);
    }

    if (vm->reg[USEMEM_START] + offset > USEMEM_MAX) {
      mvm_errno = MVM_OFFSET_OUT_OF_BOUNDS;
      errprint("max is %d", USEMEM_MAX);
      exit(1);
    }

    mvm_log(LOG_INFO,
            "Setting register '%d' to value '%u' (memory[%d + %d = %d])", reg,
            vm->memory[vm->reg[USEMEM_START] + offset], vm->reg[USEMEM_START],
            offset, vm->reg[USEMEM_START] + offset);
    vm->reg[reg] = vm->memory[vm->reg[USEMEM_START] + offset];
    break;
  }
  case OP_LDI: {
    vm->reg[REG_PC]++;
    int reg = vm->memory[vm->reg[REG_PC]];
    vm->reg[REG_PC]++;
    int imm = vm->memory[vm->reg[REG_PC]];
    mvm_log(LOG_INFO, "Loading immediate. Register %d, IMM '%d'", reg, imm);

    if (reg >= REG_R7) {
      mvm_errno = MVM_REGISTER_OUT_OF_BOUNDS;
      errprint("got register %d", reg);
      exit(1);
    }

    mvm_log(LOG_INFO, "Setting register '%d' to immediate value '%u'", reg,
            imm);
    vm->reg[reg] = imm;
    break;
  }
  default: {
    mvm_errno = MVM_UNRECOGNIZED_OPERATION;
    errprint("operation %d", op);
    exit(1);
    break;
  }
  }

  vm->reg[REG_PC]++;
  return 0;
}

int vm_loop(mvm_vm *vm) {
  while (vm->memory[vm->reg[REG_PC]] != OP_HALT) {
    run_curr_op(vm);
  }
  return 0;
}
