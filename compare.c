#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>
#include <sys/types.h>

#define BILLION  1000000000L

#define CLOCK_ID CLOCK_PROCESS_CPUTIME_ID

/*Compute the difference between two time stamps returned by clock_gettime */

uint64_t diff(struct timespec start, struct timespec end)
{
        uint64_t diff;

        diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;

        return diff;
}

void minimalFunctionCall()
{

}

int main(int argc, char *argv)
{
        struct timespec start, end;
        uint64_t elapsedTimeFunction, elapsedTimeSystem;
        int i,s;

        clock_gettime(CLOCK_ID, &start);
        minimalFunctionCall();
        clock_gettime(CLOCK_ID, &end);

        elapsedTimeFunction = diff(start, end);

        clock_gettime(CLOCK_ID, &start);
        getpid();
        clock_gettime(CLOCK_ID,&end);

        elapsedTimeSystem = diff(start, end);

        printf("Elapsed time for minimal function call is: %llu\nElapsed time for a system call is: %llu\n", (long long unsigned int)elapsedTimeFunction, (long long unsigned int)elapsedTimeSystem);
}

