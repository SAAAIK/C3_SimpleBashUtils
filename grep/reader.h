#ifndef READER_H
#define READER_H

#include <ctype.h>
#include <getopt.h>
#include <regex.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

#define RED "\033[1;31m"
#define PUR "\033[1;35m"
#define BLUE "\033[1;36m"
#define IBLUE "\033[0;104m"
#define BLUEC "\033[1;96m"
#define GREEN "\033[0;32m"
#define BGREEN "\033[1;32m"
#define RESET "\033[0m"

void compileReg(int argc, char *argv[], config *conf, int file_index);
void search(regex_t *pattern, char *path, config *conf, int fileCounter);

void printPatternErr(char *argv[]);

#endif