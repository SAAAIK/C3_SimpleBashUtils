#ifndef PARSER_H
#define PARSER_H
#include <getopt.h>
#include <stdio.h>

typedef struct {
  int b;
  int e;
  int n;
  int s;
  int t;
  int v;
} config;

int parse_param(int argc, char *argv[], char *shortOpt,
                struct option *long_options, config *conf);
void print_flag_error(char *argv[], int optind);
#endif