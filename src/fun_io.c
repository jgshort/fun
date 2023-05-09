#include <assert.h>
#include <stdlib.h>
#include <limits.h>

#include "../include/fun_io.h"

int fun_read_file_to_char_buffer(FILE * fp, char ** source, size_t * len) {
  if(fp != NULL) {
    if(fseek(fp, 0L, SEEK_END) == 0) {
      long sz = ftell(fp);
      if(sz < 0) goto err0;

      unsigned long u_sz = (unsigned long)sz;
      *source = calloc(sizeof * source, u_sz + 1);
      if(!(*source)) goto err1;

      if(fseek(fp, 0L, SEEK_SET) != 0) goto err2;

      *len = fread(*source, sizeof(char), u_sz, fp);
      if(ferror(fp) != 0 ) goto err3;

      (*len)++;
      (*source)[*len] = '\0';
    }
  }

  return EXIT_SUCCESS;

err0:
  goto catastrophe;

err1:
  goto catastrophe;

err2:
  goto catastrophe;

err3:
  goto catastrophe;

catastrophe:
  return EXIT_FAILURE;
}

void fun_read_path_to_void_buffer(const char * file_path, void ** out_buf, size_t * out_buf_len) {
  assert(file_path != NULL && out_buf != NULL && out_buf_len != NULL);

  unsigned char * buf = NULL;

  *out_buf = NULL;
  *out_buf_len = 0;

  FILE * src_file = fopen(file_path, "rb");
  SPOOKY_SET_BINARY_MODE(src_file);
  if(!src_file) { abort(); }

  if(fseek(src_file, 0L, SEEK_END) != 0) { abort(); }

  long buf_len = ftell(src_file);
  if(buf_len == -1) { abort(); }
  assert(buf_len < LONG_MAX);

  buf = calloc((size_t)buf_len, sizeof * buf);
  if(!buf) { abort(); }

  if(fseek(src_file, 0L, SEEK_SET) != 0) { abort(); }

  size_t read_len = fread(buf, sizeof(unsigned char), (size_t)buf_len, src_file);
  assert((size_t)read_len == (size_t)buf_len);

  if(ferror(src_file) != 0) { abort(); }

  *out_buf = buf;
  *out_buf_len = read_len;
}

