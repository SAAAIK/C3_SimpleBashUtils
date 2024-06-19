#include "reader.h"

void compileReg(int argc, char *argv[], config *conf, int fileIndex) {
  regex_t regex;
  int len = strlen(argv[fileIndex]);
  // printf("%s\n", conf->reg);
  // printf("%d\n", strlen(conf->reg));
  if (!conf->e && !conf->f) {
    conf->reg = realloc(conf->reg, len + 1);
    strcat(conf->reg, argv[fileIndex]);
    fileIndex++;
  } else
    conf->reg[strlen(conf->reg) - 1] = '\0';

  int fileCounter = argc - fileIndex;
  int eflags = conf->i ? REG_EXTENDED + REG_ICASE : REG_EXTENDED;

  if (!regcomp(&regex, conf->reg, eflags)) {
    for (int i = fileIndex; i < argc; i++) {
      search(&regex, argv[i], conf, fileCounter);
    }
  }
  // printf("%s\n", conf->reg);
  // printf("%d\n", strlen(conf->reg));
  regfree(&regex);
}

void search(regex_t *regex, char *fileName, config *conf, int fileCounter) {
  FILE *fl = fopen(fileName, "r");
  char *str = NULL;
  size_t len_string = 0;

  if (fl) {
    int line = 1, cfl = 0, end = 0, lfl = 0;
    while ((getline(&str, &len_string, fl)) != -1 && !lfl) {
      regmatch_t pmatch[2];
      int reg = regexec(regex, str, 2, pmatch, 0);
      int eo = (int)pmatch[0].rm_eo;
      int so = (int)pmatch[0].rm_so;

      if ((reg == 0 && !conf->v) || (reg == REG_NOMATCH && conf->v)) {
        if (conf->c) cfl++;
        if (conf->o && conf->v) {
          if (conf->l) {
            lfl = 1;
          }
          continue;
        }
        if (conf->l) {
          lfl = 1;
        } else if (!conf->c) {  //&& !conf->v
          if (fileCounter > 1 && !conf->h && !conf->o) printf("%s:", fileName);

          if (conf->n && !conf->o) printf("%d:", line);

          if (conf->o) {
            char *linePtr = str;
            while ((reg = regexec(regex, linePtr, 2, pmatch, 0)) == 0) {
              // if (pmatch[0].rm_eo == -1) {
              //   continue;
              // }
              eo = (int)pmatch[0].rm_eo;
              so = (int)pmatch[0].rm_so;

              if (fileCounter > 1 && !conf->h) printf("%s:", fileName);
              if (conf->n) printf("%d:", line);
              printf("%.*s\n", eo - so, &linePtr[so]);
              linePtr += pmatch[0].rm_eo;
            }
          } else {
            printf("%s", str);
            end = str[strlen(str) - 1] == '\n' ? 0 : 1;
          }
        }
      }
      line++;
    }
    if (conf->c && !conf->l) {  // && !conf->l)
      if (fileCounter > 1 && !conf->h)
        printf("%s:%d\n", fileName, cfl);
      else
        printf("%d\n", cfl);
    }
    if (conf->l && lfl == 1) printf("%s\n", fileName);

    if (end) printf("\n");

    free(str);
    fclose(fl);

  } else if (!conf->s)
    fprintf(stderr, "grep: %s: No such file or directory\n", fileName);
}
