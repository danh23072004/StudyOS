#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* routine_1()
{
    printf("Thread 1\n");
}

int main (int argc, char *argv[])
{
    pthread_t thread1;

    pthread_create(&thread1, NULL, routine_1, NULL);

    return 0;
}