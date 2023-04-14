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

int main(int argc, char *argv[]){
    if(argc > 1){
        if(strcmp(argv[1], "-l") == 0)
        {
            command_l();
        }
        else if(strcmp(argv[1], "-i") == 0)
        {
            command_i();
        }
        else if(strcmp(argv[1], "-li") == 0 || strcmp(argv[1], "-il") == 0)
        {
            command_il();
        }
        else
        {
            printf("Unknown command, please try again!\n");
        }
    }else{
        command_blank();
    }
    
    return 0;
}

