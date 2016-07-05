#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <sched.h>
#include <sys/types.h>
#include <errno.h>
#include <math.h>

static volatile int state = 1;

void intHandler(int x)
{
        state = 0;
        printf("Exiting\n");
}

void cpuIntensiveFunction()
{
        volatile unsigned long long i;
        for (i = 0; i < 1000000000ULL; ++i);
}

int main(int argc, char* argv[])
{
        struct sigaction act;
        act.sa_handler = intHandler;
        sigaction(SIGINT, &act, NULL);

        pid_t pid = getpid();
        int policy;
        struct sched_param param;

        if(argc == 1)
        {
                printf("Please enter parameter (SCHED_OTHER, SCHED_FIFO, SCHED_RR)\n");
                exit(1);
        }

        if (!strcmp(argv[1], "SCHED_OTHER")) {
                policy = SCHED_OTHER;
        }
        else if(!strcmp(argv[1], "SCHED_FIFO")){
                policy = SCHED_FIFO;
        }
        else if (!strcmp(argv[1], "SCHED_RR")){
                policy = SCHED_RR;
        }
        else{
                perror("Scheduling policy not understood\n");
                exit(EXIT_FAILURE);
        }

        /* set process to max priority for given scheduler */
        param.sched_priority = sched_get_priority_max(policy);

        if(sched_setscheduler(0,policy,&param)){
                perror("Error setting scheduler policy");
                exit(EXIT_FAILURE);
        }

        while(state)
        {
                printf("[%d] Sleeping\n", pid); sleep(1);
                printf("[%d] Running\n", pid); cpuIntensiveFunction();
        }
}
