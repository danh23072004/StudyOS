#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <string.h>

# define SHM_SIZE 10000000
# define KEY 0x2310

int create_shmid()
{
    int shmid = shmget(KEY, SHM_SIZE , IPC_CREAT | 0666);

    if (shmid < 0)
    {
        perror("shmget failed");
        return 0;
    }

    printf("The shared memory created with id: %d\n", shmid);
    fflush(stdout);
    return shmid;
}

char* attach_shm(int shmid)
{
    // return the address of the shared memory based on shmid
    // treat shm as a
    char* shm = shmat(shmid, NULL, 0);

    if (shm == (char *) -1)
    {
        perror("shmat failed");
        return 0;
    }

    printf("The shared memory attached at address: %p\n", shm);
    fflush(stdout);
    return shm;
}

void show_shm(char* shm)
{
    if (shm != 0)
    {
        printf("The shared memory content: %s\n", shm);
        fflush(stdout);
    }
    else
    {
        printf("The shared memory is empty\n");
        fflush(stdout);
    }
}

void detach_shm(char* shm)
{
    if (shmdt(shm) == -1)
    {
        perror("shmdt failed");
        return;
    }
    printf("The shared memory detached\n");
}

void remove_shm(int shmid)
{
    if (shmctl(shmid, IPC_RMID, NULL) == -1)
    {
        perror("shmctl failed");
        return;
    }
    printf("The shared memory removed\n");
}

void deleteContents(char* shm)
{
    memset(shm, 0, SHM_SIZE);
}

int main (int argc, char *argv[])
{
    int shmid = create_shmid();
    char* shm = attach_shm(shmid);

    pid_t childPid = fork();

    if (childPid == 0)
    {
        // child process
        printf("Child process\n");
        fflush(stdout);
        char buffer[1024];
        sprintf(buffer, "Hello from child process\n");
        // sprintf(buffer, "%s", shm);
        strcat(shm, buffer);
        exit(0);
    }
    else if (childPid > 0)
    {
        // parent process
        printf("Parent process\n");
        fflush(stdout);
        wait(NULL);
        char buffer[1024];
        sprintf(buffer, "Hello from parent process\n");
        strcat(shm, buffer);
        sprintf(buffer, "Hello from parent process 2222\n");
        // sprintf(buffer, "%s", shm);
        strcat(shm, buffer);
    }

    printf("The shared memory content: %s\n", shm);

    deleteContents(shm);
    detach_shm(shm);
    remove_shm(shmid);
    return 0;
}