#include "mvm.h"
#include "mvm/util/logger.h"
#include <stdio.h>

int main(void) {
#ifdef DEBUG
  printf(MVM_BUILD "\n");
  printf("By " MVM_AUTHORS "\n");
  printf("\n\n");
#endif
  return 0;
}
