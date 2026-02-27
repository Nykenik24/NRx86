#include "mvm.h"
#include "mvm/util/logger.h"
#include "mvm/vm.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

int main(void) {
#ifdef DEBUG
  printf(MVM_BUILD "\n");
  printf("By " MVM_AUTHORS "\n");
  printf("\n\n");
#endif

  mvm_vm *vm = new_vm();
  // clang-format off
  uint16_t code[] = {
      OP_LDI, REG_R0, 6,
      OP_HALT
  };
  // clang-format on
  size_t code_len = sizeof(code) / sizeof(code[0]);
  vm_load_code(vm, code, code_len);
  vm_loop(vm);

  mvm_reg_dump(vm);
  mvm_mem_dump(vm, 16);

  free_vm(vm);
  return 0;
}
