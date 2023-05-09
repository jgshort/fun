#include <assert.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <ctype.h>

#include "fun_options.h"
#include "fun_io.h"
#include "fun_il.h"

#define IL_CHECK(in, inst) (memcmp((in), inst, (sizeof(inst) - 1)) == 0)

#define IL_CONSUME_WS(in) do { \
  while(isspace(*c)) { \
    if(*c == '\n' || (*c == '\r' && *(c + 1) == '\n')) {  \
      row++; \
      col = 1; \
    } else { \
      col++; \
    } \
    c++; \
  } } while(false) \

typedef enum fun_il_instruction {
  FII_UNSET,
  FII_NOP,
  FII_MOV,
  FII_XOR,
  FII_SYSCALL,
  FII_END,
  FII_EOE
} fun_il_instruction;

typedef struct fun_instruction_code {
  fun_il_instruction op;
  /* TODO: Source */
  /* TODO: Destination */
} fun_instruction_code;

static const char * fun_instruction_to_string(fun_il_instruction op);

void fun_il_lex(const fun_options * options) {
  assert(options->in_file);
  assert(options->intermediate);

  void * buf = NULL;
  size_t buf_len = 0;
  fun_read_path_to_void_buffer(options->in_file, &buf, &buf_len);

  const char * c = (const char *)buf;
  const char * buf_end = c + buf_len;
 
  long int row = 1;
  long int col = 1;

  size_t code_len = 16, current_offset = 0;
  fun_instruction_code * code = calloc(code_len, sizeof * code);
  fun_instruction_code * code_end = code + code_len;
  fun_instruction_code * current = code;
  
  do {
    IL_CONSUME_WS(c);

    if(IL_CHECK(c, "nop")) { goto il_nop; }
    if(IL_CHECK(c, "mov")) { goto il_mov; }
    if(IL_CHECK(c, "xor")) { goto il_xor; } 
    if(IL_CHECK(c, "sys")) { goto il_sys; }
    goto next;

il_nop: current->op = FII_NOP;
    goto next_instruction;

il_mov: current->op = FII_MOV;
    goto next_instruction;

il_xor: current->op = FII_XOR;
    goto next_instruction;

il_sys: current->op = FII_SYSCALL;
    goto next_instruction;

next_instruction:
    if(current + 1 >= code_end) {
      code_len = code_len * 2;
      fun_instruction_code * temp = realloc(code, code_len * sizeof * temp);
      if(!temp) { abort(); }
      code = temp;
      code_end = code + code_len;
      current = code + current_offset;
    }

    current++; current_offset++;
    goto next;

next:
    c++; col++;
  } while(c < buf_end);

  fun_instruction_code * output = code;
  do {
    fprintf(stdout, "FOUND %s\n", fun_instruction_to_string(output->op)); 
    output++;
  } while(output < code_end);


  free(code), code = NULL;
  free(buf), buf = NULL;
}

static const char * fun_instruction_to_string(fun_il_instruction op) {
  switch(op) {
    case FII_NOP: return "nop";
    case FII_MOV: return "mov";
    case FII_XOR: return "xor";
    case FII_END: return "end";
    case FII_SYSCALL: return "sys";
    case FII_UNSET:
    case FII_EOE:
    default: return "<nil>";
  }
}

void fun_translate(const fun_options * options) {
  (void)options;
}
