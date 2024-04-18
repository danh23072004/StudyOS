#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(long long argc, char *argv[]){
    // Count time
    clock_t startTime, endTime;
    double cpu_time_used;
    startTime = clock();

    long long n = atoi(argv[1]);

    long long sum = 0;
    for (long long i = 1; i <= n; ++i)
        sum += i;

    endTime = clock();
    cpu_time_used = ((double)(endTime - startTime)) / CLOCKS_PER_SEC;

    printf("Sum of Serial: %lld\n", sum);
    printf("Time of Serial: %f\n", cpu_time_used);
    
    return 0;
}