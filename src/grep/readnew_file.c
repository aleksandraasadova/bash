#include "s21_grep.h"

static size_t get_file_size(FILE *);
static void write_file_to_array(FILE *, char *, size_t);
static char **array_of_lines(char *, size_t, int *);

void read_file(const char *file_path, short *flag_fopen, char ***lines, int *lines_number) {

    //char *buffer = NULL; 
    //char **lines = NULL;
    //int lines_number;
    //size_t len = 0;

    FILE *fp = fopen(file_path, "r");

    if (fp != NULL) {
        size_t file_size = get_file_size(fp);
        if (file_size != 0) {
            char *buffer = NULL; 
            buffer = malloc(file_size);
            write_file_to_array(fp, buffer, file_size);
            fclose(fp);
            *lines = array_of_lines(buffer, file_size, lines_number); //меняем указатель 
            free(buffer);
            buffer = NULL;
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

char **array_of_lines(char *buffer, size_t file_size, int *lines_number) {
    char **lines = malloc(file_size *sizeof(char *)); // память
    char *line = malloc(file_size);
    size_t lines_ind = 0; 
    //size_t buffer_ind = 0; 
    size_t line_ind = 0;

    for (size_t i = 0; i < file_size; i++) {
        if (buffer[i] != '\n' && buffer[i] != '\0') {
            line[line_ind++] = buffer[i];
        } else {
            if (line_ind > 0) {
                (*lines_number)++;
                line[line_ind] = '\0';
                lines[lines_ind] = malloc(line_ind + 1); // память
                strcpy(lines[lines_ind], line);
                lines_ind++;
                line_ind = 0;
            }
        } 
    }
    if (line_ind > 0) {
        (*lines_number)++;
        line[line_ind] = '\0';
        lines[lines_ind] = malloc(line_ind +1 );
        strcpy(lines[lines_ind], line);
        lines_ind++;
    }
    free(line);

    return lines; 
}

