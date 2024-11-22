#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

void flag_n(char *buffer, size_t file_size, int *lines_number);
void flag_b(char *buffer, size_t file_size, int *lines_number);
void flag_s(char *buffer, size_t file_size, int *empty_lines);
void flag_v(char *buffer, size_t file_size);
void flag_e(char *buffer, size_t file_size);
void flag_E(char *buffer, size_t file_size);
void flag_T(char *buffer, size_t file_size);
void flag_t(char *buffer, size_t file_size);

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
void process_file(const char *file_path, options *opt, int *lines_number, int *empty_lines);
void read_file(const char *file_path, char **buffer, size_t *file_size, short *flag_fopen);
void print_file(char *buffer, size_t file_size);
void process_flag(options *opt, char *buffer, size_t file_size, int *lines_number, int *empty_lines);

