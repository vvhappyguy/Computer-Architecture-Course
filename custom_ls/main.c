// Use Makefile for compiling and ./custom_ls for executing
// clang version 7.0.0-3 (tags/RELEASE_700/final)
// Target: x86_64-pc-linux-gnu
// Thread model: posix
// InstalledDir: /usr/bin
// Found candidate GCC installation: /usr/bin/../lib/gcc/x86_64-linux-gnu/8
// Found candidate GCC installation: /usr/lib/gcc/x86_64-linux-gnu/8
// Selected GCC installation: /usr/bin/../lib/gcc/x86_64-linux-gnu/8
// Candidate multilib: .;@m64
// Selected multilib: .;@m64

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    struct dirent **namelist;
    int n;

    n = scandir(".", &namelist, NULL, NULL);
    if (n == -1) {
        perror("scandir");
        exit(EXIT_FAILURE);
    }
    
    
    // Prints dirent fields: $type\t$inode\t$size\t$name
    while (n--) {
        printf("%hhu\t%lu\t%hu\t%s\n", namelist[n]->d_type, namelist[n]->d_ino,namelist[n]->d_reclen, namelist[n]->d_name);
        free(namelist[n]);
    }
    free(namelist);

    exit(EXIT_SUCCESS);
}

