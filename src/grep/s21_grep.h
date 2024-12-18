/*Тебе необходимо разработать утилиту grep:
- Поддержка следующих флагов: `-e`, `-i`, `-v`, `-c`, `-l`, `-n`.
- Для регулярных выражений можно использовать только библиотеки pcre или regex.
- Исходные, заголовочные и make файлы должны располагаться в директории
src/grep/.
- Итоговый исполняемый файл должен располагаться в директории src/grep/ и
называться s21_grep.*/
#define _GNU_SOURCE
#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
} options;

void parse_options(int argc, char *argv[], options *opt, char **templates,
                   short *templates_counter, short *flag_option);
void process_file(const char *file_path, char **templates,
                  short templates_counter, options opt, short files_number,
                  short flag_option);
void read_file(const char *file_path, short *flag_fopen, char **buffer,
               size_t *file_size);
void parse_buffer(const char *file_path, const char *buffer, size_t file_size,
                  char **templates, short templates_counter, options opt,
                  short files_number, int *line_number, short *l_flag,
                  int *counter);