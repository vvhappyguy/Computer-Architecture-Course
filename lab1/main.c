#include <stdio.h>
#include <unistd.h>

int main(int args, char*argv[])
{
    printf("PPID: %d\nPID: %d\n",getppid(), getpid());
    return 0;
}