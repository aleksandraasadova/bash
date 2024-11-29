#include "s21_cat.h"

static void nonprintable(unsigned char);

void process_flag(const options *opt, const char *buffer, size_t file_size,
                  int *lines_number, int *empty_lines) {
  if (opt->n) {
    flag_n(buffer, file_size, lines_number);
  } else if (opt->b) {
    flag_b(buffer, file_size, lines_number);
  } else if (opt->e) {
    flag_e(buffer, file_size);
  } else if (opt->E) {
    flag_E(buffer, file_size);
  } else if (opt->s) {
    flag_s(buffer, file_size, empty_lines);
  } else if (opt->t) {
    flag_t(buffer, file_size);
  } else if (opt->T) {
    flag_T(buffer, file_size);
  } else if (opt->v) {
    flag_v(buffer, file_size);
  } else {
    print_file(buffer, file_size);
  }
}

void print_file(const char *buffer, size_t file_size) {
  for (size_t i = 0; i < file_size; i++) {
    putchar(buffer[i]);
  }
}

void flag_n(const char *buffer, size_t file_size, int *lines_number) {
  for (size_t i = 0; i < file_size; i++) {
    if (i == 0 || buffer[i - 1] == '\n') {
      printf("%6d\t", (*lines_number)++);
    }
    putchar(buffer[i]);
  }
}

void flag_b(const char *buffer, size_t file_size, int *lines_number) {
  for (size_t i = 0; i < file_size; i++) {
    if ((i == 0 || buffer[i - 1] == '\n') && buffer[i] != '\n') {
      printf("%6d\t", (*lines_number)++);
    }
    putchar(buffer[i]);
  }
}

void flag_s(const char *buffer, size_t file_size, int *empty_lines) {
  for (size_t i = 0; i < file_size; i++) {
    if (buffer[i] == '\n') {
      if (i == 0 && *empty_lines > 0) {
      } else if ((i == 0) && (buffer[i + 1] == '\n') && (*empty_lines == 0)) {
        putchar(buffer[i]);
      } else if (*empty_lines == 0) {
        putchar(buffer[i]);
      } else if ((*empty_lines == 1) && (buffer[i - 2] != '\n')) {
        putchar(buffer[i]);
      }
      (*empty_lines)++;
    } else {
      putchar(buffer[i]);
      *empty_lines = 0;
    }
  }
  if (buffer[file_size - 1] == '\n') {
    *empty_lines = 1;
  }
}

void nonprintable(unsigned char current) {
  if ((current < 32 && current != '\n' && current != '\t') || current == 127) {
    if (current == 127) {
      putchar('^');
      putchar('?');
    } else {
      putchar('^');
      putchar(current + 64);
    }
  } else if (current >= 128) {
    putchar('M');
    putchar('-');
    putchar(current - 128);
  } else {
    putchar(current);
  }
}

void flag_v(const char *buffer, size_t file_size) {
  for (size_t i = 0; i < file_size; i++) {
    unsigned char current = (unsigned char)buffer[i];
    nonprintable(current);
  }
}

void flag_e(const char *buffer, size_t file_size) {
  for (size_t i = 0; i < file_size; i++) {
    unsigned char current = (unsigned char)buffer[i];
    if (current == '\n') {
      putchar('$');
    }
    nonprintable(current);
  }
}

void flag_E(const char *buffer, size_t file_size) {
  for (size_t i = 0; i < file_size; i++) {
    if (buffer[i] == '\n') {
      putchar('$');
      putchar('\n');
    } else {
      putchar(buffer[i]);
    }
  }
}

void flag_T(const char *buffer, size_t file_size) {
  for (size_t i = 0; i < file_size; i++) {
    if (buffer[i] == '\t') {
      putchar('^');
      putchar('I');
    } else {
      putchar(buffer[i]);
    }
  }
}

void flag_t(const char *buffer, size_t file_size) {
  for (size_t i = 0; i < file_size; i++) {
    unsigned char current = (unsigned char)buffer[i];
    if (current == '\t') {
      putchar('^');
      putchar('I');
    } else {
      nonprintable(current);
    }
  }
}
