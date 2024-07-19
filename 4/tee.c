#include "tlpi.h"

extern char *optarg;

int Tee(int argc, char *argv[])
{
    int inFd = STDIN_FILENO;
    int outFd = STDOUT_FILENO;
    if (argc > 1) {
        const char *fileName = argv[1];
        int flag = O_WRONLY | O_CREAT | O_TRUNC;
        int mode = S_IRUSR | S_IWUSR;
        int opt = getopt(argc, argv, "a:");
        if (opt == 'a') {
            fileName = optarg;
            flag &= ~O_TRUNC;
            flag |= O_APPEND;
        }
        outFd = open(fileName, flag, mode);
        if (outFd == -1) {
            Exit("open");
        }
    }

    int n = 0;
    char buf[BUF_SIZE];
    while ((n = read(inFd, buf, BUF_SIZE)) > 0) {
        if (write(STDOUT_FILENO, buf, n) < n) {
            Exit("write stdout");
        }
        if (outFd != STDOUT_FILENO) {
            if (write(outFd, buf, n) < n) {
                Exit("write outfd");
            }
        }
    }
    if (outFd != STDOUT_FILENO) {
        if (close(outFd) == -1) {
            Exit("close outfd");
        }
    }
    if (n < 0) {
        Exit("read infd");
    }
    return EXIT_SUCCESS;
}

int TestTee(int argc, char *argv[])
{
    if (argc > 3 || strcmp(argv[1], "--help") == 0) {
        Usage("%s {-a file}/{file}", argv[0]);
    }
    return Tee(argc, argv);
}
