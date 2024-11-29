#define _GNU_SOURCE
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

void flag_n(const char *buffer, size_t file_size, int *lines_number);
void flag_b(const char *buffer, size_t file_size, int *lines_number);
void flag_s(const char *buffer, size_t file_size, int *empty_lines);
void flag_v(const char *buffer, size_t file_size);
void flag_e(const char *buffer, size_t file_size);
void flag_E(const char *buffer, size_t file_size);
void flag_T(const char *buffer, size_t file_size);
void flag_t(const char *buffer, size_t file_size);

typedef struct {
  int n;
  int b;
  int e;
  int E;
  int s;
  int t;
  int T;
  int v;
} options;

void parse_options(int argc, char *argv[], options *opt, short *flag_option);
void process_file(const char *file_path, const options *opt, int *lines_number,
                  int *empty_lines);
void read_file(const char *file_path, char **buffer, size_t *file_size,
               short *flag_fopen);
void print_file(const char *buffer, size_t file_size);
void process_flag(const options *opt, const char *buffer, size_t file_size,
                  int *lines_number, int *empty_lines);
