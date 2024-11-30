#include "s21_grep.h"

static void find_pattern(const char *file_path, char *line, char **templates,
                         short t_counter, options opt, short files_number,
                         const int *line_number, short *l_flag, int *counter);
static int regexpr(char *template, char *line, options opt);
static short handle_error(const char *temp, char **line, short *error);

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
    fprintf(stderr, "Memory allocation failed\n");
  }
}
void find_pattern(const char *file_path, char *line, char **templates,
                  short templates_counter, options opt, short files_number,
                  const int *line_number, short *l_flag, int *counter) {
  short found = 0;
  short flag = 0;  // хотя бы 1
  for (short i = 0; i < templates_counter; i++) {
    int res = regexpr(templates[i], line, opt);
    if (!res) {
      flag = 1;
    }
  }
  if ((opt.v && !flag) || (!opt.v && flag)) {
    found = 1;
  }
  if (found) {
    (*counter)++;
    if (opt.l && !(*l_flag)) {
      printf("%s\n", file_path);
      *l_flag = 1;
    } else if (opt.n && files_number) {
      printf("%s:%d:%s\n", file_path, *line_number, line);
    } else if (opt.n) {
      printf("%d:%s\n", *line_number, line);
    } else if (!opt.l && !opt.c && !files_number) {
      printf("%s\n", line);
    } else if (files_number && !opt.c && !opt.l) {
      printf("%s:%s\n", file_path, line);
    } else if (files_number && !opt.n && !opt.l && !opt.c) {
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