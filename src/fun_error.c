#include <assert.h>
#include <stdlib.h>
#include <errno.h>

#include "fun_bad.h"
#include "fun_error.h"

#define FUN_EX_MAX_ALLOCS 2048

const fun_ex_errno FUN_EX_SUCCESS = 0;

static fun_ex * fun_ex_allocated_exes[FUN_EX_MAX_ALLOCS];
static size_t fun_ex_next_alloc = 0;

void fun_ex_shutdown() {
  for(size_t i = 0; i < fun_ex_next_alloc; i++) {
    free(fun_ex_allocated_exes[i]), fun_ex_allocated_exes[i] = NULL;
  }
}

fun_ex_errno fun_new_ex(long line, const char * file, const char * msg, const fun_ex * inner, const fun_ex ** out_ex) {
  fun_ex * temp = calloc(1, sizeof * temp);
  if(!temp) { abort(); }

  temp->line = line;
  temp->file = file;
  temp->msg = msg;
  temp->inner = inner;

  *out_ex = temp;

  assert(fun_ex_next_alloc < FUN_EX_MAX_ALLOCS);
  if(fun_ex_next_alloc >= FUN_EX_MAX_ALLOCS) { abort(); }
  
  fun_ex_allocated_exes[fun_ex_next_alloc] = temp;
  fun_ex_next_alloc++;

  return FUN_EX_SUCCESS;
}

