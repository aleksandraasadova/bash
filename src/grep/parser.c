#include "s21_grep.h"

static void conflicting_pairs(options *);
static struct option long_options[] = {{0, 0, 0, 0}};

void parse_options(int argc, char **argv, options *opt, char **templates,
                   short *t_counter, short *flag_option) {
  int flag;
  while ((flag = getopt_long(argc, argv, "e:ivcln", long_options, NULL)) !=
         -1) {
    switch (flag) {
      case 'e':
        opt->e = 1;
        templates[*t_counter] = optarg;
        (*t_counter)++;
        break;
      case 'i':
        opt->i = 1;
        break;
      case 'v':
        opt->v = 1;
        break;
      case 'n':
        opt->n = 1;
        break;
      case 'c':
        opt->c = 1;
        opt->n = 0;
        break;
      case 'l':
        opt->l = 1;
        opt->n = 0;
        opt->c = 0;
        break;
      default:
        (*flag_option) = 0;
        break;
    }
  }
  conflicting_pairs(opt);
  if (!opt->e && (optind < argc)) {  // от ошибки сегментации
    templates[*t_counter] = argv[optind];
    (*t_counter)++;
    optind++;
  }
  if (*t_counter == 0) {
    fprintf(stderr, "no templates in your input\n");
  }
}

void conflicting_pairs(options *opt) {
  if (opt->c && opt->l) {
    opt->c = 0;
  }
  if (opt->c && opt->n) {
    opt->n = 0;
  }
  if (opt->n && opt->l) {
    opt->n = 0;
  }
}