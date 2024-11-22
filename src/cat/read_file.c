#include "s21_cat.h"

static size_t get_file_size(FILE *);
static void write_file_to_array(FILE *fp, char *buffer, size_t file_size);

// открытие файла
void read_file(const char *file_path, char **buffer, size_t *file_size,
               short *flag_fopen) {

  FILE *fp = fopen(file_path, "r");

  if (fp != NULL) {
    *file_size = get_file_size(fp);
    if (*file_size != 0) {
      *buffer = malloc(*file_size);
      if (*buffer != NULL) 
      write_file_to_array(fp, *buffer, *file_size);
      fclose(fp);
    } else {
      *flag_fopen = 0;
    }
  } else {
    *flag_fopen = 0;
    printf("cat: %s no such file or directory\n", file_path);
  }
}

size_t get_file_size(FILE *fp) {
  size_t file_size = 0;
  fseek(fp, 0, SEEK_END);
  file_size = ftello(fp);
  fseek(fp, 0, SEEK_SET);  // fp - указатель на начало файла
  return file_size;
}

void write_file_to_array(FILE *fp, char *buffer, size_t file_size) {
  size_t index = 0;
  int current;
  while (((current = fgetc(fp)) != EOF) && (index < file_size)) {
    buffer[index++] = (char)current;
  }
} 
