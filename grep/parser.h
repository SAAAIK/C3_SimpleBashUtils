#ifndef PARSER_H
#define PARSER_H
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *reg;
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int h;
  int s;
  int f;
  int o;
} config;

int parse(int argc, char *argv[], config *conf, int *file_index);
int regopen(config *conf, char *path);

#endif