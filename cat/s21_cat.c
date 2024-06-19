#include <getopt.h>
#include <stdio.h>

#include "parser.h"
#include "reader.h"

int parse_param(int argc, char *argv[], char *shortOpt,
                struct option long_options[], config *conf);
int read_file(FILE *fp, config *conf);

int main(int argc, char *argv[]) {
  config conf = {0};
  char *shortOpt = "+beEnstTv";
  struct option long_options[] = {{"number-nonblank", 0, NULL, 'b'},
                                  {"number", 0, NULL, 'n'},
                                  {"squeeze-blank", 0, NULL, 's'},
                                  {0, 0, 0, 0}};
  // opterr = 0; // выключаем стоковые ошибки
  if (!parse_param(argc, argv, shortOpt, long_options, &conf)) {
    for (int i = optind; i < argc; i++) {
      FILE *fp;
      fp = fopen(argv[i], "rtcd ../");
      if (fp) {
        read_file(fp, &conf);
        fclose(fp);
      } else {
        fprintf(stderr, "cat: %s: No such file or directory\n",
                argv[i]);  // убрать cat??
      }
    }
  } else {
    printf("usage: cat [-benstuv] [file ...]\n");
  }

  return 0;
}  // main