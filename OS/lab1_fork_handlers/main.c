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
#include <sys/wait.h>
#include <stdlib.h>

static int number = 0;

void at_exit_trigger(void);

int main()
{
    atexit(at_exit_trigger);
    printf("1: \n\tPPID: %d\n\tPID: %d\n\n",getppid(), getpid());
    

    pid_t child_pid;
    if((child_pid = fork()) != 0)
    {
        // Parent pid
        printf("It's parent process\n");
        atexit(at_exit_trigger);
        printf("2: \n\tPPID: %d\n\tPID: %d\n",getppid(), getpid());
        int res = 0;
        waitpid(child_pid, &res, 0);
        
        printf("3: \n\tres: %d\n\tPPID: %d\n\tPID: %d\n", res ,getppid(), getpid());
    }
    else
    {
        // Forked pid
        printf("It's child process\n");
        atexit(at_exit_trigger);
        printf("2: \n\tPPID: %d\n\tPID: %d\n",getppid(), getpid());
        // Special bad action
        // int a = 0, b = 0;
        // printf("%d",a / b);
        printf("3: \n\tPPID: %d\n\tPID: %d\n",getppid(), getpid());
    }

    atexit(at_exit_trigger);
    printf("4: \n\tPPID: %d\n\tPID: %d\n",getppid(), getpid());
    
    return 0;
}

void at_exit_trigger(void)
{
    printf("at_exit_trigger(%d) for pid: %d\n", number++, getpid());
}
