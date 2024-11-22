#include "s21_grep.h"

int main(int argc, char *argv[]) {
    options opt = {0};

    //printf("argc is %d", argc);

    char *templates[argc];;
    short t_counter = 0;
    short flag_option = 1;

    if (argc > 2) { //2
        parse_options(argc, argv, &opt, templates, &t_counter, &flag_option);

        while (optind < argc) {
            char **lines = NULL;
            int lines_number = 0;
            short flag_fopen = 1;
            puts("future process func");
            printf("file is %s\n", argv[optind]);
            read_file(argv[optind], &flag_fopen, &lines, &lines_number);
            if (flag_fopen == 1 && flag_option == 1) {
                puts("wow i made it to here");
                printf("delete me later %d\n", lines_number);
                if (lines != NULL) {
                    for (int i = 0; i < lines_number; i++) {
                        free(lines[i]);
                    }
                }
                free(lines);
            }
            optind++;
        }
    } else {
        printf("Invalid input\n");
    }
    return 0;
}


