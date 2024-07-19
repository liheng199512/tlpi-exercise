#include "tlpi.h"

int Editor(int argc, char *argv[])
{
    int fd = open(argv[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1) {
        Exit("open");
    }

    int len = 0;
    int nRead = 0;
    int nWrite = 0;
    int offset = 0;
    char *buf = NULL;
    for (int ap = 2; ap < argc; ++ap) {
        switch (argv[ap][0]) {
            case 'r':
            case 'R':
                len = GetInt(&argv[ap][1]);
                buf = malloc(len);
                if (!buf) {
                    Exit("malloc");
                }
                nRead = read(fd, buf, len);
                if (nRead == -1) {
                    Exit("read");
                }
                if (nRead == 0) {
                    printf("%s: end of file\n", argv[ap]);
                } else {
                    printf("%s: ", argv[ap]);
                    for (int i = 0; i < nRead; ++i) {
                        if (argv[ap][0] == 'r') {
                            printf("%c", buf[i]);
                        } else {
                            printf("%02x ", buf[i]);
                        }
                    }
                    printf("\n");
                }
                free(buf);
                break;
            case 'w':
                nWrite = write(fd, &argv[ap][1], strlen(&argv[ap][1]));
                if (nWrite == -1) {
                    Exit("write");
                }
                printf("%s: wrote %d bytes\n", argv[ap], nWrite);
                break;
            case 's':
                offset = GetInt(&argv[ap][1]);
                if (lseek(fd, offset, SEEK_SET) == -1) {
                    Exit("lseek");
                }
                printf("%s: succeed\n", argv[ap]);
                break;
            default:
                printf("%s: unknown command\n", argv[ap]);
                break;
        }
    }
    return EXIT_SUCCESS;
}

int TestEditor(int argc, char *argv[])
{
    if (argc < 3 || strcmp(argv[1], "--help") == 0) {
        Usage("%s file {r<length>|R<length>|w<string>|s<offset>}...", argv[0]);
    }
    return Editor(argc, argv);
}
