#include "tlpi.h"

int Copy(const char *inFile, const char *outFile)
{
    int infd = open(inFile, O_RDONLY);
    if (infd == -1) {
        Exit("open file %s", inFile);
    }

    int flags = O_CREAT | O_WRONLY | O_TRUNC | O_APPEND;
    int permissions = S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH;
    int outfd = open(outFile, flags, permissions);
    if (outfd == -1) {
        Exit("open file %s", outFile);
    }

    char buf[BUF_SIZE];
    int n = 0;
    while ((n = read(infd, buf, BUF_SIZE)) > 0) {
        if (write(outfd, buf, n) != n) {
            Exit("couldn't write whole buffer");
        }
    }
    if (n == -1) {
        Exit("read");
    }

    if (close(infd) == -1) {
        Exit("close inFile");
    }
    if (close(outfd) == -1) {
        Exit("close outFile");
    }

    return EXIT_SUCCESS;
}

int TestCopy(int argc, char *argv[])
{
    if (argc != 3 || strcmp(argv[1], "--help") == 0) {
        Usage("%s in-file out-file", argv[0]);
    }
    return Copy(argv[1], argv[2]);
}
