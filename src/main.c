#include "mvm.h"
#include "mvm/assembler/assembler.h"
#include "mvm/assembler/lexer.h"
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

  // const char *source = "LDI &0, i2\n"
  //                      "SUBI &0, i4, &1\n"
  //                      "JNN i1\n";
  const char *source = "NI &0 i2\n"
                       "GGA &2 t9\n";
  mvm_asm_token_list *tokens = lex(source);
  // for (size_t i = 0; i < tokens->tk_num; i++) {
  //   printf("Token '%s', %s\n", tokens->tokens[i]->text,
  //          kindstr[tokens->tokens[i]->kind]);
  // }

  size_t code_len;
  uint16_t *code = assemble(tokens, &code_len);
  // for (size_t i = 0; i < code_len; i++) {
  //   printf("0x%x \n", code[i]);
  // }
  vm_load_code(vm, code, code_len);
  vm_loop(vm);

  free_token_list(tokens);
  free_vm(vm);
  return 0;
}
