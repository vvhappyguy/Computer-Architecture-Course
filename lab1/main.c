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
