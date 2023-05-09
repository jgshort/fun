#pragma once

#ifndef FUN_ERROR__H
#define FUN_ERROR__H

#ifdef __cplusplus
extern "C" {
#endif

typedef int fun_ex_errno;

typedef struct fun_ex fun_ex;

typedef struct fun_ex {
  long line;
  const char * file;
  const char * msg;
  const fun_ex * inner;
} fun_ex;

extern const fun_ex * const FUN_EX_ALLOC_ERR;

fun_ex_errno fun_new_ex(long /* line */, const char * /* file */, const char * /* msg */, const fun_ex * /* inner */, const fun_ex ** /* out_ex */);

void fun_ex_shutdown();

extern const fun_ex_errno FUN_EX_SUCCESS;

#ifdef __cplusplus
}
#endif

#endif /* FUN_ERROR__H */

