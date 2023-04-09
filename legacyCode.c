//First iteration of readdir to get the necesearry lengths for formating
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
    }