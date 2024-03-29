#pragma once

#ifndef FUN_OPTIONS__H
#define FUN_OPTIONS__H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdio.h>

#include "fun_error.h"
#include "fun_log.h"

typedef struct fun_options {
  const char * in_file;             /* -i [path] */
  const char * out_file;            /* -o [path] */
  fun_logging_verbosity verbosity;  /* -v [1..31] */
  bool print_help;                  /* -h */
  bool intermediate;                /* -IL */
  bool translate;                   /* -IT */
  char padding[1];
} fun_options;

void fun_options_print_help(FILE * /* fs */);
fun_ex_errno fun_options_parse(int /* argc */, char ** /* argv */, fun_options * /* options */);

#ifdef __cplusplus
}
#endif

#endif /* FUN_OPTIONS__H */

