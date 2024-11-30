#include "s21_grep.h"

void process_file(const char *file_path, char **templates,
                  short templates_counter, options opt, short files_number,
                  short flag_option) {
  short flag_fopen = 1;
  char *buffer = NULL;
  size_t file_size;
  read_file(file_path, &flag_fopen, &buffer, &file_size);
  if (flag_fopen == 1 && flag_option == 1) {
    short l_flag = 0;
    int line_number = 0;
    int counter = 0;
    parse_buffer(file_path, buffer, file_size, templates, templates_counter,
                 opt, files_number, &line_number, &l_flag, &counter);
    line_number = 0;
    free(buffer);
    if (opt.c) {
      if (files_number) {
        printf("%s:%d\n", file_path, counter);
      } else {
        printf("%d\n", counter);
      }
    }
  }
}
