#include "tlpi.h"

extern int errno;

int Dup(int fd)
{
    if (fcntl(fd, F_GETFL) == -1) {
        perror("fd is invalid");
        errno = EBADF;
        return -1;
    }
    return fcntl(fd, F_DUPFD, 0);
}

int Dup2(int oldFd, int newFd)
{
    if (fcntl(oldFd, F_GETFL) == -1) {
        perror("oldFd is invalid");
        errno = EBADF;
        return -1;
    }
    if (oldFd == newFd) {
        return newFd;
    }
    if (fcntl(newFd, F_GETFL) != -1) {
        close(newFd);
    }
    return fcntl(oldFd, F_DUPFD, newFd);
}

void TestDup()
{
    int fd1 = Dup(STDIN_FILENO);
    int fd = open("tmp.txt", O_RDWR | O_CREAT, S_IRWXU);
    if (fd == -1) {
        Exit("open");
    }
    int fd2 = Dup(STDIN_FILENO);
    int fd3 = Dup(10);
    printf("fd1 = %d, fd2 = %d, fd3 = %d\n", fd1, fd2, fd3);

    fd1 = Dup2(1, 2);
    fd2 = Dup2(3, 3);
    fd3 = Dup2(3, 7);
    int fd4 = Dup2(7, 7);
    printf("fd1 = %d, fd2 = %d, fd3 = %d fd4 = %d\n", fd1, fd2, fd3, fd4);
}

void TestDupShare()
{
    int fd = open("tmp.txt", O_RDONLY | O_CREAT, S_IRWXU);
    if (fd == -1) {
        Exit("open");
    }
    int fd1 = Dup2(fd, 100);
    if (fd1 == -1) {
        Exit("Dup");
    }

    int l1 = lseek(fd, 10, SEEK_SET);
    int l2 = lseek(fd1, 20, SEEK_CUR);
    printf("l1 = %d, l2 = %d\n", l1, l2);

    int n = write(fd, "1", 1);
    if (n != 1) {
        perror("write fd");
    }
    n = write(fd1, "1", 1);
    if (n != 1) {
        perror("write fd1");
    }
}

void TestDupWR()
{
    int fd1 = open("tmp.txt", O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
    if (fd1 == -1) {
        Exit("open fd1");
    }
    int fd2 = dup(fd1);
    if (fd2 == -1) {
        Exit("open fd2");
    }
    int fd3 = open("tmp.txt", O_RDWR);
    if (fd3 == -1) {
        Exit("open fd3");
    }

    write(fd1, "hello,", 6);
    write(fd2, "world", 5);
    lseek(fd2, 0, SEEK_SET);
    write(fd1, "HELLO,", 6);
    write(fd3, "Gidday", 6);
}