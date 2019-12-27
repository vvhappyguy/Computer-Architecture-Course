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
#include <string.h>
#include <errno.h>

#define TIME_BUFFER_SIZE_STR 25

typedef struct _pipe_value
{
    char str[TIME_BUFFER_SIZE_STR];
    pid_t pid;
} pipe_value;

int main()
{
    int time_pipe[2];
    if(pipe(time_pipe) < 0)
    {
        printf("Error - Pipe < 0\nerrno:%d\n",errno);
        return 1;
    }

     pid_t child_pid;
    if((child_pid = fork()) != 0)
    {
        // Parent pid
        pipe_value value;
        value.pid = getpid();
        time_t t = time(NULL);
        strncpy(value.str, ctime(&t), TIME_BUFFER_SIZE_STR-1);
        value.str[TIME_BUFFER_SIZE_STR - 1] = '\0';
        // Manipulation for deleting useless \n from ctime returned string
        printf("It's parent process\n");
        printf("\tPPID: %d\n\tPID: %d\n",getppid(), getpid());
        write(time_pipe[1], &value, sizeof(pipe_value));
        printf("\tWritten time is %s\n", value.str);  
    }
    else
    {
        // Forked pid
        sleep(2);
        printf("It's child process\n");
        printf("\tPPID: %d\n\tPID: %d\n",getppid(), getpid());
        pipe_value value;
        read(time_pipe[0], &value, sizeof(pipe_value));
        printf("\tRead time is %s from pid:%d\n", value.str, value.pid);
        time_t t = time(NULL);
        printf("\tBase time was %s",  ctime(&t));
    }
    return 0;
}
