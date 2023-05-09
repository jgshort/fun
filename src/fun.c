#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <errno.h>

#include "config.h"
#include "fun_bad.h"
#include "fun_error.h"
#include "fun_string.h"
#include "fun_log.h"
#include "fun_options.h"
#include "fun_il.h"

int main(int argc, char ** argv) {
  atexit(fun_ex_shutdown);

  setlocale(LC_ALL, "");

  fun_options options = { 0 };
  if(fun_options_parse(argc, argv, &options) != FUN_EX_SUCCESS) { goto err0; }

  if(options.intermediate) {
    fun_il_lex(&options);
  } else if(options.translate) {
    fun_translate(&options);
  }

  return EXIT_SUCCESS;
err0:
  return EXIT_FAILURE;
}

