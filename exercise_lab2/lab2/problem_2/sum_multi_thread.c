#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

long long sum = 0;
#define MAX_THREADS 100000

struct thread_args
{
    long long start;
    long long end;
};

void *increment_sum(void *arg)
{
    struct thread_args *args = (struct thread_args *)arg;

    // Cal per thread
    long long local_sum = 0;

    // Run from start to the end, for each threads cal the sum
    for (long long i = args->start; i <= args->end; i++)
    {
        local_sum += i;
    }

    /* Start Critical Section */
    // Use a mutex to ensure thread-safe access to the shared sumer
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_lock(&mutex);
    // Update the shared sumer using mutex protection
    sum += local_sum;
    pthread_mutex_unlock(&mutex);
    /* End Critical Section */

    pthread_exit(NULL);
}

long long main(long long argc, char *argv[])
{
    // Measure time
    clock_t startTime, endTime;
    double cpu_time_used;
    startTime = clock();

    // Take number of threads
    long long num_threads = atoi(argv[1]), n = atoi(argv[2]);

    // Init sum = 0
    sum = 0;

    // Create threads
    pthread_t threads[MAX_THREADS];
    struct thread_args thread_args[MAX_THREADS]; // Use a separate array for arguments
    long long status;

    // Create threads and do job

    long long gap = n / num_threads;
    long long start = 1;
    long long end = gap;
    for (int i = 0; i < num_threads; i++)
    {
        // Assign start & end
        thread_args[i].start = start;
        thread_args[i].end = end;

        start += gap;
        end += gap;
    }

    // Create threads
    for (int i = 0; i < num_threads; i++)
        pthread_create(&threads[i], NULL, increment_sum, &thread_args[i]);

    
    // Wait for all threads to finish
    for (int i = 0; i < num_threads; i++)
        pthread_join(threads[i], NULL);

    // Measure time
    endTime = clock();
    cpu_time_used = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;

    printf("Sum of MultiThreads: %lld\n", sum);
    printf("Time of MultiThreads: %f\n", cpu_time_used);

    return 0;
}