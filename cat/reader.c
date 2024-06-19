#include "reader.h"

void print_flag_error(char *argv[], int optind) {
  fprintf(stderr, "cat: illegal option --%s\n", argv[optind - 1]);
}

int read_file(FILE *fp, config *conf) {
  char ch;

  int gobbler_flag = 0;
  char prev = '\n';
  int line_counter = 0;
  while ((ch = fgetc(fp)) != EOF) {
    int line = 0;
    line = (ch == '\n' && prev == '\n') ? 1 : 0;
    if (ch == '\n') {
      if (gobbler_flag) {
        continue;
      }
    } else {
      gobbler_flag = 0;
    }
    if (line && conf->s) {
      gobbler_flag = 1;
    }

    if (conf->b) {
      if (prev == '\n' && !line) printf("%6d\t", ++line_counter);
    } else if (conf->n) {
      if (prev == '\n') printf("%6d\t", ++line_counter);
    }

    if (conf->v) {
      if (ch >= 0 && ch < 32 && ch != 9 && ch != 10) {
        printf("^%c", ch + 64);
        prev = ch;
        continue;
      } else if (ch == 127) {
        printf("^?");
        prev = ch;
        continue;
      }
    }

    if (conf->e) {
      if (ch == '\n') {
        putchar('$');
      }
    }

    if (conf->t) {
      if (ch == '\t') {
        putchar('^');
        putchar('I');
        prev = ch;
        continue;
      }
    }
    prev = ch;
    printf("%c", ch);
  }
  return 0;
}