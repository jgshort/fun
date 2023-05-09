#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#include "config.h"
#include "fun_error.h"
#include "fun_string.h"
#include "fun_log.h"
#include "fun_options.h"

void fun_options_print_help(FILE * fs) {
  fprintf(fs, "%s %s\n", PACKAGE_NAME, PACKAGE_VERSION);
  fprintf(fs, "Supported command line arguments:\n");
  fprintf(fs, "\t-h        : Print this help message.\n");
  fprintf(fs, "\t-i [path] : Input file path. Required.\n");
  fprintf(fs, "\t-o [path] : Output file path. Required. Existing output will be overwritten.\n");
  fprintf(fs, "\t-v [1 - 5]: Logging verbosity; default is ERROR. Optional.\n");
  fprintf(fs, "\t-IL       : compile [input] to intermediate assembly\n");
  fprintf(fs, "\t-IT       | translate [input] to C\n");
}

fun_ex_errno fun_options_parse(int argc, char ** argv, fun_options * options) {
  if(argc <= 1) { 
    fun_options_print_help(stderr);
    exit(EXIT_FAILURE); 
  }

  const char * verbosity_argument = NULL;
  for(int i = 0; i < argc; i++) {
    if(argv[i][0] == '-') {
      if(i + 1 > argc) { goto err0; }
      switch (argv[i][1]) {
        case 'h': options->print_help = true; break;
        case 'I':
          {
            if(argv[i][2] == 'L') { /* -IL */
              options->intermediate = true;
            } else if(argv[i][2] == 'T') { /* -IT */
              options->translate = true;
            }
          }
          break;
        case 'i':
          {
            if(!argv[i + 1]) { goto err1; }
            options->in_file = strndup(argv[i + 1], FUN_STRING_MAX_LEN);
          }
          break;
        case 'o':
          {
            if(!argv[i + 1]) { goto err2; }
            options->out_file = strndup(argv[i + 1], FUN_STRING_MAX_LEN);
          }
          break;
        case 'v':
          {
            errno = 0;
            verbosity_argument = argv[i + 1];
            long int verbosity = strtol(argv[i + 1], NULL, 0);
            if(errno == ERANGE || verbosity <= FLV_UNSET || verbosity > FLV_EOE) { 
              goto err3;
            }
            errno = 0;
            options->verbosity = fun_set_logging_verbosity(verbosity, options->verbosity); 
          }
          break;
        default:
          goto err0;
      }
    }
  }

  if(options->print_help) {
    fun_options_print_help(stdout);
    exit(EXIT_SUCCESS);
  }

  if(!options->out_file) { goto err2; }

  if(!options->in_file) { goto err1; }
  if(access(options->in_file, F_OK) != 0) { goto err4; }

  assert(options->in_file);
  assert(options->out_file);

  if(options->verbosity == FLV_UNSET) { options->verbosity = FLV_ERROR; }
  if(options->verbosity & FLV_INFO) {
    fprintf(stdout, "Set logging verbosity level to ");
    fun_print_logging_verbosity(options->verbosity);
    fprintf(stdout, "\n");
    if(options->intermediate ) {
      fprintf(stdout, "Assembling IL [%s] to [%s]\n", options->in_file, options->out_file);
    } else if(options->translate) {
      fprintf(stdout, "Translating [%s] to [%s]\n", options->in_file, options->out_file);
    }
  }

  return FUN_EX_SUCCESS;

err4:
  fprintf(stderr, "ERROR! Input file does not exist!\n");
  goto err0;

err3:
  fprintf(stderr, "ERROR! Invalid verbosity argument (-v %s):\n\n", verbosity_argument);
  fprintf(stderr, "-v [numeric(1..%i)]: Verbosity is an integer mask OR'd together as follows:\n", FLV_SILENT | FLV_ERROR | FLV_WARNING | FLV_INFO | FLV_DEBUG);
  fprintf(stderr, "\t%i - Log error messages (this is the default logging level).\n", FLV_ERROR);
  fprintf(stderr, "\t%i - Log warning messages.\n", FLV_WARNING);
  fprintf(stderr, "\t%i - Log informative messages.\n", FLV_INFO);
  fprintf(stderr, "\t%i - Log diagnostic messages.\n", FLV_DEBUG);
  fprintf(stderr, "\t%i - Silent (no logging at all).\n\n", FLV_SILENT);
  fprintf(stderr, "EXAMPLES\n\n");
  fprintf(stderr, "The following examples set the logging level to [error][info], which will\nlog both error and informative messages:\n\n");
  fprintf(stderr, "\t./" PACKAGE_NAME " -v %i      # (inline 1 OR 4)\n", FLV_ERROR | FLV_INFO);
  fprintf(stderr, "\t./" PACKAGE_NAME " -v %i -v %i # (multiple OR'd arguments)\n", FLV_ERROR, FLV_INFO);
  goto err0;

err2:
  fprintf(stderr, "ERROR! Missing required command line argument, '-o [path]':\n");
  fprintf(stderr, "-o [path]: Output file path is required.\n");
  goto err0;

err1:
  fprintf(stderr, "ERROR! Missing command line argument, '-i [path]':\n");
  fprintf(stderr, "-i [path]: Input file path is required.\n");
  goto err0;

err0:
  return -1;
}

