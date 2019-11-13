// Use Makefile for compiling
// clang version 7.0.0-3 (tags/RELEASE_700/final)
// Target: x86_64-pc-linux-gnu
// Thread model: posix
// InstalledDir: /usr/bin
// Found candidate GCC installation: /usr/bin/../lib/gcc/x86_64-linux-gnu/8
// Found candidate GCC installation: /usr/lib/gcc/x86_64-linux-gnu/8
// Selected GCC installation: /usr/bin/../lib/gcc/x86_64-linux-gnu/8
// Candidate multilib: .;@m64
// Selected multilib: .;@m64

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    time_t lt;
    lt = time(NULL);
    printf("Time = %ld\n", lt);
    sleep(1); 

    int time_pipe[2];
    if(pipe(time_pipe) < 0)
    {
        printf("Error - Pipe < 0\n");
        return 1;
    }

     __pid_t child_pid;
    if((child_pid = fork()) != 0)
    {
        // Parent pid
        printf("It's parent process\n");
        printf("\tPPID: %d\n\tPID: %d\n",getppid(), getpid());
        lt = time(NULL); // Update time before writing to pipe
        write(time_pipe[1], &lt, sizeof(time_t));
        printf("\tWritten time is %ld\n", lt);
        int res = 0;
        sleep(1);
        waitpid(child_pid, &res, 0);
    }
    else
    {
        // Forked pid
        printf("It's child process\n");
        printf("\tPPID: %d\n\tPID: %d\n",getppid(), getpid());
        printf("\tBase time was %ld\n", lt);
        read(time_pipe[0], &lt, sizeof(time_t));
        printf("\tRead time is %ld\n", lt);
        sleep(1);
        lt = time(NULL);
        printf("\tNow time is %ld\n", lt);
    }
    return 0;
}
