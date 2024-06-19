#ifndef READER_H
#define READER_H
#include <ctype.h>
#include <getopt.h>
#include <stdio.h>

#include "parser.h"

int read_file(FILE *fp, config *conf);
void print_flag_error(char *argv[], int optind);

#endif