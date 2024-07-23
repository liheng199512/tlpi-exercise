#include "tlpi.h"

int AtomicAppend(int argc, char *argv[])
{
    const char *fileName = argv[1];
    int num = atoi(argv[2]);
    int flag = O_WRONLY | O_CREAT | O_APPEND;
    int mode = S_IRWXU;
    if (argc == 4 && argv[3][0] == 'x') {
        flag &= ~O_APPEND;
    }

    int fd = open(fileName, flag, mode);
    if (fd == -1) {
        Exit("open");
    }

    for (int i = 0; i < num; ++i) {
        if (!(flag & O_APPEND)) {
            lseek(fd, 0, SEEK_END);
        }
        write(fd, "1", 1);
    }
    return EXIT_SUCCESS;
}

int TestAtomicAppend(int argc, char *argv[])
{
    if (argc != 3 && argc != 4) {
        Usage("%s filename number [x]", argv[0]);
    }
    return AtomicAppend(argc, argv);
}
