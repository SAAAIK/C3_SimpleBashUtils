#include "parser.h"
#include "reader.h"

int main(int argc, char *argv[]) {
  config conf = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  conf.reg = calloc(1, sizeof(char));
  int f = 0;

  if (argc < 3) {
    fprintf(stderr,
            "Использование: %s [-flag] \"text\" [filename1 filename2 ...]\n",
            argv[0]);
    free(conf.reg);
    return 1;
  }

  if (parse(argc, argv, &conf, &f) != 2) {
    compileReg(argc, argv, &conf, f);
  }

  free(conf.reg);
  return 0;
}