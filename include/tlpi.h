#ifndef TLPI_H
#define TLPI_H

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <unistd.h>  // for getopt, use `-std=gnu99`

#define BUF_SIZE 1024
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

void Usage(const char *format, ...);
void Exit(const char *format, ...);
long GetInt(const char *str);

#endif
