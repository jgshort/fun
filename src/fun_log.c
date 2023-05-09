#include <stdlib.h>
#include <stdio.h>

#include "../include/fun_log.h"

fun_logging_verbosity fun_set_logging_verbosity(long int in, fun_logging_verbosity verbosity) {
  long int in_to_flv = FLV_UNSET;

  if((in & FLV_DEBUG) == FLV_DEBUG) { in_to_flv |= verbosity | FLV_DEBUG; }
  if((in & FLV_INFO) == FLV_INFO) { in_to_flv |= verbosity | FLV_INFO; }
  if((in & FLV_WARNING) == FLV_WARNING) { in_to_flv |= verbosity | FLV_WARNING; }
  if((in & FLV_ERROR) == FLV_ERROR) { in_to_flv |= verbosity | FLV_ERROR; }
  if((in & FLV_SILENT) == FLV_SILENT) { in_to_flv |= verbosity | FLV_SILENT; }

  return (fun_logging_verbosity)in_to_flv;
}

void fun_print_logging_verbosity(fun_logging_verbosity verbosity) {
  if((verbosity & FLV_SILENT) != 0) { fprintf(stdout, "[silent]"); }
  if((verbosity & FLV_ERROR) != 0) { fprintf(stdout, "[error]"); }
  if((verbosity & FLV_WARNING) != 0) { fprintf(stdout, "[warning]"); }
  if((verbosity & FLV_INFO) != 0) { fprintf(stdout, "[info]"); }
  if((verbosity & FLV_DEBUG) != 0) { fprintf(stdout, "[debug]"); }
}


