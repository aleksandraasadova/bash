#include "s21_cat.h"

static struct option long_options[] = {{"number-nonblank", no_argument, 0, 'b'},
                                       {"number", no_argument, 0, 'n'},
                                       {"squeeze-blank", no_argument, 0, 's'},
                                       {NULL, 0, NULL, 0}};

void parse_options(int argc, char *argv[], options *opt, short *flag_option) {
  int flag;
  while ((flag = getopt_long(argc, argv, "nbsetTvE", long_options, NULL)) !=
         -1) {
    switch (flag) {
      case 'n':
        opt->n = 1;
        break;
      case 'b':
        opt->b = 1;
        opt->n = 0;
        break;
      case 's':
        opt->s = 1;
        break;
      case 'e':
        opt->e = 1;
        break;
      case 't':
        opt->t = 1;
        break;
      case 'v':
        opt->v = 1;
        break;
      case 'T':
        opt->T = 1;
        break;
      case 'E':
        opt->E = 1;
        break;
      default:
        (*flag_option) = 0;
        break;
    }
  }
}