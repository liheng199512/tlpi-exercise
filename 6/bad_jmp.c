#include "tlpi.h"

jmp_buf env;

void f2()
{
    longjmp(env, 1);
}

void f11()
{
    printf("in f11\n");
    if (setjmp(env) != 0) {
        printf("in f11, returned\n");
    }
    printf("out f11\n");
}

void f1()
{
    printf("in f1\n");
    f11();
    printf("out f1\n");
}

void JmpTest()
{
    f1();
    f2();
}
