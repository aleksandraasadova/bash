#include "s21_cat.h"

int main(int argc, char *argv[]) {
  options opt = {0};
  int lines_number = 1;
  int empty_lines = 0;
  short flag_option = 1;

  if (argc > 1) {
    parse_options(argc, argv, &opt, &flag_option);
    if (flag_option) {
      while (optind < argc) {
        process_file(argv[optind], &opt, &lines_number, &empty_lines);
        optind++;
      }
    }
  } else {
    printf("Usage: [OPTION]... [FILE]...\n");
  }
  return 0;
}
