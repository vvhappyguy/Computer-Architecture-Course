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
#include <sys/stat.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>

// Only for killing child process in specific situations
#include <wait.h>
#include <signal.h>

#define FIFO_PATH "/tmp/time_fifo"
#define DATASIZE_TIME sizeof(time_t)

int main()
{
    time_t lt;
    lt = time(NULL);
    printf("Time = %ld\n", lt);
    sleep(1); 

    if(mkfifo(FIFO_PATH, 0666) == -1)
    {
        printf("Can't make FIFO with name %s\n", FIFO_PATH);
        exit(1);
    }
    else
    {
        printf("FIFO with name %s created successfully.\n", FIFO_PATH);
    }
    

     __pid_t child_pid;
     int fifo_fd;
    if((child_pid = fork()) != 0)
    {
        // Parent pid
        printf("It's parent process\n");
        printf("\tPPID: %d\n\tPID: %d\n",getppid(), getpid());
        lt = time(NULL); // Update time before writing to pipe
        fifo_fd = open(FIFO_PATH, O_WRONLY);
        if(fifo_fd == -1)
        {
            printf("Can't open FIFO %x\n", fifo_fd);
            int res = 0;
            kill(child_pid, SIGINT);
            waitpid(child_pid, &res, 0);
            unlink(FIFO_PATH);
            exit(1);
        }
        write(fifo_fd, &lt, DATASIZE_TIME);
        printf("\tWritten time is %ld\n", lt);
        int res = 0;
        close(fifo_fd);
        sleep(1);
        waitpid(child_pid, &res, 0);
        unlink(FIFO_PATH);
    }
    else
    {
        // Forked pid
        printf("It's child process\n");
        printf("\tPPID: %d\n\tPID: %d\n",getppid(), getpid());
        printf("\tBase time was %ld\n", lt);
        fifo_fd = open(FIFO_PATH, O_RDONLY);
        if(fifo_fd == -1)
        {
            printf("Can't open FIFO %x\n", fifo_fd);            
            exit(1);
        }
        read(fifo_fd, &lt, DATASIZE_TIME);
        close(fifo_fd);
        printf("\tRead time is %ld\n", lt);
        sleep(1);
        lt = time(NULL);
        printf("\tNow time is %ld\n", lt);
    }
    return 0;
}
