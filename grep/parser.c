#include "parser.h"

int parse(int argc, char *argv[], config *conf, int *f) {
  int res, nofl = 1, len = 0, def = 0;
  int empty = 1;
  char *shortOpt = "e:ivclnhsf:o";

  while ((res = getopt_long(argc, argv, shortOpt, NULL, NULL)) != -1 && nofl) {
    switch (res) {
      case 'e':
        conf->e = 1;
        len = strlen(optarg);
        conf->reg = realloc(conf->reg, strlen(conf->reg) + len + 2);
        strcat(conf->reg, optarg);
        strcat(conf->reg, "|");
        break;
      case 'i':
        conf->i = 1;
        break;
      case 'c':
        conf->c = 1;
        break;
      case 'l':
        conf->l = 1;
        break;
      case 'n':
        conf->n = 1;
        break;
      case 'v':
        conf->v = 1;
        break;
      case 'h':
        conf->h = 1;
        break;
      case 's':
        conf->s = 1;
        break;
      case 'f':
        conf->f = 1;
        empty = regopen(conf, optarg);
        break;
      case 'o':
        conf->o = 1;
        break;
      default:
        def = 1;
        nofl = 0;
    }
  }
  if (conf->c || conf->l) conf->n = 0;
  // if (conf->v) conf->o = 0;
  *f = optind;

  if (empty == 0) {
    nofl = 2;
  } else if (def == 0) {
    nofl = 1;
  } else {
    nofl = 0;
  }

  return nofl;
}

int regopen(config *conf, char *fileName) {
  FILE *fp = fopen(fileName, "r");
  int err = 1;
  char *str = NULL;
  size_t len_string = 0;

  if (fp) {
    while ((getline(&str, &len_string, fp)) != -1) {
      int len = 0;
      len = strlen(str);
      if (str[len - 1] == '\n') str[len - 1] = '\0';
      conf->reg = realloc(conf->reg, strlen(conf->reg) + len + 2);
      strcat(conf->reg, str);
      strcat(conf->reg, "|");
    }
    free(str);
    fclose(fp);
  } else {
    err = 0;
    if (!conf->s)
      fprintf(stderr, "grep: %s: No such file or directory\n", fileName);
  }
  return err;
}