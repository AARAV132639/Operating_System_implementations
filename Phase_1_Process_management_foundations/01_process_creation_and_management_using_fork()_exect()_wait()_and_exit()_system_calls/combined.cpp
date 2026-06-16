#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;

    int status;

    pid = fork();
    pid = fork();    

    if(pid<0)
    {
        perror("fork");
        exit(1);
    }

     

    if(pid ==0)
    {
        printf("Child process\n");
        printf("PID = %d\n", getpid());

        execl("/bin/date","date",NULL);

        perror("exec");

        exit(1);
    }

   
    else
    {
        printf("Parent process\n");
        printf("Waiting for child ....\n");

        wait(&status);

        if(WIFEXITED(status))
        {
            printf("Child exited with status %d \n", WEXITSTATUS(status));
        }

        printf("parent terminating \n");
    }
    return 0;
}