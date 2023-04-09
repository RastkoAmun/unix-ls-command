#include "unixLs.h"

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

void getLengths(int* grpLen, int* pwLen){
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
        if(strlen(grp->gr_name) > *grpLen){
          *grpLen = strlen(grp->gr_name);
        }
        if(strlen(pw->pw_name) > *pwLen){
          *pwLen = strlen(pw->pw_name);
        }
    }
    closedir(dir);

    // printf("Lengths: %d %d\n\n", grpLen, pwLen);
}