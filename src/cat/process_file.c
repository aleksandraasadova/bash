#include "s21_cat.h"

void process_file(const char *file_path, options *opt, int *lines_number,
                  int *empty_lines) {
  char *buffer = NULL;
  size_t file_size;
  short flag_fopen = 1;
  short *ptr_flag = &flag_fopen;
  read_file(file_path, &buffer, &file_size, ptr_flag);
  if (flag_fopen != 0) {
    process_flag(opt, buffer, file_size, lines_number, empty_lines);
    free(buffer);
  }
}