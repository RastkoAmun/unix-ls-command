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

void print_permissions(mode_t mode);
void getAndPrintGroup(gid_t grpNum);
void getAndPrintUserName(uid_t uid);

int main(){
    DIR *dir;
    struct dirent *dp;
    struct stat buf;

    struct group *grp;
    int grpLen = 0;
    struct passwd *pw;
    int pwLen = 0;

    dir = opendir(".");

    while((dp = readdir(dir)) != NULL){
        if(lstat(dp->d_name, &buf) < 0){
            perror("lstat");
            return 1;
        }
        
        grp = getgrgid(buf.st_gid); 
        pw = getpwuid(buf.st_uid);

        //Getting maximum
        if(strlen(grp->gr_name) > grpLen){
          grpLen = strlen(grp->gr_name);
        }
        if(strlen(pw->pw_name) > pwLen){
          pwLen = strlen(pw->pw_name);
        }

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

// void getLengths(){
//   //First iteration of readdir to get the necesearry lengths for formating
//     while((dp = readdir(dir)) != NULL){
//         if(lstat(dp->d_name, &buf) < 0){
//             perror("lstat");
//             return 1;
//         }

//         grp = getgrgid(buf.st_gid); 
//         pw = getpwuid(buf.st_uid);

//         //Getting maximum
//         if(strlen(grp->gr_name) > grpLen){
//           grpLen = strlen(grp->gr_name);
//         }
//         if(strlen(pw->pw_name) > pwLen){
//           pwLen = strlen(pw->pw_name);
//         }
//     }
// }

void getAndPrintGroup(gid_t grpNum) {
  struct group *grp;

  grp = getgrgid(grpNum); 
  
  if (grp) {
    printf("The group ID %u -> %s\n", grpNum, grp->gr_name);
  } else {
    printf("No group name for %u found\n", grpNum);
  }
}


void getAndPrintUserName(uid_t uid) {

  struct passwd *pw = NULL;
  pw = getpwuid(uid);

  if (pw) {
    printf("The user ID %u -> %s\n", uid, pw->pw_name);
  } else {
    perror("Hmm not found???");
    printf("No name found for %u\n", uid);
  }
}


// IMPORTANT
// This code is copied from the internet. I was trying how to print this instead of 
// integer which buf.st_mode returns
void print_permissions(mode_t mode) {
    char mode_as_string[10];
    // putchar((S_ISDIR(mode)) ? 'd' : '-');
    // putchar((mode & S_IRUSR) ? 'r' : '-');
    // putchar((mode & S_IWUSR) ? 'w' : '-');
    // putchar((mode & S_IXUSR) ? 'x' : '-');
    // putchar((mode & S_IRGRP) ? 'r' : '-');
    // putchar((mode & S_IWGRP) ? 'w' : '-');
    // putchar((mode & S_IXGRP) ? 'x' : '-');
    // putchar((mode & S_IROTH) ? 'r' : '-');
    // putchar((mode & S_IWOTH) ? 'w' : '-');
    // putchar((mode & S_IXOTH) ? 'x' : '-');

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