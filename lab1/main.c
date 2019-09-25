#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("1: \n\tPPID: %d\n\tPID: %d\n",getppid(), getpid());
    

    if(fork() == 0)
    {
        // Parent pid
        printf("2: \n\tPPID: %d\n\tPID: %d\n",getppid(), getpid());
    }
    else
    {
        // Forked pid
        printf("2: \n\tPPID: %d\n\tPID: %d\n",getppid(), getpid());
    }
    
    getchar();
    return 0;
}
