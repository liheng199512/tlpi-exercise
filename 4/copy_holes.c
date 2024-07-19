#include "tlpi.h"

int CopyHoles(const char *inFile, const char *outFile)
{
    int inFd = open(inFile, O_RDONLY);
    if (inFd == -1) {
        Exit("open in file");
    }
    int outFd = open(outFile, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (outFd == -1) {
        Exit("open out file");
    }

    int expand = 0;
    char ch = 0;
    int n = 0;
    lseek(inFd, 0, SEEK_SET);

    while ((n = read(inFd, &ch, 1)) == 1) {
        if (ch == '\0') {
            ++expand;
        } else {
            int offset = lseek(outFd, expand, SEEK_END);
            if (write(outFd, &ch, 1) != 1) {
                Exit("write out file");
            }
            expand = 0;
        }
    }
    if (n < 0) {
        Exit("read in file");
    }

    if (close(inFd) == -1) {
        Exit("close in file");
    }
    if (close(outFd) == -1) {
        Exit("close out file");
    }
    return EXIT_SUCCESS;
}

int TestCopyHoles(int argc, char *argv[])
{
    if (argc != 3 || strcmp(argv[1], "--help") == 0) {
        Usage("%s inFile outFile", argv[0]);
    }

    int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);  // 使用O_APPEND不会产生空洞
    if (fd == -1) {
        Exit("open");
    }
    write(fd, "1234", 4);
    lseek(fd, 1000, SEEK_END);
    write(fd, "asdfvbghjk", 10);
    lseek(fd, 1321, SEEK_END);
    write(fd, "0987654321", 10);
    if (close(fd) == -1) {
        Exit("close");
    }

    return CopyHoles(argv[1], argv[2]);
}