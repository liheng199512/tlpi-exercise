#include "tlpi.h"

int ReadV(int fd, const struct iovec *iov, int iovCnt)
{
    int readn = 0;
    for (int i = 0; i < iovCnt; ++i) {
        int n = 0;
        if ((n = read(fd, iov[i].iov_base, iov[i].iov_len)) < 0) {
            Exit("read");
        }
        readn += n;
    }
    return readn;
}

int WriteV(int fd, const struct iovec *iov, int iovCnt)
{
    int writen = 0;
    for (int i = 0; i < iovCnt; ++i) {
        int n = 0;
        if ((n = write(fd, iov[i].iov_base, iov[i].iov_len)) < 0) {
            Exit("write");
        }
        writen += n;
    }
    return writen;
}

void TestReadVWriteV()
{
    struct iovec iov[10];
    for (int i = 0; i < 10; ++i) {
        iov[i].iov_base = malloc(100);
        if (iov[i].iov_base == NULL) {
            Exit("malloc");
        }
        iov[i].iov_len = 100;
    }

    int fd = open("tmp.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
    if (fd == -1) {
        Exit("open");
    }
    int n = WriteV(fd, iov, 10);
    printf("write n = %d\n", n);
    lseek(fd, 0, SEEK_SET);
    n = ReadV(fd, iov, 10);
    printf("read n = %d\n", n);

    for (int i = 0; i < 10; ++i) {
        free(iov[i].iov_base);
    }
}
