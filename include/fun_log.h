#pragma once

#ifndef FUN_LOG__H
#define FUN_LOG__H

typedef enum fun_logging_verbosity {
  FLV_UNSET   = 0x0000,
  FLV_ERROR   = 0x0001,
  FLV_WARNING = 0x0002,
  FLV_INFO    = 0x0004,
  FLV_DEBUG   = 0x0008,
  FLV_SILENT  = 0x0010,
  FLV_EOE     = FLV_SILENT | FLV_ERROR | FLV_WARNING | FLV_INFO | FLV_DEBUG
} fun_logging_verbosity;

fun_logging_verbosity fun_set_logging_verbosity(long int /* in */, fun_logging_verbosity /* verbosity */);
void fun_print_logging_verbosity(fun_logging_verbosity /* verbosity */);

#endif /* FUN_LOG__H */

