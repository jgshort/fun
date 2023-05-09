#ifndef FUN_IO__H
#define FUN_IO__H

#include <stdio.h>

/* From: http://www.zlib.net/zlib_how.html */
/* This is an ugly hack required to avoid corruption of the input and output
 * data on Windows/MS-DOS systems. Without this, those systems would assume
 * that the input and output files are text, and try to convert the end-of-line
 * characters from one standard to another. That would corrupt binary data, and
 * in particular would render the compressed data unusable. This sets the input
 * and output to binary which suppresses the end-of-line conversions.
 * SET_BINARY_MODE() will be used later on stdin and stdout, at the beginning
 * of main():
*/
#if defined(MSDOS) || defined(OS2) || defined(WIN32) || defined(__CYGWIN__)
#include <fcntl.h>
#include <io.h>
#define SPOOKY_SET_BINARY_MODE(file) { setmode(fileno((file)), O_BINARY) }
#else
#define SPOOKY_SET_BINARY_MODE(file)
#endif /* >> if defined(MSDOS) || ... */

int fun_read_file_to_char_buffer(FILE * /* fp */, char ** /* source */, size_t * /* len */);
void fun_read_path_to_void_buffer(const char * /* file_path */, void ** /* out_buf */, size_t * /* out_buf_len */);

#endif /* FUN_IO__H */

