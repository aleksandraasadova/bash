#include "s21_grep.h"

static void parse_buffer(const char *file_path, char *buffer, size_t file_size, char **templates, short templates_counter, options opt, short files_number, int *line_number, short *l_flag, int *counter);
static void find_pattern(const char *file_path, char *line, char **templates,
                         short t_counter, options opt, short files_number,
                         int *line_number, short *l_flag, int *counter);
static int regexpr(char *template, char *line, options opt);

void process_file(const char *file_path, char **templates, short templates_counter, options opt, short files_number, short flag_option) {
    short flag_fopen = 1;
    //printf("file is %s\n", argv[optind]);
    char *buffer = NULL;
    size_t file_size;
    read_file(file_path, &flag_fopen, &buffer, &file_size);
    if (flag_fopen == 1 && flag_option == 1) {
        //puts("wow i made it to here");
        short l_flag = 0;
        int line_number = 0;
        int counter = 0;
        parse_buffer(file_path, buffer, file_size, templates,
                     templates_counter, opt, files_number, &line_number,
                     &l_flag, &counter);
        free(buffer);
        if (opt.c) {
          printf("%d\n", opt.c);
        }
    }
}

void parse_buffer(const char *file_path, char *buffer, size_t file_size,
                  char **templates, short templates_counter, options opt,
                  short files_number, int *line_number, short *l_flag,
                  int *counter) {
  char *line = NULL;
  int line_ind = 0;
  for (size_t i = 0; i < file_size; i++) {
    if (buffer[i] != '\n' && buffer[i] != '\0') {
      line = realloc(line, line_ind + 1);
      line[line_ind++] = buffer[i];
    } else {
      if (line_ind > 0) {
        line = realloc(line, line_ind + 1);
        line[line_ind] = '\0';
        (*line_number)++;
        line_ind = 0;
        find_pattern(file_path, line, templates, templates_counter, opt,
                     files_number, line_number, l_flag, counter);
        free(line);
        line = NULL;
        line_ind = 0;
      }
    }
  }
  if (line_ind > 0) {
    line = realloc(line, line_ind + 1);
    line[line_ind] = '\0';
    (*line_number)++;
    find_pattern(file_path, line, templates, templates_counter, opt,
                 files_number, line_number, l_flag, counter);
    free(line);
  }
}

void find_pattern(const char *file_path, char *line, char **templates,
                  short templates_counter, options opt, short files_number,
                  int *line_number, short *l_flag, int *counter) {
  short res_flag = 0;
  for (short i = 0; i < templates_counter; i++) {
    int res = regexpr(templates[i], line, opt);
    if ((!res_flag) && (!res)) {
      res_flag = 1;
    }
    // regexepr возвращает 0 в случае если шаблон найден 0 - ок
    if (opt.v && res_flag) {
      res = 1;
    } else if (opt.v && !res_flag) {
      res = 0;
    }
    if (!res) {
      (*counter)++;
    }
    if (opt.l && !res && !(*l_flag)) {
      printf("%s\n", file_path);
      *l_flag = 1;
    }
    if (!res && opt.n && files_number) {
      printf("%s:%d:%s\n", file_path, *line_number, line);
    } else if (!res && opt.n) {
      printf("%d:%s\n", *line_number, line);
    } else if (!res && files_number) {
      printf("%s:%s\n", file_path, line);
    } else if (!res) {
      printf("%s\n", line);
    }
  }
}

int regexpr(char *template, char *line, options opt) {
  int flags = (opt.i) ? REG_ICASE | REG_EXTENDED : REG_EXTENDED;
  regex_t preg;
  regcomp(&preg, template, flags);
  int res = regexec(&preg, line, 0, 0, 0);
  regfree(&preg);
  return res;  // 0 = found
}
