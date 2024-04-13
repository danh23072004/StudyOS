#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_KEY 0x123

// calculate the average rating of a movie using 2 processes

int main (int argc, char *argv[]) 
{
    // unzip the file movie-100k-split.zip
    system("unzip movie-100k-split.zip");
}