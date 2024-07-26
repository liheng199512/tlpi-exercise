#include "tlpi.h"

char g_buf[65535];
int g_primes[] = {2, 3, 5, 7};

extern char etext, edata, end;

static int Square(int x)
{
    int t1;
    int t2;
    int t3;
    printf("&t1=%p, &t2=%p, &t3=%p\n", &t1, &t2, &t3);  // 栈怎么往地址高的方向增长了？
    int result;
    result = x * x;
    printf("in Square\n");
    printf("&x=%p, &result=%p\n", &x, &result);
    return result;
}

static void DoCal(int val)
{
    printf("in DoCal\n");
    printf("&val=%p\n", &val);
    printf("the square of %d is %d\n", val, Square(val));
    if (val < 1000) {
        int t;
        t = val * val * val;
        printf("&t=%p\n", &t);
        printf("the cube of %d is %d\n", val, t);
    }
}

int MemSegmentsTest(int argc, char *argv[])
{
    printf("etext=%p, edata=%p, end=%p\n", &etext, &edata, &end);
    printf("&argc=%p, argv=%p\n", &argc, (void *)argv);
    static int key = 99;
    static char buf[10240000];
    char *p;
    p = malloc(1024);

    printf("&key=%p, &buf=%p, &p=%p, p = %p\n", &key, buf, &p, p);

    DoCal(key);

    free(p);
    return EXIT_SUCCESS;
}