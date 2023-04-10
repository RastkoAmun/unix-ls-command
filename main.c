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
    
    // printf("ARG is %d\n", *argv[1]);
    // char input[10] = 
    getLengths(&maxGrpLen, &maxPwLen, &maxSizeLen, &maxINodeLen, &maxFileNameLen);
    printf("Lengths: %d %d %d %d %d", maxGrpLen, maxPwLen, maxSizeLen, maxFileNameLen, maxINodeLen);

    printf("Number of arguments %d\n", argc);

    if(strcmp(argv[1], "-l") == 0)
    {
        command_l();
    }
    else if(strcmp(argv[1], "-i") == 0)
    {
        command_i();
    }
    else if(strcmp(argv[1], "-R") == 0)
    {
        printf("This is -R \n");
    }
    else if(strcmp(argv[1], "-li") == 0 || strcmp(argv[1], "-il") == 0)
    {
        command_il();
    }
    else if(strcmp(argv[1], "-lR") == 0 || strcmp(argv[1], "-Rl") == 0)
    {
        printf("This is -lR \n");
    }
    else if(strcmp(argv[1], "-iR") == 0 || strcmp(argv[1], "-Ri") == 0){
        printf("This is -iR \n");
    }
    else if(strcmp(argv[1], "-liR") == 0 || strcmp(argv[1], "-lRi") == 0 || 
        strcmp(argv[1], "-ilR") == 0 || strcmp(argv[1], "-iRl") == 0 ||
        strcmp(argv[1], "-Ril") == 0 || strcmp(argv[1], "-Rli") == 0 )
    {
        printf("This is -ilR \n");
    }
    else if(argv[1] == NULL)
    {
        printf("Ohh yeah no arguments, I will deal with that\n");
    }
    else
    {
        printf("Sorry UnixLs doesn't understand your argument\n");
    }
    

    return 0;
}

