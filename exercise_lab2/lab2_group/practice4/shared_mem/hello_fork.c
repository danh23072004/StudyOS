#include <stdio.h>

int main(int argc, char *argv[])
{
    fork();
    printf("Hello, world!\n");
    getc(stdin);
    return 0;
}