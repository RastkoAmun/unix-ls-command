#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <libgen.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include "unixLs.h"


int main(){

    getLengths(&grpLen, &pwLen);

    dir = opendir(".");

    printf("Lengths: %d %d\n\n", grpLen, pwLen);

    while((dp = readdir(dir)) != NULL){
        if(lstat(dp->d_name, &buf) < 0){
            perror("lstat");
            return 1;
        }
        
        grp = getgrgid(buf.st_gid); 
        pw = getpwuid(buf.st_uid);

        // printf("NLINK: %ld\n\n", (long)((long)buf.st_nlink > 10));

        print_permissions(buf.st_mode);
        printf("%4ld",(long)buf.st_nlink);
        printf("%*s", (grpLen + 2),  pw->pw_name);
        printf("%*s", (pwLen + 2), grp->gr_name);

        
        printf("  ");
        printf("%3lld", (long long) buf.st_size);
        printf("  ");

        printf("%ld", (long) buf.st_mtime);
        printf("%s\n", dp->d_name);

        // getAndPrintGroup(buf.st_gid);
        // getAndPrintUserName(buf.st_uid);
    }

    closedir(dir);
    return 0;
}



