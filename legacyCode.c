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


    // else if(strcmp(argv[1], "-lR") == 0 || strcmp(argv[1], "-Rl") == 0)
        // {
        //     printf("This is -lR \n");
        // }
        // else if(strcmp(argv[1], "-iR") == 0 || strcmp(argv[1], "-Ri") == 0){
        //     printf("This is -iR \n");
        // }
        // else if(strcmp(argv[1], "-liR") == 0 || strcmp(argv[1], "-lRi") == 0 || 
        //     strcmp(argv[1], "-ilR") == 0 || strcmp(argv[1], "-iRl") == 0 ||
        //     strcmp(argv[1], "-Ril") == 0 || strcmp(argv[1], "-Rli") == 0 )
        // {
        //     printf("This is -ilR \n");
        // }
        // else if(argc == 1)
        // {
        //     printf("Ohh yeah no arguments :D :D :D \n");
        //     printf("Does it print this23rqwef? L\n");
        // }
        // else
        // {
        //     printf("Sorry UnixLs doesn't understand your argument\n");
        // }

        // printf("Does it print this? L\n");





        // else if(strcmp(argv[1], "-R") == 0)
        // {
        //    command_R(".");
        // }




            
    // // printf("ARG is %d\n", *argv[1]);
    // // char input[10] = 
    // getLengths(&maxGrpLen, &maxPwLen, &maxSizeLen, &maxINodeLen, &maxFileNameLen);
    // printf("Lengths: %d %d %d %d %d", maxGrpLen, maxPwLen, maxSizeLen, maxFileNameLen, maxINodeLen);

    // printf("Number of arguments %d\n", argc);

