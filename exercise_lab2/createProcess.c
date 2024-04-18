#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // This is the header of POSIX API
#include <string.h>

int main(int argc, char *argv[])
{
    __pid_t pid = fork();

    int x = 0;

    if (pid == 0) // pid == 0 when it is the child process
    {
        x++;
        printf("Child process: x = %d\n", x);
        printf("Child process is sleeping\n");
        sleep(3);
    }
    else
    {
        printf("Parent process: x = %d\n", x);
    }


    x += 3;
    printf("process %d : x = %d\n", getpid(), x);

    return 0;
}