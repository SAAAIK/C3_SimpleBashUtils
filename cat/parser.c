#include "parser.h"

int parse_param(int argc, char *argv[], char *shortOpt,
                struct option *long_options, config *conf) {
  int res;
  int error = 0;
  int idx = 0;

  while ((res = getopt_long(argc, argv, shortOpt, long_options, &idx)) != -1) {
    switch (res) {
      case 'b':
        conf->b = 1;
        break;
      case 'e':
        conf->e = 1;
        conf->v = 1;
        break;
      case 'E':
        conf->e = 1;
        break;
      case 'n':
        conf->n = 1;
        break;
      case 't':
        conf->t = 1;
        conf->v = 1;
        break;
      case 'T':
        conf->t = 1;
        break;
      case 'v':
        conf->v = 1;
        break;
      case 's':
        conf->s = 1;
        break;
      case '?':
        print_flag_error(argv, optind);
        // printf ("cat: illegal option --%s\n", optarg);
        error = 1;
        break;
      default:
        error = 1;
        break;
    }
  }
  if (conf->b) {
    conf->n = 0;
  }
  if (error) {
    return 1;
  }
  return 0;
}
