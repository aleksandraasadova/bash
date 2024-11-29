#include "s21_grep.h"

static void parse_buffer(const char *file_path, const char *buffer,
                         size_t file_size, char **templates,
                         short templates_counter, options opt,
                         short files_number, int *line_number, short *l_flag,
                         int *counter);
static void find_pattern(const char *file_path, char *line, char **templates,
                         short t_counter, options opt, short files_number,
                         const int *line_number, short *l_flag, int *counter);
static int regexpr(char *template, char *line, options opt);
static short handle_error(const char *temp, char **line, short *error);

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
    if (opt.c && files_number) {
      printf("%s:%d\n", file_path, counter);
    } else if (opt.c) {
      printf("%d\n", counter);
    }
  }
}

void parse_buffer(const char *file_path, const char *buffer, size_t file_size,
                  char **templates, short templates_counter, options opt,
                  short files_number, int *line_number, short *l_flag,
                  int *counter) {
  char *line = NULL;
  int line_ind = 0;
  short error = 0;
  for (size_t i = 0; i < file_size; i++) {
    if (buffer[i] != '\n' && buffer[i] != '\0') {
      char *temp = realloc(line, line_ind + 1);
      error = handle_error(temp, &line, &error);
      if (error) {
      } else {
        line = temp;
        line[line_ind++] = buffer[i];
      }
    } else {
      // if (line_ind > 0)
      char *temp = realloc(line, line_ind + 1);
      error = handle_error(temp, &line, &error);
      if (error) {
      } else {
        line = temp;
        line[line_ind] = '\0';
        (*line_number)++;
        find_pattern(file_path, line, templates, templates_counter, opt,
                     files_number, line_number, l_flag, counter);
        free(line);
        line = NULL;
        line_ind = 0;
      }
    }
  }
  if (line_ind > 0) {
    char *temp = realloc(line, line_ind + 1);
    error = handle_error(temp, &line, &error);
    if (error) {
    } else {
      line = temp;
      line[line_ind] = '\0';
      (*line_number)++;
      find_pattern(file_path, line, templates, templates_counter, opt,
                   files_number, line_number, l_flag, counter);
      free(line);
    }
  }
  if (error) {
    fprintf(stderr, "Ошибка при выделении памяти\n");
  }
}

void find_pattern(const char *file_path, char *line, char **templates,
                  short templates_counter, options opt, short files_number,
                  const int *line_number, short *l_flag, int *counter) {
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
      // puts("here");
      printf("%s:%d:%s\n", file_path, *line_number, line);
    } else if (!res && opt.n) {
      // puts("here2");
      printf("%d:%s\n", *line_number, line);
    } else if (!res && !opt.l && !opt.c && !files_number) {
      // puts("here3");
      printf("%s\n", line);
    } else if (!res && files_number && !opt.c && !opt.l) {
      // puts("here4");
      printf("%s:%s\n", file_path, line);
    } else if (!res && files_number && !opt.n && !opt.l && !opt.c) {
      // puts("here5");
      printf("%s:%s\n", file_path, line);
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
short handle_error(const char *temp, char **line, short *error) {
  if (temp == NULL) {
    if (*line) {
      free(*line);
      *line = NULL;
    }
    *error = 1;
  }
  return *error;
}