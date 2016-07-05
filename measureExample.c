/*
** This program illustrates the use of clock_gettime 
*/

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>

#define BILLION  1000000000L

#define CLOCK_ID CLOCK_PROCESS_CPUTIME_ID

/*Compute the difference between two time stamps returned by clock_gettime */

uint64_t diff(struct timespec start, struct timespec end)
{
  uint64_t diff;

  diff = BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec;

  return diff;
}


int main(int argc, char *argv[])
{
  struct timespec start, end;
  uint64_t elapsedTime;
  int i,s;


  clock_gettime(CLOCK_ID, &start);
     for (i=0; i < 10; i++)
        s = 0;
  clock_gettime(CLOCK_ID, &end);
  elapsedTime = diff(start,end);
  printf("elapsed process CPU time is %llu\n",(long long unsigned int) elapsedTime);

}
