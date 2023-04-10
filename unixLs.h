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
static struct passwd *pw;
static int maxGrpLen = 0;
static int maxPwLen = 0;
static int maxSizeLen = 0;
static int maxFileNameLen = 0;
static int maxINodeLen = 0;


void print_permissions(mode_t mode);
void getLengths(int* maxGrpLen, int* maxPwLen, int* maxSizeLen, int* maxINodeLen, int* maxFileNameLen);
void command_l();
void command_i();