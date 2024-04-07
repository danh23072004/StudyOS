#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // This is the header of POSIX API
#include <string.h>

int main(int argc, char *argv[])
{
    __pid_t pidCurrentProcess = getpid();
    __pid_t pidParentProcess = getppid();

    printf("Current process ID: %d\n", pidCurrentProcess);
    printf("Parent process ID: %d\n", pidParentProcess);

    return 0;
}