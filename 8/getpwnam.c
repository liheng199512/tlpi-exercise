#include "tlpi.h"

struct passwd *GetPwNam(const char *name)
{
    setpwent();
    struct passwd *ent = getpwent();
    while (ent) {
        if (strcmp(ent->pw_name, name) == 0) {
            break;
        }
        ent = getpwent();
    }
    endpwent();
    return ent;
}

void TestGetPwNam()
{
    struct passwd *ent = GetPwNam("liheng");
    printf("username=%s, uid=%d\n", ent->pw_name, ent->pw_uid);
}
