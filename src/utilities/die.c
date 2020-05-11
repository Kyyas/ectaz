#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

void die(const char *str)
{
    perror(str);
    exit(1);
}
