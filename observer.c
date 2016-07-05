#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>


void my_sigchld_handler(int sig)
{
        pid_t p;
        int status;

        while ((p=waitpid(-1, &status, WNOHANG)) != -1)
        {
                printf("Process Terminated\n");
                exit(1);
        }
}

int main(int argc, char *argv[])
{

        struct sigaction sa;

        memset(&sa, 0, sizeof(sa));
        sa.sa_handler = my_sigchld_handler;

        sigaction(SIGCHLD, &sa, NULL);
        
        //Start the process specified in the arguments
        pid_t pid;
        pid = fork();

        FILE *fp;
        char buff[255];

        //if its a child process
        if(pid == 0)
        {
                if(execvp(argv[1], argv) < 0)
                {
                        perror("Exec Problem");
                        exit(1);
                }
        }
        else if(pid < 0)
        {
                perror("Problem Forking");
                exit(-1);
        }
        else //Parent process
        {
                while(1)
                {
                        printf("%d\n", pid);

                        //Read in [pid]/stat
                        int i = 0;
                        char* token;
                        char readIn[255];

                        //Prepare filepath
                        sprintf(readIn, "/proc/%d/stat", pid);
                        printf("%d\n",pid);
                        fp = fopen(readIn, "r");

                        //Read in stat
                        if(fgets(buff, 255, fp) == NULL)
                        {
                                break;
                        }

                        char *str = strdup(buff);  // We own str's memory now.

                        //Print the amount of time this process has been scheduled in user mode and kernel mode
                        while ((token = strsep(&str, " ")))
                        {
                                if(i == 13) printf("User Mode: %s\n", token);
                                if(i == 14) printf("Kernel Mode: %s\n", token);
                                i++;
                        }

                        sleep(1);
                        fclose(fp);
                }
        }
}
