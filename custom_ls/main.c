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
        // TODO: Add checking stat structure for all files and printing like ls -al
        printf("%hhu\t%lu\t%hu\t%s\n", namelist[n]->d_type, namelist[n]->d_ino,namelist[n]->d_reclen, namelist[n]->d_name);
        free(namelist[n]);
    }
    free(namelist);

    exit(EXIT_SUCCESS);
}

/* 
    ls -al

total 16
drwxrwxr-x 2 dev dev 4096 окт 19 23:26 .    
drwxrwxr-x 5 dev dev 4096 окт  6 21:09 ..
-rw-rw-r-- 1 dev dev 1103 окт 19 23:28 main.c
-rw-rw-r-- 1 dev dev   69 окт  6 21:09 Makefile

1. filetype
2. permission flags in positive view
3. count of links for file
4. owner name
5. owner group
6. file size
7. time of LastModification
8. name
*/
