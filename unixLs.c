#include "unixLs.h"

//UTILITY FUNCTIONS
// printing permission from the given mode integer
void print_permissions(mode_t mode) {
  char mode_as_string[10];
  mode_as_string[0] = (char)((S_ISDIR(mode)) ? 'd' : '-');
  mode_as_string[1] = (char)((mode & S_IRUSR) ? 'r' : '-');
  mode_as_string[2] = (char)((mode & S_IWUSR) ? 'w' : '-');
  mode_as_string[3] = (char)((mode & S_IXUSR) ? 'x' : '-');
  mode_as_string[4] = (char)((mode & S_IRGRP) ? 'r' : '-');
  mode_as_string[5] = (char)((mode & S_IWGRP) ? 'w' : '-');
  mode_as_string[6] = (char)((mode & S_IXGRP) ? 'x' : '-');
  mode_as_string[7] = (char)((mode & S_IROTH) ? 'r' : '-');
  mode_as_string[8] = (char)((mode & S_IWOTH) ? 'w' : '-');
  mode_as_string[9] = (char)((mode & S_IXOTH) ? 'x' : '-');
  printf("%s", mode_as_string);
}

//Getting maxinum lengths of all necesary fields, in order to
//format the file in the most optimal way
void getLengths(int* maxGrpLen, int* maxPwLen, int* maxSizeLen, int* maxINodeLen, int* maxFileNameLen){
  //First iteration of readdir to get the necesearry lengths for formating
  dir = opendir(".");
  while((dp = readdir(dir)) != NULL){
    if(lstat(dp->d_name, &buf) < 0){
        perror("lstat");
        return;
    }

    grp = getgrgid(buf.st_gid); 
    pw = getpwuid(buf.st_uid);

    //Getting maximum
    if(strlen(grp->gr_name) > *maxGrpLen){
      *maxGrpLen = strlen(grp->gr_name);
    }
    if(strlen(pw->pw_name) > *maxPwLen){
      *maxPwLen = strlen(pw->pw_name);
    }

    char str[20];
    sprintf(str, "%ld", buf.st_size);
    if(strlen(str) > *maxSizeLen){
      *maxSizeLen = strlen(str);
    }

    char str2[50];
    sprintf(str2, "%ld", buf.st_ino);
    if(strlen(str2) > *maxINodeLen){
      *maxINodeLen = strlen(str2);
    }

    // char str3[100];
    // sprintf(str3, "%ld", dp->d_name);
    if(strlen(dp->d_name) > *maxFileNameLen){
      *maxFileNameLen = strlen(dp->d_name);
    }
    // printf("The integer %ld as a string is %s\n", strlen(str), str);  
  }
  closedir(dir);
}


void command_blank(){
  dir = opendir(".");
  while((dp = readdir(dir)) != NULL){
    if(lstat(dp->d_name, &buf) < 0){
        perror("lstat");
        return;
    }
    printf("  ");
    printf("%s\n", dp->d_name);
  }
  closedir(dir);
}

//COMMAND FOR PRINTING -l ALONE
void command_l(){
  getLengths(&maxGrpLen, &maxPwLen, &maxSizeLen, &maxINodeLen, &maxFileNameLen);
  dir = opendir(".");
  while((dp = readdir(dir)) != NULL){
    if(lstat(dp->d_name, &buf) < 0){
        perror("lstat");
        return;
    }
    
    //SETUP needed for printing everything correctly
    grp = getgrgid(buf.st_gid); 
    pw = getpwuid(buf.st_uid);
    //Converting time
    long time = (long) buf.st_mtime;
    struct tm *timeinfo;
    char buffer[80];
    timeinfo = localtime(&time);
    strftime(buffer, 80, "%b %d %Y %H:%M", timeinfo);

    // ------------------------------------------------------

    //Printing -l in correct format
    printf("  ");
    print_permissions(buf.st_mode);
    printf("%4ld",(long)buf.st_nlink);
    printf("%*s", (maxGrpLen + 2), pw->pw_name);
    printf("%*s", (maxPwLen + 2), grp->gr_name);     
    printf("%*lld", (maxSizeLen + 2), (long long)buf.st_size);
    printf("  ");
    printf("%s", buffer);
    printf("  ");
    printf("%s\n", dp->d_name);
  }
  closedir(dir);
}

void command_i(){
  getLengths(&maxGrpLen, &maxPwLen, &maxSizeLen, &maxINodeLen, &maxFileNameLen);
  dir = opendir(".");

  printf("%*s  ", (maxINodeLen + 2), "iNode");
  printf("%2s\n", "File Name");
  printf("-------------------------------------------------------\n");
  
  while((dp = readdir(dir)) != NULL){
    if(lstat(dp->d_name, &buf) < 0){
        perror("lstat");
        return;
    }

    printf("%*ld  ", (maxINodeLen + 2), buf.st_ino);
    printf("%-2s\n", dp->d_name);
  }
  closedir(dir);
}

void command_il(){
  getLengths(&maxGrpLen, &maxPwLen, &maxSizeLen, &maxINodeLen, &maxFileNameLen);
  dir = opendir(".");
  while((dp = readdir(dir)) != NULL){
    if(lstat(dp->d_name, &buf) < 0){
        perror("lstat");
        return;
    }
    
    //SETUP needed for printing everything correctly
    grp = getgrgid(buf.st_gid); 
    pw = getpwuid(buf.st_uid);
    //Converting time
    long time = (long) buf.st_mtime;
    struct tm *timeinfo;
    char buffer[80];
    timeinfo = localtime(&time);
    strftime(buffer, 80, "%b %d %Y %H:%M", timeinfo);

    // ------------------------------------------------------

    //Printing -l in correct format
    printf("%*ld  ", (maxINodeLen + 2), buf.st_ino);
    print_permissions(buf.st_mode);
    printf("%4ld",(long)buf.st_nlink);
    printf("%*s", (maxGrpLen + 2), pw->pw_name);
    printf("%*s", (maxPwLen + 2), grp->gr_name);     
    printf("%*lld", (maxSizeLen + 2), (long long)buf.st_size);
    printf("  ");
    printf("%s", buffer);
    printf("  ");
    printf("%s\n", dp->d_name);
  }
  closedir(dir);
}

void command_R(char* path){
  dir = opendir(".");

  if (dir == NULL) {
    perror("opendir");
    return;
  }
  
  while((dp = readdir(dir)) != NULL){
    if(strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0){
      continue;
    }

    printf("%s/%s\n", path, dp->d_name);

    char subpath[1024];
    snprintf(subpath, sizeof(subpath), "%s/%s", path, dp->d_name);
    struct stat st;
    if(lstat(subpath, &st) == 0 && S_ISDIR(st.st_mode)){
      command_R(subpath);
    }
    command_R(subpath);
  }
  closedir(dir);
}
