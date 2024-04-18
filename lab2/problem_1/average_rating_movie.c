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

// MOVIE DATA //

struct Movie
{
    int movie_id;
    int rating;
};

struct MovieAverageRate
{
    int movie_id;
    float average_rating;
};

void readDataFromText(char* filename, struct Movie moviesData[], int* size)
{
    FILE *filePointer;
    char buffer[1024]; // Buffer to store each line read from the file

    // Open the file in read mode
    filePointer = fopen(filename, "r");

    // Check if file was opened successfully
    if (filePointer == NULL) {
        perror("Error");
        return;
    }

    // Read each line until end of file
    int index = 0;
    int data1, data2, data3, data4;
    while (fgets(buffer, sizeof(buffer), filePointer) != NULL)
    {
        sscanf(buffer, "%d %d %d %d", &data1, &data2, &data3, &data4);
        moviesData[index].movie_id = data2;
        moviesData[index].rating = data3;
        index++;
    }
    *size = index;
    // Close the file
    fclose(filePointer);
}

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

// CHILD PROCESSES //

void sortMovieAverageRate(struct MovieAverageRate movieAverageRate[], int count)
{
    // sort based on ID
    for (int i = 0; i < count - 1; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            if (movieAverageRate[i].movie_id > movieAverageRate[j].movie_id)
            {
                struct MovieAverageRate temp = movieAverageRate[i];
                movieAverageRate[i] = movieAverageRate[j];
                movieAverageRate[j] = temp;
            }
        }
    }
}

void childProcess(char* writeShm, char* filename, int childPID)
{
    // childPID = 1 or 2 indicates the child process number
    int movie_size = 0;
    struct Movie moviesData[100000];
    readDataFromText(filename, moviesData, &movie_size);
    // write to shared memory

    int arrayX[100000] = {0};
    struct MovieAverageRate movieAverageRate[100000] = {0};

    int sum = 0;
    int count = 0;
    int numOfRate = 0;
    for (int i = 0; i < movie_size; i++)
    {
        if (arrayX[i] == 0)
        {
            sum = 0;
            numOfRate = 0;
            for (int j = i; j < movie_size; j++)
            {
                if (moviesData[i].movie_id == moviesData[j].movie_id)
                {
                    sum += moviesData[j].rating;
                    arrayX[j] = 1;
                    numOfRate++;
                } 
            }
            movieAverageRate[count].movie_id = moviesData[i].movie_id;
            movieAverageRate[count].average_rating = (float)sum / numOfRate;
            count++;
        }
    }

    // Write result to shared memory
    sortMovieAverageRate(movieAverageRate, count);

    // char* writeShmPointer = writeShm;

    char buffer[1024];
    sprintf(buffer, "-- Child process %d calculate file %d --\n", childPID, childPID);
    strcat(writeShm, buffer);
    for (int i = 0; i < count; i++)
    {
        sprintf(buffer, "Movie ID: %d, Average Rating: %.2f\n", movieAverageRate[i].movie_id, movieAverageRate[i].average_rating);
        strcat(writeShm, buffer);
    }

    printf("Child process %d has written result to shared memory\n", childPID);
    exit(0);
}


void writeOutputFile(char* shm)
{
    FILE *file = fopen("output", "w+");

    fprintf(file, "%s", shm);

    fclose(file);
    
}

// delete all contents of shared memory
void deleteContents(char* shm)
{
    memset(shm, 0, SHM_SIZE);
}

int main (int argc, char *argv[])
{
    // create an array of movie data

    int shmid = create_shmid();
    char* shm = attach_shm(shmid);
    deleteContents(shm);

    // 2 child processes return the status of the child processes
    int status1 = 0, status2 = 0;
    // Create 2 child processes
    pid_t pchild_1 = fork();
    if (pchild_1 == 0)
    {
        // pchild_1 process
        childProcess(shm, "movie-100k_1.txt", 1);
    }
    else
    {
        waitpid(pchild_1, &status1, 0);
        pid_t pchild_2 = fork();
        if (pchild_2 == 0)
        {
            // pdchild_2 process
            childProcess(shm, "movie-100k_2.txt", 2);
        }
        // Parent process
        waitpid(pchild_2, &status2, 0);
    }

    // Write output
    writeOutputFile(shm);

    deleteContents(shm);
    detach_shm(shm);
    remove_shm(shmid);
}
