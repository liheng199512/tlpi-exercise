#include "tlpi.h"

void Usage(const char *format, ...)
{
    va_list argList;
    fflush(stdout);

    fprintf(stderr, "Usage: ");
    va_start(argList, format);
    vfprintf(stderr, format, argList);
    va_end(argList);

    fprintf(stderr, "\n");
    fflush(stderr);
    exit(EXIT_FAILURE);
}

void Exit(const char *format, ...)
{
    va_list argList;
    fflush(stdout);

    fprintf(stderr, "Exit: ");
    va_start(argList, format);
    vfprintf(stderr, format, argList);
    va_end(argList);
    
    fprintf(stderr, "\n");
    fflush(stderr);
    exit(EXIT_FAILURE);
}

long GetInt(const char *str)
{
    char *end = NULL;
    long num = strtol(str, &end, 10);
    return (int)num;
}
