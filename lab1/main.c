#include <stdio.h>
#include <unistd.h>

int main()
{
    printf("PPID: %d\nPID: %d\n",getppid(), getpid());
    return 0;
}
