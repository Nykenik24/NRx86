// mvm_error.h
#ifndef _MVM_ERROR_H
#define _MVM_ERROR_H

typedef enum {
  MVM_NOERR,
  MVM_UNRECOGNIZED_OPERATION,
  MVM_OFFSET_OUT_OF_BOUNDS,
  MVM_REGISTER_OUT_OF_BOUNDS,
  MVM_CODE_LEN_OUT_OF_BOUNDS,
  MVM_OUT_OF_USEMEM_BOUNDS
} MVM_ERRNO;

extern MVM_ERRNO mvm_errno;
extern const char *mvm_errstr[];

void errprint(const char *fmt, ...);

#endif
