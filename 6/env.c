#include "tlpi.h"

int UnSetEnv(const char *name)
{
    if (name == NULL || name[0] == '\0' || strchr(name, '=') != NULL) {
        errno = EINVAL;
        return -1;
    }

    extern char **environ;
    int len = strlen(name);
    for (char **p1 = environ; *p1;) {
        if (strncmp(*p1, name, len) == 0 && (*p1)[len] == '=') {
            for (char **p2 = p1; *p2; ++p2) {
                *p2 = *(p2 + 1);
            }
        } else {
            ++p1;
        }
    }
    return EXIT_SUCCESS;
}

int SetEnv(const char *name, const char *value, int overWrite)
{
    if (name == NULL || value == NULL || name[0] == '\0' || strchr(name, '=') != NULL) {
        errno = EINVAL;
        return -1;
    }

    if (getenv(name) != NULL && overWrite == 0) {
        return 0;
    }

    UnSetEnv(name);

    char *buf = malloc(strlen(name) + strlen(value) + 2);
    if (buf == NULL) {
        return -1;
    }
    int n = sprintf(buf, "%s=%s", name, value);
    if (n < 0) {
        return -1;
    }

    return putenv(buf);
}

void TestEnv()
{
    SetEnv("xyz", "one", 1);
    SetEnv("xyz", "two", 1);
    SetEnv("xyz", "three", 0);
    system("printenv | grep xyz");
    UnSetEnv("xyz");
    system("printenv | grep xyz");
}
