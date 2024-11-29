#include "s21_grep.h"

static short check_files_number(int, int);

int main(int argc, char *argv[]) {
  options opt = {0};
  // char *templates[argc];        // !!
  char **templates = malloc(argc * sizeof(char *));
  short templates_counter = 0;  // !!
  short flag_option = 1;

  if (argc > 2) {  // 2
    parse_options(argc, argv, &opt, templates, &templates_counter,
                  &flag_option);
    // printf("Template: %d\n", templates_counter);
    short files_number = check_files_number(optind, argc);

    while (optind < argc) {
      process_file(argv[optind], templates, templates_counter, opt,
                   files_number, flag_option);
      optind++;
    }
    free(templates);
  } else {
    printf("Invalid input\n");
  }
  return 0;
}

short check_files_number(int optind, int argc) {
  short res = 0;
  if (optind < argc - 1) {
    res = 1;
  }
  return res;
}
