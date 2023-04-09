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

static DIR *dir;
static struct dirent *dp;
static struct stat buf;

static struct group *grp;
static int grpLen = 0;
static struct passwd *pw;
static int pwLen = 0;


void print_permissions(mode_t mode);
void getAndPrintGroup(gid_t grpNum);
void getAndPrintUserName(uid_t uid);
void getLengths();