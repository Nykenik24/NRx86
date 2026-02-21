#include "mvm/util/logger.h"
#include <stdarg.h>
#include <stdio.h>

static const char *loglvl_str[4] = {[LOG_INFO] = "\x1b[32mINFO\x1b[0m",
                                    [LOG_DEBUG] = "\x1b[34mDEBUG\x1b[0m",
                                    [LOG_WARN] = "\x1b[33mWARN\x1b[0m",
                                    [LOG_ERROR] = "\x1b[31mERROR\x1b[0m"};

void nrx_log(log_level_t log_level, const char *fmt, ...) {
#ifdef DEBUG
  va_list list;
  va_start(list, fmt);

  printf("\x1b[30m" __DATE__ " " __TIME__ "\x1b[0m [");
  printf("%s", loglvl_str[log_level]);
  printf("]: ");
  vprintf(fmt, list);
  printf("\n");
#endif
}
