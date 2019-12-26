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
#include <sys/stat.h>
#include <time.h> // For time
#include <pwd.h> // For user owner
#include <grp.h> // For group owner
#include <string.h>

void printFileType( mode_t);
void printPerms( mode_t);
void printUserOwner( uid_t);
void printGroupOwner( gid_t _gid);
void printSize( off_t _size);

#define TIME_BUFFER_SIZE_STR 25

int main(void)
{
    struct dirent **namelist;
    int n;

    n = scandir(".", &namelist, NULL, NULL);
    if (n == -1) {
        perror("scandir");
        exit(EXIT_FAILURE);
    }

    
    printf("total %i\n", n);
    while (n--) {
        static struct stat tmp_stat;

        if(stat(namelist[n]->d_name, &tmp_stat) == 0)
        {
            printFileType(tmp_stat.st_mode);
            printPerms(tmp_stat.st_mode);
            printf(" %lu", tmp_stat.st_nlink);
            printf(" ");
            printUserOwner(tmp_stat.st_uid);
            printf(" ");
            printGroupOwner(tmp_stat.st_gid);
            printf(" ");
            printSize(tmp_stat.st_size);
            printf(" ");
            // Manipulation for deleting useless \n from ctime returned string
            char tmp_time[TIME_BUFFER_SIZE_STR];
            strncpy(tmp_time, ctime(&tmp_stat.st_mtime), TIME_BUFFER_SIZE_STR - 1);
            tmp_time[TIME_BUFFER_SIZE_STR - 1] = '\0';
            printf("%s", tmp_time);
            printf("\t%s", namelist[n]->d_name);
            printf("\n");
        }
        free(namelist[n]);
    }
    free(namelist);

    exit(EXIT_SUCCESS);
}

void printFileType( mode_t _mode)
{
            switch (_mode & S_IFMT)
            {
            case S_IFBLK:
                printf("b");
                break;
            case  S_IFCHR:
                printf("c");
                break;
            case  S_IFDIR:
                printf("d");
                break;
            case  S_IFIFO:
                printf("p");
                break;
            case  S_IFLNK:
                printf("l");
                break;
            case  S_IFSOCK:
                printf("s");
                break;
            // case  S_IFREG:
            //     printf("f");
            //     break;
            default:
                printf("-");
                break;
            }
}

void printPerms( mode_t _mode)
{
    if(_mode & 0400)
        printf("r");
    else
        printf("-");
    if(_mode & 0200)
        printf("w");
    else
        printf("-");
    if(_mode & 0100)
        printf("x");
    else
        printf("-");
    if(_mode & 0040)
        printf("r");
    else
        printf("-");
    if(_mode & 0020)
        printf("w");
    else
        printf("-");
    if(_mode & 0010)
        printf("x");
    else
        printf("-");
    if(_mode & 0004)
        printf("r");
    else
        printf("-");
    if(_mode & 0002)
        printf("w");
    else
        printf("-");
    if(_mode & 0001)
        printf("x");
    else
        printf("-");
}

void printUserOwner( uid_t _uid)
{
    struct passwd *pws;
    pws = getpwuid(_uid);
    printf("%s", pws->pw_name);
}

void printGroupOwner( gid_t _gid)
{
    struct group *gp;
    gp = getgrgid(_gid);
    printf("%s", gp->gr_name);
}

void printSize( off_t _size)
{
    printf("%5ld", _size);
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
